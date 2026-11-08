import http.client
import json
import os
from pathlib import Path
import subprocess
import tempfile
import unittest

import page_meta


class FakeLogins(page_meta.Logins):
    """Logins with a scripted GitHub answer instead of network calls."""

    def __init__(self, cache, answer):
        super().__init__(cache, "cp-algorithms/cp-algorithms", "token")
        self.answer = answer
        self.calls = 0

    def query(self, sha):
        self.calls += 1
        if isinstance(self.answer, Exception):
            raise self.answer
        return self.answer


class LoginCacheTest(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.cache = Path(self.temp.name) / "authors.json"
        self.cache.write_text(json.dumps({
            "known": {"login": "known", "name": "Known", "url": "https://github.com/known",
                      "emails": ["known@example.com"]},
        }))
        self.before = self.cache.read_text()

    def test_failed_lookup_is_not_cached(self):
        for error in (OSError("timeout"), http.client.IncompleteRead(b"{"),
                      LookupError("RATE_LIMITED"), ValueError("bad JSON")):
            with self.subTest(error=type(error).__name__):
                logins = FakeLogins(self.cache, error)
                self.assertEqual(logins.resolve("new@example.com", "New Person", "a" * 40),
                                 ("New Person", "#"))
                # Not retried within the same run, and nothing is saved.
                logins.resolve("new@example.com", "New Person", "a" * 40)
                self.assertEqual(logins.calls, 1)
                logins.save()
                self.assertEqual(self.cache.read_text(), self.before)

    def test_found_account_is_cached(self):
        user = {"login": "newuser", "name": "New Person", "url": "https://github.com/newuser"}
        logins = FakeLogins(self.cache, user)
        self.assertEqual(logins.resolve("new@example.com", "New Person", "a" * 40),
                         ("newuser", "https://github.com/newuser"))
        logins.save()
        saved = json.loads(self.cache.read_text())
        self.assertEqual(saved["newuser"]["emails"], ["new@example.com"])

    def test_missing_account_is_cached_once(self):
        logins = FakeLogins(self.cache, None)
        self.assertEqual(logins.resolve("new@example.com", "New Person", "a" * 40),
                         ("New Person", "#"))
        logins.save()
        saved = json.loads(self.cache.read_text())
        self.assertEqual(saved["new@example.com"]["login"], "New Person")
        # A later build reads the cache and does not ask GitHub again.
        later = FakeLogins(self.cache, None)
        later.resolve("new@example.com", "New Person", "a" * 40)
        self.assertEqual(later.calls, 0)

    def test_known_email_needs_no_lookup(self):
        logins = FakeLogins(self.cache, OSError("must not be called"))
        self.assertEqual(logins.resolve("known@example.com", "Known", "a" * 40),
                         ("known", "https://github.com/known"))
        self.assertEqual(logins.calls, 0)


class CreationDatesTest(unittest.TestCase):
    """creation_dates() on a small repository with dated commits."""

    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.cwd = os.getcwd()
        os.chdir(self.root)
        self.addCleanup(os.chdir, self.cwd)
        self.git("init", "-q")
        self.git("config", "user.email", "test@example.com")
        self.git("config", "user.name", "Test")

    def git(self, *args, date=None):
        env = dict(os.environ)
        if date:
            env["GIT_AUTHOR_DATE"] = env["GIT_COMMITTER_DATE"] = f"@{date} +0000"
        subprocess.run(["git", *args], check=True, env=env, capture_output=True)

    def commit(self, date, message):
        self.git("add", "-A")
        self.git("commit", "-q", "-m", message, date=date)

    def test_copy_and_rename_keep_the_original_date(self):
        text = "".join(f"line {i} of an article about Fenwick trees\n" for i in range(40))
        Path("a.md").write_text(text)
        self.commit(1000000000, "add a")
        Path("other.md").write_text("unrelated\n")
        self.commit(1100000000, "add other")
        # Copy a.md while a.md itself stays unchanged in this commit.
        Path("b.md").write_text(text)
        self.commit(1200000000, "copy a to b")
        Path("b.md").rename("c.md")
        self.commit(1300000000, "rename b to c")
        created = page_meta.creation_dates()
        self.assertEqual(created["a.md"], 1000000000)
        self.assertEqual(created["b.md"], 1000000000)
        self.assertEqual(created["c.md"], 1000000000)
        self.assertEqual(created["other.md"], 1100000000)


if __name__ == "__main__":
    unittest.main()
