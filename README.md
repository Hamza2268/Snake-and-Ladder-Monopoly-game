<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>SnakeMonGame — README</title>
<link href="https://fonts.googleapis.com/css2?family=Syne:wght@400;600;700;800&family=DM+Mono:wght@400;500&family=Lora:ital,wght@0,400;0,500;1,400&display=swap" rel="stylesheet">
<style>
  *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }

  :root {
    --bg: #0f0e0c;
    --bg2: #181714;
    --bg3: #211f1b;
    --surface: #252320;
    --surface2: #2e2b27;
    --border: rgba(255,255,255,0.08);
    --border2: rgba(255,255,255,0.14);
    --text: #f0ebe3;
    --text2: #a89e90;
    --text3: #6b6358;
    --accent: #e8a84c;
    --accent2: #c97b2e;
    --accent-dim: rgba(232,168,76,0.12);
    --accent-dim2: rgba(232,168,76,0.06);
    --green: #5cba7a;
    --green-dim: rgba(92,186,122,0.12);
    --red: #d96060;
    --red-dim: rgba(217,96,96,0.12);
    --blue: #6aafdf;
    --blue-dim: rgba(106,175,223,0.12);
    --purple: #9b81d9;
    --purple-dim: rgba(155,129,217,0.12);
    --radius: 10px;
    --radius-lg: 16px;
  }

  html { scroll-behavior: smooth; }

  body {
    background: var(--bg);
    color: var(--text);
    font-family: 'Lora', Georgia, serif;
    font-size: 16px;
    line-height: 1.75;
    min-height: 100vh;
  }

  /* ── HEADER ── */
  header {
    position: relative;
    padding: 5rem 2rem 4rem;
    text-align: center;
    border-bottom: 1px solid var(--border);
    overflow: hidden;
  }
  header::before {
    content: '';
    position: absolute;
    inset: 0;
    background:
      radial-gradient(ellipse 60% 50% at 20% 30%, rgba(232,168,76,0.07) 0%, transparent 70%),
      radial-gradient(ellipse 50% 60% at 80% 70%, rgba(92,186,122,0.05) 0%, transparent 70%),
      repeating-linear-gradient(0deg, transparent, transparent 39px, rgba(255,255,255,0.02) 40px),
      repeating-linear-gradient(90deg, transparent, transparent 39px, rgba(255,255,255,0.02) 40px);
    pointer-events: none;
  }
  .badge-row {
    display: flex;
    gap: 8px;
    justify-content: center;
    flex-wrap: wrap;
    margin-bottom: 1.5rem;
  }
  .badge {
    font-family: 'DM Mono', monospace;
    font-size: 11px;
    padding: 4px 10px;
    border-radius: 100px;
    border: 1px solid;
    letter-spacing: 0.04em;
    text-transform: uppercase;
  }
  .badge-amber { color: var(--accent); border-color: rgba(232,168,76,0.3); background: var(--accent-dim2); }
  .badge-green { color: var(--green); border-color: rgba(92,186,122,0.3); background: var(--green-dim); }
  .badge-blue  { color: var(--blue);  border-color: rgba(106,175,223,0.3); background: var(--blue-dim); }
  .badge-purple{ color: var(--purple);border-color: rgba(155,129,217,0.3); background: var(--purple-dim); }

  h1.hero {
    font-family: 'Syne', sans-serif;
    font-size: clamp(2.8rem, 7vw, 5.2rem);
    font-weight: 800;
    letter-spacing: -0.03em;
    line-height: 1.05;
    color: var(--text);
    margin-bottom: 0.6rem;
  }
  h1.hero span { color: var(--accent); }
  .tagline {
    font-family: 'Lora', serif;
    font-style: italic;
    font-size: 1.15rem;
    color: var(--text2);
    max-width: 520px;
    margin: 0 auto 2rem;
  }
  .course-tag {
    display: inline-block;
    font-family: 'DM Mono', monospace;
    font-size: 12px;
    color: var(--text3);
    letter-spacing: 0.08em;
    text-transform: uppercase;
  }

  /* ── LAYOUT ── */
  .container {
    max-width: 900px;
    margin: 0 auto;
    padding: 0 2rem;
  }

  /* ── NAV ── */
  nav {
    position: sticky;
    top: 0;
    z-index: 100;
    background: rgba(15,14,12,0.92);
    backdrop-filter: blur(12px);
    border-bottom: 1px solid var(--border);
    padding: 0 2rem;
  }
  nav ul {
    display: flex;
    list-style: none;
    gap: 0;
    max-width: 900px;
    margin: 0 auto;
    overflow-x: auto;
  }
  nav ul::-webkit-scrollbar { display: none; }
  nav a {
    display: block;
    padding: 0.85rem 1.1rem;
    font-family: 'DM Mono', monospace;
    font-size: 12px;
    text-transform: uppercase;
    letter-spacing: 0.06em;
    color: var(--text3);
    text-decoration: none;
    white-space: nowrap;
    border-bottom: 2px solid transparent;
    transition: color 0.2s, border-color 0.2s;
  }
  nav a:hover { color: var(--accent); border-bottom-color: var(--accent); }

  /* ── SECTIONS ── */
  section {
    padding: 4rem 0;
    border-bottom: 1px solid var(--border);
  }
  section:last-child { border-bottom: none; }

  h2 {
    font-family: 'Syne', sans-serif;
    font-size: 1.65rem;
    font-weight: 700;
    color: var(--text);
    margin-bottom: 1.5rem;
    letter-spacing: -0.02em;
    display: flex;
    align-items: center;
    gap: 0.6rem;
  }
  h2 .h2-icon {
    width: 28px;
    height: 28px;
    border-radius: 6px;
    display: flex;
    align-items: center;
    justify-content: center;
    font-size: 14px;
    flex-shrink: 0;
  }
  h3 {
    font-family: 'Syne', sans-serif;
    font-size: 1.05rem;
    font-weight: 600;
    color: var(--text);
    margin-bottom: 0.75rem;
    letter-spacing: -0.01em;
  }
  p { color: var(--text2); margin-bottom: 1rem; }
  p:last-child { margin-bottom: 0; }

  /* ── OVERVIEW GRID ── */
  .overview-grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
    gap: 1px;
    background: var(--border);
    border: 1px solid var(--border);
    border-radius: var(--radius-lg);
    overflow: hidden;
    margin-bottom: 2rem;
  }
  .ov-cell {
    background: var(--bg2);
    padding: 1.25rem 1.5rem;
    transition: background 0.2s;
  }
  .ov-cell:hover { background: var(--surface); }
  .ov-num {
    font-family: 'Syne', sans-serif;
    font-size: 2rem;
    font-weight: 800;
    color: var(--accent);
    line-height: 1;
    margin-bottom: 0.3rem;
  }
  .ov-label {
    font-family: 'DM Mono', monospace;
    font-size: 11px;
    text-transform: uppercase;
    letter-spacing: 0.08em;
    color: var(--text3);
  }

  /* ── CARD GRID ── */
  .card-grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(260px, 1fr));
    gap: 12px;
    margin: 1.5rem 0;
  }
  .card {
    background: var(--bg2);
    border: 1px solid var(--border);
    border-radius: var(--radius-lg);
    padding: 1.25rem 1.4rem;
    transition: border-color 0.2s, background 0.2s;
  }
  .card:hover { border-color: var(--border2); background: var(--surface); }
  .card-icon {
    width: 36px;
    height: 36px;
    border-radius: 8px;
    display: flex;
    align-items: center;
    justify-content: center;
    font-size: 16px;
    margin-bottom: 0.8rem;
  }
  .ci-amber { background: var(--accent-dim); }
  .ci-green  { background: var(--green-dim); }
  .ci-red    { background: var(--red-dim); }
  .ci-blue   { background: var(--blue-dim); }
  .ci-purple { background: var(--purple-dim); }

  /* ── CARDS TABLE ── */
  .cards-table {
    width: 100%;
    border-collapse: collapse;
    margin: 1.5rem 0;
    font-size: 14px;
  }
  .cards-table th {
    font-family: 'DM Mono', monospace;
    font-size: 11px;
    text-transform: uppercase;
    letter-spacing: 0.08em;
    color: var(--text3);
    text-align: left;
    padding: 0.5rem 0.75rem;
    border-bottom: 1px solid var(--border);
  }
  .cards-table td {
    padding: 0.7rem 0.75rem;
    color: var(--text2);
    border-bottom: 1px solid var(--border);
    vertical-align: top;
  }
  .cards-table tr:last-child td { border-bottom: none; }
  .cards-table tr:hover td { background: var(--surface); }
  .card-num {
    font-family: 'DM Mono', monospace;
    font-size: 12px;
    font-weight: 500;
    background: var(--accent-dim);
    color: var(--accent);
    border: 1px solid rgba(232,168,76,0.2);
    border-radius: 6px;
    padding: 2px 8px;
    white-space: nowrap;
  }

  /* ── CODE BLOCK ── */
  pre {
    background: var(--bg3);
    border: 1px solid var(--border);
    border-radius: var(--radius);
    padding: 1.25rem 1.5rem;
    overflow-x: auto;
    margin: 1rem 0;
  }
  code {
    font-family: 'DM Mono', monospace;
    font-size: 13px;
    color: var(--accent);
    line-height: 1.6;
  }
  p code, li code {
    background: var(--surface);
    border: 1px solid var(--border);
    border-radius: 4px;
    padding: 1px 6px;
    font-size: 13px;
    color: var(--accent);
  }

  /* ── FILE FORMAT ── */
  .file-block {
    background: var(--bg3);
    border: 1px solid var(--border);
    border-left: 3px solid var(--accent);
    border-radius: var(--radius);
    padding: 1.25rem 1.5rem;
    margin: 1.25rem 0;
    font-family: 'DM Mono', monospace;
    font-size: 13px;
    color: var(--text2);
    line-height: 1.8;
    white-space: pre;
    overflow-x: auto;
  }
  .file-block .comment { color: var(--text3); }
  .file-block .num { color: var(--accent); }

  /* ── STEPS ── */
  .steps {
    display: flex;
    flex-direction: column;
    gap: 0;
    margin: 1.5rem 0;
  }
  .step {
    display: flex;
    gap: 1.2rem;
    padding: 1.25rem 0;
    border-bottom: 1px solid var(--border);
    align-items: flex-start;
  }
  .step:last-child { border-bottom: none; }
  .step-num {
    font-family: 'Syne', sans-serif;
    font-size: 1rem;
    font-weight: 800;
    color: var(--accent);
    background: var(--accent-dim);
    border: 1px solid rgba(232,168,76,0.2);
    width: 34px;
    height: 34px;
    border-radius: 50%;
    display: flex;
    align-items: center;
    justify-content: center;
    flex-shrink: 0;
    margin-top: 2px;
  }
  .step-body h3 { margin-bottom: 0.3rem; }
  .step-body p { margin-bottom: 0; }

  /* ── MODE SPLIT ── */
  .mode-split {
    display: grid;
    grid-template-columns: 1fr 1fr;
    gap: 12px;
    margin: 1.5rem 0;
  }
  @media (max-width: 640px) { .mode-split { grid-template-columns: 1fr; } }
  .mode-box {
    border-radius: var(--radius-lg);
    padding: 1.5rem;
    border: 1px solid var(--border);
  }
  .mode-design { background: linear-gradient(135deg, var(--blue-dim) 0%, var(--bg2) 100%); }
  .mode-play   { background: linear-gradient(135deg, var(--green-dim) 0%, var(--bg2) 100%); }
  .mode-label {
    font-family: 'DM Mono', monospace;
    font-size: 11px;
    text-transform: uppercase;
    letter-spacing: 0.1em;
    margin-bottom: 0.75rem;
  }
  .lbl-blue   { color: var(--blue); }
  .lbl-green  { color: var(--green); }
  .mode-box ul {
    list-style: none;
    display: flex;
    flex-direction: column;
    gap: 0.4rem;
  }
  .mode-box li {
    font-size: 14px;
    color: var(--text2);
    padding-left: 1rem;
    position: relative;
  }
  .mode-box li::before {
    content: '→';
    position: absolute;
    left: 0;
    color: var(--text3);
  }

  /* ── BONUS TABLE ── */
  .bonus-grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(190px, 1fr));
    gap: 10px;
    margin: 1.25rem 0;
  }
  .bonus-card {
    background: var(--bg2);
    border: 1px solid var(--border);
    border-radius: var(--radius);
    padding: 1rem 1.1rem;
    position: relative;
    overflow: hidden;
  }
  .bonus-card::before {
    content: '';
    position: absolute;
    top: 0; left: 0; right: 0;
    height: 2px;
  }
  .bc-ice::before    { background: var(--blue); }
  .bc-fire::before   { background: var(--red); }
  .bc-poison::before { background: var(--green); }
  .bc-lightning::before { background: var(--accent); }
  .bonus-title {
    font-family: 'Syne', sans-serif;
    font-weight: 700;
    font-size: 14px;
    margin-bottom: 0.3rem;
  }
  .bt-ice       { color: var(--blue); }
  .bt-fire      { color: var(--red); }
  .bt-poison    { color: var(--green); }
  .bt-lightning { color: var(--accent); }
  .bonus-desc   { font-size: 13px; color: var(--text2); line-height: 1.5; }

  /* ── STRUCTURE ── */
  .struct-grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(180px, 1fr));
    gap: 8px;
    margin: 1.25rem 0;
  }
  .struct-item {
    background: var(--bg2);
    border: 1px solid var(--border);
    border-radius: var(--radius);
    padding: 0.85rem 1rem;
  }
  .struct-class {
    font-family: 'DM Mono', monospace;
    font-size: 13px;
    color: var(--accent);
    font-weight: 500;
    margin-bottom: 0.2rem;
  }
  .struct-desc {
    font-size: 12px;
    color: var(--text3);
    line-height: 1.4;
  }

  /* ── ALERT ── */
  .alert {
    border-radius: var(--radius);
    padding: 1rem 1.25rem;
    margin: 1.25rem 0;
    font-size: 14px;
    color: var(--text2);
    display: flex;
    gap: 0.75rem;
    align-items: flex-start;
    border: 1px solid;
  }
  .alert-amber { background: var(--accent-dim2); border-color: rgba(232,168,76,0.2); }
  .alert-green { background: var(--green-dim); border-color: rgba(92,186,122,0.2); }
  .alert-icon { font-size: 16px; flex-shrink: 0; margin-top: 1px; }

  /* ── FOOTER ── */
  footer {
    padding: 2.5rem 2rem;
    text-align: center;
    border-top: 1px solid var(--border);
    font-family: 'DM Mono', monospace;
    font-size: 12px;
    color: var(--text3);
    letter-spacing: 0.04em;
  }
  footer span { color: var(--accent); }

  /* ── RESPONSIVE ── */
  @media (max-width: 600px) {
    .overview-grid { grid-template-columns: 1fr 1fr; }
    h1.hero { font-size: 2.4rem; }
  }
