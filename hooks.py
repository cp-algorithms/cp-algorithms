import os
import subprocess

# git 2.56.0 stops `git log --follow` at the 2021 rename of these pages, so the
# git-revision-date-localized plugin finds no creation commit and strict builds fail.
# Remove CREATION_COMMITS and on_config once the CI runners use a git release with the
# mv/log-follow-speedup fix, which is pending after 2.56.0. The override only applies
# while git cannot find the creation commit itself.
CREATION_COMMITS = {
    "src/geometry/convex-hull.md": "f59e64e0c6f2caedc7971e2318c3f470796ab465",
}


def on_env(env, config, files):
    env.add_extension('jinja2.ext.do')


def on_config(config):
    try:
        from mkdocs_git_revision_date_localized_plugin.util import Util
    except ImportError:
        return config
    root = os.path.dirname(os.path.realpath(config.config_file_path))
    overrides = {os.path.join(root, path): commit for path, commit in CREATION_COMMITS.items()}
    original = Util.get_git_commit_timestamp

    def git(*args):
        return subprocess.run(["git", "-C", root, *args], capture_output=True, text=True, check=True).stdout.strip()

    def get_git_commit_timestamp(self, path, is_first_commit=False):
        commit = overrides.get(os.path.realpath(path)) if is_first_commit else None
        if commit and not git("log", "--follow", "--diff-filter=Ar", "--format=%H", "--", path):
            return commit, int(git("show", "-s", "--format=%at", commit))
        return original(self, path, is_first_commit)

    Util.get_git_commit_timestamp = get_git_commit_timestamp
    return config
