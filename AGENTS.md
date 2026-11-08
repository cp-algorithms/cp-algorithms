# Working on cp-algorithms

cp-algorithms teaches algorithms for competitive programming. Prefer a clear
explanation and a short, correct implementation that readers can understand,
test, and adapt. Read `CONTRIBUTING.md` and follow the surrounding article's
conventions. These instructions apply to agent-assisted contributions.

## Before making changes

- Read the whole affected section, its prerequisites, extracted snippets, and
  tests. Read the linked issue and all existing PR review threads before editing
  or replying. Check for an existing fix or overlapping PR.
- Decide whether an addition belongs before polishing it or requesting more
  work. Correctness alone does not justify inclusion: compare its educational
  benefit with the current article and related coverage. Consider a compact
  addition, replacement, short note or link, or declining the addition.
  Respect prior maintainer decisions about scope. If the benefit is unclear,
  raise that decision before expanding the implementation.
- State the concrete problem and the smallest change that solves it. Keep
  unrelated cleanup, new APIs, alternative implementations, and infrastructure
  changes out of the PR unless they are necessary to the same change.
- For a claimed bug, identify the supported input contract and violated
  invariant. Reproduce it on the current base before fixing it. A failing test
  on an unsupported input does not establish a bug. Equally, do not invent a
  restriction to excuse an ordinary supported case.
- Preserve contributors' attribution and concurrent work. Prefer additional
  commits to rewriting someone else's published branch. A request to prepare
  a PR does not by itself authorize merging or deploying it.

## Explanations and code

- Explain the problem and intuition before introducing notation. Define every
  symbol, state, index convention, input bound, and nonstandard term before use.
  Link relevant prerequisites instead of repeating their explanations.
- Explain why the algorithm works, not just what each line does. Identify the
  invariant and justify its preservation and the final result. For an optimum,
  prove optimality as well as feasibility. Justify the stated complexity.
- Keep the explanation, examples, and implementation consistent. Distinguish
  properties of the general technique from choices specific to an example.
  Work through examples, including equality and boundary cases where relevant.
- Prefer one implementation per idea. Keep multiple approaches or languages
  only when each offers a meaningful idea or use case worth the explanation
  and upkeep. Explain when to choose each. If a new approach is better at the
  same job, consider replacing the existing one instead of keeping both.
  Reuse existing articles and library routines where that makes the result
  easier to follow. Avoid unnecessary input/output scaffolding and generic APIs.
- State meaningful numeric and resource bounds. Check intermediate arithmetic,
  sentinels, indexing, initialization, and repeated calls, not only the final
  result. Use exact integer arithmetic when floating point would invalidate the
  algorithm. Do not widen the supported domain without considering its cost.
- Preserve useful fast paths. Support performance claims with comparable
  measurements on relevant tasks, or remove/qualify the claim. Do not describe
  a microbenchmark or a different compiler configuration as an end-to-end win.
- Credit sources for code, proofs, translations, and illustrations. Establish
  permission or a compatible license for reused material. An image being
  publicly accessible is not permission to republish it.

## Tests and rendering

