# SnakeMonGame 🎲🐍

> A hybrid of **Snakes & Ladders** and **Monopoly** — built with object-oriented C++

![C++](https://img.shields.io/badge/Language-C%2B%2B-blue?style=flat-square)
![OOP](https://img.shields.io/badge/Paradigm-OOP-green?style=flat-square)
![University](https://img.shields.io/badge/Cairo%20University-CMPG102-orange?style=flat-square)
![Semester](https://img.shields.io/badge/Fall-2024-purple?style=flat-square)

---

## Table of Contents

- [Overview](#overview)
- [How to Play](#how-to-play)
- [Game Modes](#game-modes)
- [Game Objects](#game-objects)
- [Card Types](#card-types)
- [Special Attacks (Bonus)](#special-attacks-bonus)
- [Architecture & Class Structure](#architecture--class-structure)
- [Building & Running](#building--running)
- [Grid File Format](#grid-file-format)

---

## Overview

SnakeMonGame is a turn-based board game played on a 10×10 grid. Players roll dice, climb ladders, slide down snakes, and land on event cards that can shift the game dramatically. The board is fully customizable — design your own grid in Design Mode before playing.

The entire project is implemented in C++ following strict object-oriented principles: inheritance, polymorphism, and virtual functions are used throughout. All input and output happens exclusively through a graphical window (CMU Graphics Library) — no console interaction whatsoever.

| Stat | Value |
|---|---|
| Players | 4 |
| Grid Size | 10×10 (100 cells) |
| Card Types | 13 |
| Starting Wallet | 100 coins |
| Special Attacks | 4 types |
| Game Modes | Design & Play |

---

## How to Play

### Setup
1. Launch the application — it opens in **Design Mode**.
2. Use the toolbar to place ladders, snakes, and cards anywhere on the board.
3. Save your grid, then switch to **Play Mode**.

### Turn Structure
Each turn, the active player must:
1. **Roll Dice** (random 1–6) or **Input Dice Value** (manual entry).
2. Move forward by the rolled number.
3. Resolve the landing cell — ladder, snake, or card effect is applied automatically.

### Wallet & Recharge
- Every player starts with **100 coins**.
- Every **3 turns**, instead of a penalty, the player receives a wallet recharge — or they may choose to launch a **special attack** instead.
- If a player's wallet hits 0, they are eliminated.

### Winning
The first player to reach or pass **cell 100** wins the game.

> **Note:** All input and output is handled exclusively through the graphical window. No console input is used at any point.

---

## Game Modes

### Design Mode — Board Editor
Used to build and customize the game board before playing.

| Action | Description |
|---|---|
| Add Ladder | Place a ladder with a start cell and end cell |
| Add Snake | Place a snake with a head cell and tail cell |
| Add Card | Place any of the 13 card types on a cell |
| Delete Game Object | Remove any object from a cell |
| Copy Card | Copy a card to the clipboard |
| Cut Card | Cut a card from a cell |
| Paste Card | Paste the clipboard card to another cell |
| Save Grid | Save the current board layout to a `.txt` file |
| Open Grid | Load a previously saved board from a file |
| Switch to Play Mode | Start a game session on the current board |

### Play Mode — Game Session
Used to actually play the game.

| Action | Description |
|---|---|
| Roll Dice | Generate a random dice value (1–6) and move |
| Input Dice Value | Manually enter a dice value and move |
| New Game | Reset all players and start a fresh session |
| Switch to Design Mode | Return to the board editor |

---

## Game Objects

### 🪜 Ladders
Defined by a **start cell** (lower) and an **end cell** (higher). When a player lands on the start cell, they immediately climb to the end cell — a lucky shortcut forward.

Validation ensures the end cell is above the start cell and that neither cell already contains another game object.

### 🐍 Snakes
Defined by a **head cell** (higher) and a **tail cell** (lower). Landing on the head cell causes the player to slide down to the tail — a painful setback.

### 🃏 Cards
Occupy a single cell. When a player lands on a card cell, its `Apply()` function is called and the effect is immediately applied to that player. Cards can be copied, cut, and pasted in Design Mode.

---

## Card Types

| Card | Name | Effect |
|---|---|---|
| **Card 1** | Wallet Deduct | Deducts a configurable coin amount from the player's wallet |
| **Card 2** | Wallet Credit | Adds a configurable coin amount to the player's wallet |
| **Card 3** | Next Ladder | Moves the player to the start of the nearest ladder ahead; nothing happens if none exists |
| **Card 4** | Next Snake | Moves the player to the head of the nearest snake ahead; nothing happens if none exists |
| **Card 5** | Bonus Roll | Player moves an additional number of cells equal to their last dice roll (double move) |
| **Card 6** | Penalty Roll | Player moves backward by the same number as their last dice roll |
| **Card 7** | Extra Turn | Grants the player an additional dice roll immediately |
| **Card 8** | Skip Turn | Prevents the player from rolling dice on their next turn |
| **Card 9** | Teleport | Moves the player to a designer-specified cell on the board |
| **Card 10** | Station (Blue) | Purchasable property — buy it or pay rent to the current owner |
| **Card 11** | Station (Green) | Same buy/rent mechanic as Card 10 with independent price & fee values |
| **Card 12** | Station (Yellow) | Same buy/rent mechanic as Card 10 with independent price & fee values |
| **Card 13** | Station (Red) | Same buy/rent mechanic as Card 10 with independent price & fee values |

> **Station Cards (10–13):** Price and fees are configured once per card type and shared across all cells of that type on the board. Landing on an unowned station lets you buy it; landing on an owned one deducts the fee from your wallet and pays it to the owner.

---

## Special Attacks (Bonus)

Every 3 turns, a player may launch a special attack instead of recharging their wallet. Each attack type may be used **at most twice** per player per game.

### ❄️ Ice
Choose a target player. That player is **frozen** and cannot roll dice on their next turn.

### 🔥 Fire
Choose a target player. They lose **20 coins per turn for 3 consecutive turns** (60 coins total).

### ☠️ Poison
Choose a target player. Their dice roll is **reduced by 1** for the next 5 turns.

### ⚡ Lightning
Instantly deducts **20 coins from all other players** simultaneously.

> A player denied from rolling (by Ice or Card 8) still takes their turn — it just passes with no movement.

---

## Architecture & Class Structure

The project follows a strict layered OOP design. Each class has a single, well-defined responsibility.

```
ApplicationManager
├── Grid
│   ├── Cell  ×100  (2D array, private)
│   │   ├── CellPosition
│   │   └── GameObject*  (base class pointer)
│   │       ├── Ladder
│   │       ├── Snake
│   │       └── Card  (base)
│   │           ├── CardOne  ...  CardThirteen
│   └── Player  ×4
├── Input
└── Output
```

### Class Responsibilities

| Class | Responsibility |
|---|---|
| `ApplicationManager` | Top-level controller — identifies action type, creates and executes the action object, then updates the GUI |
| `Grid` | Owns the `CellList` (10×10 array) and `PlayerList`. The **only** class that can iterate over cells directly |
| `Cell` | Holds a `CellPosition` and an optional `GameObject*` pointer |
| `CellPosition` | Encapsulates grid position as `vCell`, `hCell`, and cell number — no pixel coordinates |
| `Action` | Abstract base for every toolbar operation; derived classes override `ReadActionParameters()` and `Execute()` |
| `GameObject` | Abstract base for `Ladder`, `Snake`, and `Card`; provides virtual `Draw()`, `Save()`, `Load()`, `Apply()` |
| `Card` | Abstract base for all 13 card types; adds virtual `ReadCardParameters()` |
| `Player` | Tracks player number, step count, wallet, and current cell; owns the `Move()` logic |
| `Input` | **Only** class allowed to read from the GUI window |
| `Output` | **Only** class allowed to draw to the GUI window — toolbar, status bar, game objects, messages |

### Key Design Principles

- **Polymorphism everywhere** — `GameObject*` base pointers dispatch `Draw()`, `Save()`, and `Apply()` to the correct derived type automatically with no `dynamic_cast` abuse.
- **Single responsibility** — `Grid` loops and calls; it does not contain game logic. Logic lives inside each `GameObject` subclass.
- **No global variables** — all state is passed as function parameters or stored in class members.
- **No console I/O** — all input/output routes exclusively through `Input` and `Output` classes.

---

## Building & Running

### Requirements
- Windows OS
- Visual Studio 2012 or later
- CMU Graphics Library (bundled in `CMUgraphicsLib/`)

### Steps

1. **Open the solution** — open `PT-Project.vcxproj` in Visual Studio.

2. **Check the images folder** — ensure the `images/` folder is in the same directory as the compiled executable.

3. **Build & Run** — press `F5` (with debugging) or `Ctrl+F5` (without). The game window opens in Design Mode.

4. **Load a sample grid** *(optional)* — click **Open Grid** in the toolbar and select one of the provided `.txt` files to start with a pre-built board.

---

## Grid File Format

Grids are saved to and loaded from plain `.txt` files. The format has three sections: ladders, then snakes, then cards.

### Format Specification

```
<Number of Ladders>
<start_cell> <end_cell>
...

<Number of Snakes>
<head_cell> <tail_cell>
...

<Number of Cards>
<card_type> <cell> [parameters...]
...
```

### Example File

```
2           // 2 ladders
13 57       // ladder: start=13, end=57
6 39        // ladder: start=6,  end=39

2           // 2 snakes
97 31       // snake: head=97, tail=31
92 48       // snake: head=92, tail=48

5           // 5 cards
1 2 10      // Card1  at cell 2,  deduct amount = 10
1 20 12     // Card1  at cell 20, deduct amount = 12
2 15 30     // Card2  at cell 15, credit amount = 30
3 50        // Card3  at cell 50, no parameters
10 25 20 5  // Card10 at cell 25, price = 20, fees = 5
```

> Station cards (10–13) store price and fees **once** — all cells of the same card type on the board share those values automatically.

---

*Cairo University · Faculty of Engineering · Computer Engineering Department · CMPG102 · Fall 2024*
