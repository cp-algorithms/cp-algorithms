document.addEventListener("DOMContentLoaded", () => {
  if (document.cookie.indexOf("donation_banner_hidden=true") !== -1) return;

  const banner = document.createElement("div");
  banner.id = "donation-banner";
  banner.style = "display:flex;align-items:center;justify-content:space-between;position:relative;background:#f44336;color:white;padding:0.75rem 1rem;margin-bottom:1rem;font-size:1rem;";

  const span = document.createElement("span");
  span.innerHTML = `
  <strong>
    Please consider 
    <a href="https://github.com/sponsors/cp-algorithms" style="color: #bbdefb; text-decoration: underline;">
      Donating
    </a>.
  </strong> This website is ad‑free and run by volunteers.
`;
  banner.appendChild(span);

  const button = document.createElement("button");
  button.innerText = "×";
  button.style = "background:none;border:none;color:inherit;font-size:1.5rem;cursor:pointer;";
  button.addEventListener("click", () => {
    banner.style.display = "none";
    document.cookie = "donation_banner_hidden=true; path=/; max-age=" + 60 * 60 * 24 * 2;// 2 days 
  });
  banner.appendChild(button);

  const content = document.querySelector("div.md-container"); // adjust to the correct parent container
  if (content && content.firstChild) {
    content.insertBefore(banner, content.firstChild);
  }
});