</style>
</head>
<body>

<!-- HEADER -->
<header>
  <div class="badge-row">
    <span class="badge badge-amber">C++</span>
    <span class="badge badge-green">OOP</span>
    <span class="badge badge-blue">Cairo University</span>
    <span class="badge badge-purple">CMPG102 · Fall 2024</span>
  </div>
  <h1 class="hero">Snake<span>Mon</span>Game</h1>
  <p class="tagline">A hybrid of Snakes &amp; Ladders and Monopoly — built with object-oriented C++</p>
  <span class="course-tag">Programming Techniques · Phase 2</span>
</header>

<!-- STICKY NAV -->
<nav>
  <ul>
    <li><a href="#overview">Overview</a></li>
    <li><a href="#how-to-play">How to Play</a></li>
    <li><a href="#modes">Game Modes</a></li>
    <li><a href="#cards">Cards</a></li>
    <li><a href="#objects">Game Objects</a></li>
    <li><a href="#bonus">Bonus Attacks</a></li>
    <li><a href="#architecture">Architecture</a></li>
    <li><a href="#build">Build</a></li>
    <li><a href="#file-format">File Format</a></li>
  </ul>
</nav>

<div class="container">

  <!-- OVERVIEW -->
  <section id="overview">
    <h2>
      <span class="h2-icon ci-amber" style="background:var(--accent-dim);">◈</span>
      Overview
    </h2>
    <p>
      SnakeMonGame is a turn-based board game that merges the classic Snakes &amp; Ladders mechanic with Monopoly-style property and event cards. Up to four players compete on a 10×10 grid, rolling dice, climbing ladders, dodging snakes, and landing on special cards that can flip the game at any moment.
    </p>
    <p>
      The project is implemented in C++ using object-oriented design principles including inheritance, polymorphism, and virtual functions. A graphical window (CMU Graphics Library) handles all input and output — no console interaction at all.
    </p>

    <div class="overview-grid">
      <div class="ov-cell">
        <div class="ov-num">4</div>
        <div class="ov-label">Players</div>
      </div>
      <div class="ov-cell">
        <div class="ov-num">100</div>
        <div class="ov-label">Grid Cells</div>
      </div>
      <div class="ov-cell">
        <div class="ov-num">13</div>
        <div class="ov-label">Card Types</div>
      </div>
      <div class="ov-cell">
        <div class="ov-num">4</div>
        <div class="ov-label">Special Attacks</div>
      </div>
      <div class="ov-cell">
        <div class="ov-num">2</div>
        <div class="ov-label">Game Modes</div>
      </div>
      <div class="ov-cell">
        <div class="ov-num">100</div>
        <div class="ov-label">Starting Wallet</div>
      </div>
    </div>
  </section>

  <!-- HOW TO PLAY -->
  <section id="how-to-play">
    <h2>
      <span class="h2-icon ci-green" style="background:var(--green-dim);">▶</span>
      How to Play
    </h2>
    <p>The game runs through two phases: first you design the board, then you play on it.</p>

    <div class="steps">
      <div class="step">
        <div class="step-num">1</div>
        <div class="step-body">
          <h3>Design your grid</h3>
          <p>Switch to Design Mode and use the toolbar to place ladders, snakes, and event cards anywhere on the 10×10 board. Save the grid to a file once satisfied.</p>
        </div>
      </div>
      <div class="step">
        <div class="step-num">2</div>
        <div class="step-body">
          <h3>Start a game</h3>
          <p>Switch to Play Mode. Four players begin at cell 1 with a wallet of 100 coins and a step count of 0.</p>
        </div>
      </div>
      <div class="step">
        <div class="step-num">3</div>
        <div class="step-body">
          <h3>Take your turn</h3>
          <p>On each turn, click <em>Roll Dice</em> (random 1–6) or <em>Input Dice Value</em> to enter a number manually. Your player moves forward that many cells.</p>
        </div>
      </div>
      <div class="step">
        <div class="step-num">4</div>
        <div class="step-body">
          <h3>Land on a cell</h3>
          <p>If the cell contains a ladder, climb to its top. If it contains a snake, slide to its tail. If it contains a card, the card's effect is applied immediately.</p>
        </div>
      </div>
      <div class="step">
        <div class="step-num">5</div>
        <div class="step-body">
          <h3>Recharge your wallet</h3>
          <p>Every 3 turns, instead of a penalty you receive a wallet recharge — or you may choose to launch a special attack on another player instead.</p>
        </div>
      </div>
      <div class="step">
        <div class="step-num">6</div>
        <div class="step-body">
          <h3>Win the game</h3>
          <p>The first player to reach or pass cell 100 wins. If a player's wallet reaches 0, they are eliminated.</p>
        </div>
      </div>
    </div>

    <div class="alert alert-amber">
      <span class="alert-icon">⚑</span>
      <span>All game input and output happens exclusively through the graphical window. No console input is used at any point.</span>
    </div>
  </section>

  <!-- GAME MODES -->
  <section id="modes">
    <h2>
      <span class="h2-icon ci-blue" style="background:var(--blue-dim);">⊞</span>
      Game Modes
    </h2>
    <p>The application operates in two distinct modes, switchable from the toolbar.</p>

    <div class="mode-split">
      <div class="mode-box mode-design">
        <div class="mode-label lbl-blue">Design Mode</div>
        <h3 style="color: var(--blue); margin-bottom: 0.6rem;">Board Editor</h3>
        <ul>
          <li>Add Ladder</li>
          <li>Add Snake</li>
          <li>Add Card (all 13 types)</li>
          <li>Delete Game Object</li>
          <li>Copy Card</li>
          <li>Cut Card</li>
          <li>Paste Card</li>
          <li>Save Grid to file</li>
          <li>Open Grid from file</li>
          <li>Switch to Play Mode</li>
        </ul>
      </div>
      <div class="mode-box mode-play">
        <div class="mode-label lbl-green">Play Mode</div>
        <h3 style="color: var(--green); margin-bottom: 0.6rem;">Game Session</h3>
        <ul>
          <li>Roll Dice (random)</li>
          <li>Input Dice Value (manual)</li>
          <li>New Game (reset)</li>
          <li>Player movement &amp; wallet</li>
          <li>Ladder &amp; Snake effects</li>
          <li>Card effects on landing</li>
          <li>Every-3-turns recharge</li>
          <li>Special attacks</li>
          <li>Switch back to Design</li>
        </ul>
      </div>
    </div>
  </section>

  <!-- CARDS -->
  <section id="cards">
    <h2>
      <span class="h2-icon ci-purple" style="background:var(--purple-dim);">♠</span>
      Card Types
    </h2>
    <p>Cards are placed on cells during design mode. When a player lands on a card cell during play, its effect is applied immediately. There are 13 unique card types.</p>

    <table class="cards-table">
      <thead>
        <tr>
          <th>Card</th>
          <th>Name</th>
          <th>Effect</th>
        </tr>
      </thead>
      <tbody>
        <tr>
          <td><span class="card-num">01</span></td>
          <td>Wallet Deduct</td>
          <td>Deducts a configurable coin amount from the player's wallet.</td>
        </tr>
        <tr>
          <td><span class="card-num">02</span></td>
          <td>Wallet Credit</td>
          <td>Adds a configurable coin amount to the player's wallet.</td>
        </tr>
        <tr>
          <td><span class="card-num">03</span></td>
          <td>Next Ladder</td>
          <td>Moves the player to the start of the nearest ladder ahead. If none exists, nothing happens.</td>
        </tr>
        <tr>
          <td><span class="card-num">04</span></td>
          <td>Next Snake</td>
          <td>Moves the player to the head of the nearest snake ahead. If none exists, nothing happens.</td>
        </tr>
        <tr>
          <td><span class="card-num">05</span></td>
          <td>Bonus Roll</td>
          <td>Player moves an additional number of cells equal to their last dice roll (double move).</td>
        </tr>
        <tr>
          <td><span class="card-num">06</span></td>
          <td>Penalty Roll</td>
          <td>Player moves backward by the same number as their last dice roll.</td>
        </tr>
        <tr>
          <td><span class="card-num">07</span></td>
          <td>Extra Turn</td>
          <td>Grants the player an additional dice roll immediately.</td>
        </tr>
        <tr>
          <td><span class="card-num">08</span></td>
          <td>Skip Next Turn</td>
          <td>Prevents the player from rolling dice on their next turn.</td>
        </tr>
        <tr>
          <td><span class="card-num">09</span></td>
          <td>Teleport</td>
          <td>Moves the player directly to a designer-specified cell on the board.</td>
        </tr>
        <tr>
          <td><span class="card-num">10</span></td>
          <td>Station (Blue)</td>
          <td>Purchasable property. Land on it — buy it or pay rent to the owner.</td>
        </tr>
        <tr>
          <td><span class="card-num">11</span></td>
          <td>Station (Green)</td>
          <td>Same purchase/rent mechanic as Card 10 with independent price &amp; fee settings.</td>
        </tr>
        <tr>
          <td><span class="card-num">12</span></td>
          <td>Station (Yellow)</td>
          <td>Same purchase/rent mechanic as Card 10 with independent price &amp; fee settings.</td>
        </tr>
        <tr>
          <td><span class="card-num">13</span></td>
          <td>Station (Red)</td>
          <td>Same purchase/rent mechanic as Card 10 with independent price &amp; fee settings.</td>
        </tr>
      </tbody>
    </table>

    <div class="alert alert-green">
      <span class="alert-icon">ℹ</span>
      <span>Station cards (10–13) share price and fees across all their cells — parameters are entered once and applied to every card of the same type on the board.</span>
    </div>
  </section>

  <!-- GAME OBJECTS -->
  <section id="objects">
    <h2>
      <span class="h2-icon ci-red" style="background:var(--red-dim);">⟜</span>
      Game Objects
    </h2>
    <div class="card-grid">
      <div class="card">
        <div class="card-icon ci-green">↑</div>
        <h3>Ladders</h3>
        <p>Defined by a start cell and an end cell (end must be higher). When a player lands on the start cell, they are immediately transported to the end cell — a lucky shortcut.</p>
        <p>Validated so start cells cannot already contain another game object and end must be above start.</p>
      </div>
      <div class="card">
        <div class="card-icon ci-red">↓</div>
        <h3>Snakes</h3>
        <p>Defined by a head cell (higher) and a tail cell (lower). Landing on the head sends the player sliding down to the tail — a dangerous setback.</p>
        <p>Similar validation ensures no conflicts with existing objects.</p>
      </div>
      <div class="card">
        <div class="card-icon ci-purple">♠</div>
        <h3>Cards</h3>
        <p>Occupy a single cell. When landed on, their <code>Apply()</code> virtual function is called automatically, producing the card's unique effect on the landing player.</p>
        <p>Cards can be copied, cut, and pasted to other cells in design mode.</p>
      </div>
    </div>
  </section>

  <!-- BONUS ATTACKS -->
  <section id="bonus">
    <h2>
      <span class="h2-icon ci-amber" style="background:var(--accent-dim);">⚡</span>
      Special Attacks (Bonus)
    </h2>
    <p>
      Every 3 turns, when a player would normally recharge their wallet, they may choose to launch a special attack instead. Each player has access to all four attacks, but can use each attack type at most <strong>twice</strong> per game.
    </p>

    <div class="bonus-grid">
      <div class="bonus-card bc-ice">
        <div class="bonus-title bt-ice">❄ Ice</div>
        <div class="bonus-desc">Choose a target player. That player is frozen and cannot roll dice on their next turn.</div>
      </div>
      <div class="bonus-card bc-fire">
        <div class="bonus-title bt-fire">🔥 Fire</div>
        <div class="bonus-desc">Choose a target player. They lose 20 coins per turn for 3 consecutive turns (60 total).</div>
      </div>
      <div class="bonus-card bc-poison">
        <div class="bonus-title bt-poison">☠ Poison</div>
        <div class="bonus-desc">Choose a target player. Their dice roll is reduced by 1 for 5 turns.</div>
      </div>
      <div class="bonus-card bc-lightning">
        <div class="bonus-title bt-lightning">⚡ Lightning</div>
        <div class="bonus-desc">Instantly deducts 20 coins from every other player simultaneously.</div>
      </div>
    </div>

    <div class="alert alert-amber">
      <span class="alert-icon">⚑</span>
      <span>A player who has been frozen (Ice) cannot roll on their next turn but still counts that turn. Poison and Fire effects persist across turns and are tracked per player.</span>
    </div>
  </section>

  <!-- ARCHITECTURE -->
  <section id="architecture">
    <h2>
      <span class="h2-icon ci-blue" style="background:var(--blue-dim);">⊙</span>
      Architecture &amp; Class Structure
    </h2>
    <p>The project strictly follows a layered object-oriented design. Each class has a single responsibility and communicates through well-defined interfaces.</p>

    <div class="struct-grid">
      <div class="struct-item">
        <div class="struct-class">ApplicationManager</div>
        <div class="struct-desc">Top-level controller. Identifies actions, creates action objects, executes them, and updates the GUI.</div>
      </div>
      <div class="struct-item">
        <div class="struct-class">Grid</div>
        <div class="struct-desc">Owns the 10×10 CellList and the 4 Player pointers. Only class that can loop over cells.</div>
      </div>
      <div class="struct-item">
        <div class="struct-class">Cell</div>
        <div class="struct-desc">Holds a CellPosition and an optional pointer to a GameObject.</div>
      </div>
      <div class="struct-item">
        <div class="struct-class">CellPosition</div>
        <div class="struct-desc">Represents grid position via vCell, hCell, and cell number. No real-pixel coordinates.</div>
      </div>
      <div class="struct-item">
        <div class="struct-class">Action (base)</div>
        <div class="struct-desc">Abstract base for every toolbar operation. Derived classes override ReadActionParameters() and Execute().</div>
      </div>
      <div class="struct-item">
        <div class="struct-class">GameObject (base)</div>
        <div class="struct-desc">Abstract base for Ladder, Snake, and Card. Provides virtual Draw(), Save(), Load(), Apply().</div>
      </div>
      <div class="struct-item">
        <div class="struct-class">Card (base)</div>
        <div class="struct-desc">Inherits GameObject. Base for all 13 card types with virtual ReadCardParameters() and Apply().</div>
      </div>
      <div class="struct-item">
        <div class="struct-class">Player</div>
        <div class="struct-desc">Tracks player number, step count, wallet, and current cell. Owns Move() logic.</div>
      </div>
      <div class="struct-item">
        <div class="struct-class">Input</div>
        <div class="struct-desc">Only class that reads from the GUI window. All input must route through here.</div>
      </div>
      <div class="struct-item">
        <div class="struct-class">Output</div>
        <div class="struct-desc">Only class that writes to the GUI window. Handles drawing, toolbar, status bar, and messages.</div>
      </div>
    </div>

    <div class="alert alert-amber">
      <span class="alert-icon">⚑</span>
      <span>Polymorphism is used throughout — GameObjects are stored as base-class pointers, and virtual functions dispatch to the correct derived implementation without any <code>dynamic_cast</code> abuse.</span>
    </div>
  </section>

  <!-- BUILD -->
  <section id="build">
    <h2>
      <span class="h2-icon ci-green" style="background:var(--green-dim);">▤</span>
      Building &amp; Running
    </h2>

    <h3>Requirements</h3>
    <p>Windows with Visual Studio (tested on VS 2012+). The project uses the CMU Graphics Library bundled inside <code>CMUgraphicsLib/</code>.</p>

    <h3>Steps</h3>
    <div class="steps">
      <div class="step">
        <div class="step-num">1</div>
        <div class="step-body">
          <h3>Open the solution</h3>
          <p>Open <code>PT-Project.vcxproj</code> in Visual Studio.</p>
        </div>
      </div>
      <div class="step">
        <div class="step-num">2</div>
        <div class="step-body">
          <h3>Ensure images folder is present</h3>
          <p>The <code>images/</code> folder must be in the same directory as the executable. Copy it from the project root if needed.</p>
        </div>
      </div>
      <div class="step">
        <div class="step-num">3</div>
        <div class="step-body">
          <h3>Build &amp; Run</h3>
          <p>Press <kbd>F5</kbd> (Start Debugging) or <kbd>Ctrl+F5</kbd> (Start Without Debugging). The game window will open in Design Mode.</p>
        </div>
      </div>
      <div class="step">
        <div class="step-num">4</div>
        <div class="step-body">
          <h3>Load a sample grid (optional)</h3>
          <p>Click <em>Open Grid</em> in the toolbar and select one of the provided <code>.txt</code> grid files to start with a pre-built board.</p>
        </div>
      </div>
    </div>
  </section>

  <!-- FILE FORMAT -->
  <section id="file-format">
    <h2>
      <span class="h2-icon ci-amber" style="background:var(--accent-dim);">⊟</span>
      Grid File Format
    </h2>
    <p>Grids are saved to and loaded from plain text files. The format is structured in three sections: ladders first, then snakes, then cards.</p>

    <div class="file-block"><span class="num">N_ladders</span>
