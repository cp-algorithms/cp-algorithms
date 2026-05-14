import re


def define_env(env):

    @env.macro
    def get_practice_problems():

        page_path = env.page.file.abs_src_path

        with open(page_path, "r", encoding="utf-8") as f:
            content = f.read()

        # match:
        # ## Problems
        # ## Practice Problems
        section_match = re.search(
            r"## (Practice Problems|Problems)(.*?)(\n## |\Z)",
            content,
            re.S,
        )

        if not section_match:
            return "No problems found."

        section = section_match.group(2)

        # extract ALL markdown links
        matches = re.findall(r"\[(.*?)\]\((.*?)\)", section)

        if not matches:
            return "No problems found."

        grouped = {}

        for title, url in matches:
            # platform extraction
            if "-" in title:
                platform = title.split("-")[0].strip()
            else:
                platform = "Other"

            grouped.setdefault(platform, []).append(
                {
                    "title": title.strip(),
                    "url": url.strip(),
                }
            )

        output = []

        for platform in sorted(grouped.keys()):
            output.append(f"### {platform}")

            for p in grouped[platform]:
                output.append(f"* [{p['title']}]({p['url']})")

            output.append("")

        return "\n".join(output)
