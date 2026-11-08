// Header button that hides or shows the sidebar on wide screens.
// The table of contents is integrated into the navigation sidebar,
// so one button covers both. The choice persists across pages.
// The T, M and B keys also toggle it. Shift+click on the button (or
// Shift+Enter) turns these shortcut keys off or on again. The button's
// title says which keys work and how to switch them.
(() => {
  const hiddenKey = "cpalgo-sidebar-hidden";
  const shortcutsKey = "cpalgo-sidebar-shortcuts";
  const icon =
    '<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24">' +
    '<path d="M3 6h18v2H3V6m0 5h18v2H3v-2m0 5h18v2H3v-2Z"></path></svg>';

  const load = (name) => {
    try {
      return localStorage.getItem(name);
    } catch {
      return null;
    }
  };
  const store = (name, value) => {
    try {
      localStorage.setItem(name, value);
    } catch {}
  };

  let shortcuts = load(shortcutsKey) !== "off";
  const describe = () =>
    shortcuts
      ? "Toggle navigation. Shortcut keys: T, M or B. Shift+click to turn them off."
      : "Toggle navigation. Shortcut keys are off. Shift+click to turn them on.";

  const isHidden = () => document.documentElement.classList.contains("sidebar-hidden");
  const apply = (hidden) => {
    document.documentElement.classList.toggle("sidebar-hidden", hidden);
    // Screen readers announce whether the navigation is shown.
    document.querySelectorAll(".sidebar-toggle").forEach((button) =>
      button.setAttribute("aria-expanded", String(!hidden)));
  };
  const toggle = () => {
    const hidden = !isHidden();
    apply(hidden);
    store(hiddenKey, hidden ? "1" : "0");
  };

  // Apply before first paint to avoid a flash of the sidebar.
  apply(load(hiddenKey) === "1");

  document.addEventListener("DOMContentLoaded", () => {
    const title = document.querySelector(".md-header__title");
    if (!title) return;
    const button = document.createElement("button");
    button.className = "md-header__button md-icon sidebar-toggle";
    button.setAttribute("aria-label", "Toggle navigation");
    button.title = describe();
    button.innerHTML = icon;
    const sidebar = document.querySelector(".md-sidebar--primary");
    if (sidebar) {
      sidebar.id ||= "sidebar-navigation";
      button.setAttribute("aria-controls", sidebar.id);
    }
    button.setAttribute("aria-expanded", String(!isHidden()));
    // Announces the shortcut setting after a Shift+click.
    const status = document.createElement("span");
    status.className = "md-visually-hidden";
    status.setAttribute("role", "status");
    button.addEventListener("click", (event) => {
      if (event.shiftKey) {
        shortcuts = !shortcuts;
        store(shortcutsKey, shortcuts ? "on" : "off");
        button.title = describe();
        status.textContent = shortcuts ? "Shortcut keys on." : "Shortcut keys off.";
        return;
      }
      toggle();
    });
    title.after(button, status);
  });

  document.addEventListener("keydown", (event) => {
    if (!shortcuts || event.ctrlKey || event.metaKey || event.altKey) return;
    // composedPath() also sees inputs inside shadow roots, such as search.
    const target = event.composedPath()[0];
    if (!(target instanceof Element)) return;
    if (target.isContentEditable || target.closest("input, textarea, select, [contenteditable]")) return;
    if (["t", "m", "b"].includes(event.key.toLowerCase())) toggle();
  });
})();