- For new or changed executable snippets, use a named fence such as
  ```` ```{.cpp file=example_name} ```` and a test in `test/` that includes the
  extracted header. Test the published snippet, not a duplicate implementation.
- Use a small independent oracle, a meaningful regression, or an appropriate
  problem checker. Cover relevant supported boundaries and repeated use. Keep
  fixtures bounded in time and memory. For a bug fix, show that the regression
  fails before the fix and passes afterward when practical.
- From `test/`, run `python3 extract_snippets.py`, compile and run the affected
  test, then run `./test.sh` for C++ changes. The runner currently uses C++17 and
  UBSan. A standalone Python/Java test is not run by this runner: explicitly
  integrate and execute it if the PR relies on it. Do not require algorithm
  tests for a wording-only or link-only change.
- Build site changes with `mkdocs build --strict` and inspect the affected page
  in the actual MkDocs/site preview. GitHub's Markdown preview is insufficient.
  Check math, lists, tabs, admonitions, images, and links. For UI changes, check
  relevant widths, themes, keyboard behavior, and focused/nonempty states.
- Add new articles to `src/navigation.md` and the new-article list in `README.md`.
  Include the appropriate Original/Translated front matter and source credit.
  Preserve old anchors and provide redirects for moved pages.
- Before adding a practice problem, read its statement and, when needed, the
  editorial. Check that the article's technique is a natural, useful part of
  the solution. Compare what it teaches with the closest existing problems,
  including examples in the article body. Check repeated learning goals as
  well as duplicate links. Do not infer these from problem titles alone.
- Keep practice lists compact. Beyond roughly ten problems, look for a
  compelling benefit such as a new application, difficulty gap, or better
  replacement. This is a guideline, not a hard cap or a reason to prune blindly.
  A useful judge link for an existing worked example can still add value.
  If the benefit is unclear, ask for a brief rationale, not a full solution.
- Check problem links, prefer a judge where readers can submit, and place
  problems by difficulty where practical.
- Do not commit extracted headers, binaries, caches, local editor settings, or
  generated site output as ordinary source changes. Changes to the extractor or
  test framework must keep tests connected to the maintained article snippets.
- Check CI for the latest PR head. A successful AI-review check is not a build
  or test result. Report missing, pending, or blocked checks accurately. Verify
  automated findings against the code and its contract before acting on them.

## Writing

These rules apply to contributor-facing text: `README.md`, `CONTRIBUTING.md`,
this file, site pages outside the articles, error messages, commit messages,
PR descriptions and review replies. Article prose keeps its own style.
These rules adapt
[ratschlab/writing-rules](https://github.com/ratschlab/writing-rules/blob/5fe98632f7399e0dd1006cc20ff38f90c9bd823e/PRINCIPLES.md),
which gives the sources behind each principle.

- Start with the outcome or the action the reader must take. Keep the
  prerequisites, consequences and limits that affect a decision.
- Keep facts and uncertainty accurate. Check every count, path, command and
  workflow name against the repository. Keep "may" or "might" where the outcome
  is really uncertain.
- An error message names the problem and a next step. Give the cause only when
  it is known.
- Say who acts when responsibility matters.
- Make headings, labels and link text name their topic or destination. Never
  use "here" as link text. Use one name for each thing, and match labels on the
  site and on GitHub exactly.
- Make three or more parallel items a list. Number the steps of a procedure.
- Put what most readers need first. Move rare setup and background to a later
  section or a link.
- House style: one idea per sentence, no semicolons, and numbers as digits. Aim
  for about 20 words per sentence and at most 5 sentences per paragraph. Treat
  these as prompts for review. Never change the meaning to meet them.
- Before checking style, read the text as its reader. Check that they can find
  the point and take the right action.

## Communicating with maintainers

- Lead with the concrete problem and resulting change. Assume the reader has
  not seen your local work. A routine description usually needs one or two
  short paragraphs. Aim for at most 100–200 words unless the change needs more.
- Include a minimal reproducer or before/after example for a bug, important
  assumptions, source attribution, and any material compatibility or performance
  tradeoff. Mention manual checks and limitations that matter to the decision.
  Do not repeat passing CI, test counts, or routine validation checklists.
- Use simple, natural language. Omit generic praise, repeated summaries,
  implementation inventories, internal task history, and bulky logs. Keep
  explanatory detail in the article or linked supporting material.
- Write a commit subject that describes the change on its own. Use the body for
  the motivation and constraints that the diff does not show.
- Report a suspected vulnerability through the private route in `SECURITY.md`.
  Keep its details out of public issues, PRs and comments.
- Reply in the relevant review thread. State what changed, or give a concise
  technical reason for disagreeing. Check the latest code before saying an
  issue is fixed. Do not repeatedly ping maintainers without new information.
- Keep the title and description consistent with the final diff. Use one source
  line per paragraph or list item in GitHub messages and let GitHub wrap it.
- Briefly disclose material AI assistance and the extent of human verification.
  Preserve any requested disclosures. Never imply a personal review, test run,
  or judge acceptance that did not happen.
- Before requesting review, read the complete diff and the exact message as its
  recipient. Remove unnecessary text, check links and evidence, and make the
  remaining decision or requested action clear.
