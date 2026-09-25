// The mkdocs-toggle-sidebar-plugin button has nothing to toggle once the
// theme collapses the sidebar into the drawer, and it looks like a duplicate
// of the drawer hamburger next to it. Instead of replicating the theme's
// breakpoint here, mirror the theme itself: show the button only while the
// drawer hamburger is hidden.
document.addEventListener("DOMContentLoaded", () => {
  const drawer = document.querySelector(".md-header label[for='__drawer']");
  if (!drawer) return;

  const sync = () => {
    const toggle = document.querySelector(".mkdocs-toggle-sidebar-button");
    if (toggle) {
      toggle.style.display = getComputedStyle(drawer).display === "none" ? "" : "none";
    }
  };

  window.addEventListener("resize", sync);
  const header = document.querySelector(".md-header__inner");
  if (header) {
    // The plugin inserts its button after this script runs
    new MutationObserver(sync).observe(header, { childList: true });
  }
  sync();
});
