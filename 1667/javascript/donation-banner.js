document.addEventListener("DOMContentLoaded", () => {
  const STORAGE_KEY = "donationBannerHiddenUntil";
  const HIDE_DAYS = 90;

  const hiddenUntil = Number(localStorage.getItem(STORAGE_KEY) || 0);
  if (Date.now() < hiddenUntil) return;

  const banner = document.createElement("aside");
  banner.id = "donation-banner";
  banner.innerHTML = `
    <div class="donation-banner">
      <p class="donation-text">
        <strong>Please consider
          <a class="donation-link" href="https://github.com/sponsors/cp-algorithms">
            supporting us</a>
        </strong> — ad-free, volunteer-run.
      </p>
      <button class="donation-close" type="button" aria-label="Dismiss">×</button>
    </div>
  `;

  const content = document.querySelector("div.md-content") || document.body;
  content.insertBefore(banner, content.firstChild);

  banner.querySelector(".donation-close").addEventListener("click", () => {
    banner.remove();
    const until = Date.now() + HIDE_DAYS * 24 * 60 * 60 * 1000;
    localStorage.setItem(STORAGE_KEY, String(until));
  });
});
