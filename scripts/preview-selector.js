document.addEventListener("DOMContentLoaded", async () => {
  const select = document.querySelector(".article-preview select");
  if (!select) return;
  select.addEventListener("change", () => location.assign(select.value));
  try {
    const response = await fetch(select.dataset.index, {cache: "no-cache"});
    if (!response.ok) return;
    const previews = await response.json();
    for (const number of Object.keys(previews).sort((a, b) => Number(a) - Number(b))) {
      if (!/^[1-9][0-9]*$/.test(number) || number === select.dataset.pr) continue;
      const path = previews[number].pages[select.dataset.article];
      if (!path || !path.startsWith("/") || path.startsWith("//")) continue;
      select.add(new Option(`PR #${number}`, path));
    }
  } catch {
    // Main and the current PR remain usable when the preview list is unavailable.
  }
});
