// Header button that hides or shows the sidebar on wide screens.
// The table of contents is integrated into the navigation sidebar,
// so one button covers both. The choice persists across pages.
// The T, M and B keys also toggle it.
(() => {
  const key = "cpalgo-sidebar-hidden";
  const icon =
    '<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24">' +
    '<path d="M3 6h18v2H3V6m0 5h18v2H3v-2m0 5h18v2H3v-2Z"></path></svg>';

  const read = () => {
    try {
      return localStorage.getItem(key) === "1";
    } catch {
      return false;
    }
  };
  const apply = (hidden) =>
    document.documentElement.classList.toggle("sidebar-hidden", hidden);
  const toggle = () => {
    const hidden = !document.documentElement.classList.contains("sidebar-hidden");
    apply(hidden);
    try {
      localStorage.setItem(key, hidden ? "1" : "0");
    } catch {}
  };

  // Apply before first paint to avoid a flash of the sidebar.
  apply(read());

  document.addEventListener("DOMContentLoaded", () => {
    const title = document.querySelector(".md-header__title");
    if (title) {
      const button = document.createElement("button");
      button.className = "md-header__button md-icon sidebar-toggle";
      button.title = "Toggle navigation";
      button.setAttribute("aria-label", "Toggle navigation");
      button.innerHTML = icon;
      button.addEventListener("click", toggle);
      title.after(button);
    }
  });

  document.addEventListener("keydown", (event) => {
    if (event.ctrlKey || event.metaKey || event.altKey) return;
    const target = event.target;
    if (target.isContentEditable || /^(INPUT|TEXTAREA|SELECT)$/.test(target.tagName)) return;
    if (["t", "m", "b"].includes(event.key.toLowerCase())) toggle();
  });
})();