<span class="comment">start_cell  end_cell    (repeated N_ladders times)</span>

<span class="num">N_snakes</span>
<span class="comment">head_cell  tail_cell   (repeated N_snakes times)</span>

<span class="num">N_cards</span>
<span class="comment">card_type  cell  [parameters...]  (repeated N_cards times)</span></div>

    <h3>Example file</h3>
    <div class="file-block"><span class="num">2</span>         <span class="comment">// 2 ladders</span>
13 57     <span class="comment">// ladder: start 13 → end 57</span>
6 39      <span class="comment">// ladder: start 6  → end 39</span>
<span class="num">2</span>         <span class="comment">// 2 snakes</span>
97 31     <span class="comment">// snake:  head 97 → tail 31</span>
92 48     <span class="comment">// snake:  head 92 → tail 48</span>
<span class="num">5</span>         <span class="comment">// 5 cards</span>
1 2 10    <span class="comment">// Card1 at cell 2,  wallet deduct = 10</span>
1 20 12   <span class="comment">// Card1 at cell 20, wallet deduct = 12</span>
2 15 30   <span class="comment">// Card2 at cell 15, wallet credit = 30</span>
3 50      <span class="comment">// Card3 at cell 50, no parameters</span>
10 25 20 5<span class="comment">// Card10 at cell 25, price = 20, fees = 5</span></div>

    <div class="alert alert-green">
      <span class="alert-icon">ℹ</span>
      <span>Station cards (10–13) only store their price and fees once per type. Subsequent cards of the same type on the board share those values automatically.</span>
    </div>
  </section>

</div>

<footer>
  SnakeMonGame · CMPG102 Fall 2024 · Cairo University · Faculty of Engineering
  <br><br>
  Built with <span>C++</span> and the CMU Graphics Library
</footer>

</body>
</html>
