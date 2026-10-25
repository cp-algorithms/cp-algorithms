# Working on cp-algorithms

cp-algorithms teaches algorithms for competitive programming. Prefer a clear
explanation and a short, correct implementation that readers can understand,
test, and adapt. Read `CONTRIBUTING.md` and follow the surrounding article's
conventions. These instructions apply to agent-assisted contributions.

## Before making changes

- Read the whole affected section, its prerequisites, extracted snippets, and
  tests. Read the linked issue and all existing PR review threads before editing
  or replying. Check for an existing fix or overlapping PR.
- State the concrete problem and the smallest change that solves it. Keep
  unrelated cleanup, new APIs, alternative implementations, and infrastructure
  changes out of the PR unless they are necessary to the same change.
- For a claimed bug, identify the supported input contract and violated
  invariant. Reproduce it on the current base before fixing it. A failing test
  on an unsupported input does not establish a bug; equally, do not invent a
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
  prove optimality as well as feasibility; justify the stated complexity.
- Keep the explanation, examples, and implementation consistent. Distinguish
  properties of the general technique from choices specific to an example.
  Work through examples, including equality and boundary cases where relevant.
- Prefer one implementation per idea. Add another language or algorithm only
  when it provides a concrete benefit worth the extra explanation and upkeep.
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
- Add new articles to `src/navigation.md` and the new-article list in `README.md`;
  include the appropriate Original/Translated front matter and source credit.
  Preserve old anchors and provide redirects for moved pages.
- Before adding a practice problem, read its statement and identify how the
  article's algorithm helps solve it. Check the link, avoid duplicate entries,
  and place it by difficulty where practical.
- Do not commit extracted headers, binaries, caches, local editor settings, or
  generated site output as ordinary source changes. Changes to the extractor or
  test framework must keep tests connected to the maintained article snippets.
- Check CI for the latest PR head. A successful AI-review check is not a build
  or test result. Report missing, pending, or blocked checks accurately. Verify
  automated findings against the code and its contract before acting on them.

## Communicating with maintainers

- Lead with the concrete problem and resulting change. Assume the reader has
  not seen your local work. A routine description usually needs one or two
  short paragraphs; aim for at most 100–200 words unless the change needs more.
- Include a minimal reproducer or before/after example for a bug, important
  assumptions, source attribution, and any material compatibility or performance
  tradeoff. Mention manual checks and limitations that matter to the decision;
  do not repeat passing CI, test counts, or routine validation checklists.
- Use simple, natural language. Omit generic praise, repeated summaries,
  implementation inventories, internal task history, and bulky logs. Keep
  explanatory detail in the article or linked supporting material.
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
