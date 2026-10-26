"""Exercise the actual deployment shell steps with local gh/git stubs."""
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
import yaml

repo = Path(__file__).resolve().parents[1]
steps = yaml.safe_load((repo/'.github/workflows/deploy-prod.yml').read_text())['jobs']['deploy_github_pages']['steps']
gate = next(step['run'] for step in steps if step.get('id') == 'get-pr-number')
publish = next(step['run'] for step in steps if step.get('id') == 'article-previews')
configure = next(step['run'] for step in steps if step.get('id') == 'preview-site')
sha = 'a' * 40

fake_gh = '''#!/usr/bin/python3
import json, os, pathlib, subprocess, sys
root = pathlib.Path(os.environ['FIXTURE_ROOT'])
state = json.loads((root/'state.json').read_text())
endpoint = next(arg for arg in sys.argv if arg.startswith('repos/'))
if endpoint.endswith('/files'):
    (root/'files-read').touch()
    if os.environ['SCENARIO'] == 'advance-during-files':
        state['head']['sha'] = 'b' * 40
    elif os.environ['SCENARIO'] == 'close-during-files':
        state['state'] = 'closed'
    (root/'state.json').write_text(json.dumps(state))
    name = 'src/new.md' if state['head']['sha'] != 'a' * 40 else 'src/old.md'
    print(json.dumps([[{'filename': name}]]))
else:
    if endpoint.endswith('/pages'):
        base = 'https://previews.example/project/'
        if os.environ['SCENARIO'] == 'same-origin':
            base = 'https://gh.cp-algorithms.com/previews/'
        if os.environ['SCENARIO'] == 'production-origin':
            base = 'https://cp-algorithms.com/previews/'
        branch = 'main' if os.environ['SCENARIO'] == 'wrong-pages-branch' else 'gh-pages'
        state = {'html_url':base,'source':{'branch':branch,'path':'/'}}
    elif '/git/trees/' in endpoint:
        state = {'truncated':os.environ['SCENARIO'] == 'truncated-inventory','tree':[{'type':'blob','path':'main/old.html'}]}
    query = sys.argv[sys.argv.index('--jq')+1] if '--jq' in sys.argv else '.'
    sys.exit(subprocess.run(['jq','-r',query],input=json.dumps(state),text=True).returncode)
'''
fake_git = '''#!/usr/bin/python3
import os, pathlib, sys
root = pathlib.Path(os.environ['FIXTURE_ROOT'])
if 'push' in sys.argv:
    (root/'pushed').touch()
sys.exit(1 if 'diff' in sys.argv else 0)
'''
fake_python = '''#!/usr/bin/python3
import os, sys
if sys.argv[1:3] == ['-m', 'pip']:
    sys.exit(0)
os.execv(sys.executable, [sys.executable, *sys.argv[1:]])
'''

class PreviewDeploymentTest(unittest.TestCase):
    def test_publication_guards(self):
        for scenario in ('current', 'already-stale', 'advance-during-files', 'already-closed', 'close-during-files',
                         'missing-token', 'same-repo', 'same-origin', 'production-origin', 'wrong-pages-branch', 'truncated-inventory'):
            with self.subTest(scenario=scenario), tempfile.TemporaryDirectory(prefix='cp-deploy-check-') as temp:
                root = Path(temp)
                for folder in ('bin','public/123','published','temp'):
                    (root/folder).mkdir(parents=True)
                (root/'scripts').symlink_to(repo/'scripts',target_is_directory=True)
                (root/'public/123/old.html').write_text('<html><head></head><body><article>Old build</article></body></html>')
                state = {'state':'closed' if scenario == 'already-closed' else 'open', 'head':{'sha':'b'*40 if scenario == 'already-stale' else sha}}
                (root/'state.json').write_text(json.dumps(state))
                for name, code in (('gh',fake_gh),('git',fake_git),('python3',fake_python)):
                    path = root/'bin'/name
                    path.write_text(code.replace('#!/usr/bin/python3', '#!' + sys.executable))
                    path.chmod(0o755)
                env = dict(os.environ,PATH=str(root/'bin')+':'+os.environ['PATH'],FIXTURE_ROOT=str(root),SCENARIO=scenario,
                           BUILD_EVENT='pull_request',BUILD_SHA=sha,PR_NUMBER='123',GITHUB_REPOSITORY='test/site',
                           GH_TOKEN='' if scenario == 'missing-token' else 'local-stub',
                           PREVIEW_REPOSITORY='TEST/SITE' if scenario == 'same-repo' else 'test/previews',
                           RUNNER_TEMP=str(root/'temp'),GITHUB_OUTPUT=str(root/'output'),GITHUB_STEP_SUMMARY=str(root/'summary'),
                           PYTHONDONTWRITEBYTECODE='1')
                subprocess.run(['bash','-eo','pipefail','-c',gate],cwd=root,env=env,check=True,capture_output=True,text=True)
                if 'deploy=true' in (root/'output').read_text():
                    result = subprocess.run(['bash','-eo','pipefail','-c',configure],cwd=root,env=env,capture_output=True,text=True)
                    if result.returncode == 0:
                        env['PREVIEW_SITE_URL'] = next(line[4:] for line in (root/'output').read_text().splitlines() if line.startswith('url='))
                        result = subprocess.run(['bash','-eo','pipefail','-c',publish],cwd=root,env=env,capture_output=True,text=True)
                    if result.returncode and scenario in ('current','advance-during-files','close-during-files'):
                        raise RuntimeError(result.stdout+result.stderr)
                    if scenario in ('missing-token','same-repo','same-origin','production-origin','wrong-pages-branch','truncated-inventory'):
                        self.assertNotEqual(result.returncode, 0, 'Invalid configuration did not fail closed')
                pushed = (root/'pushed').exists()
                expected = scenario == 'current'
                self.assertEqual(pushed, expected)
                if pushed:
                    registry = json.loads((root/'published/preview/index.json').read_text())
                    self.assertEqual(registry['123']['pages'], {'old.html':'/project/old/preview/123/'})
                    self.assertIn('url=https://previews.example/project/preview/123/', (root/'output').read_text())


if __name__ == "__main__":
    unittest.main()
