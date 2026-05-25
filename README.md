# Mario Reflourished 🍄💫

An advanced, feature-rich 2D platformer built with modern **C++** and the **SFML (Simple and Fast Multimedia Library)**. *Mario Reflourished* reimagines the classic retro Super Mario Bros experience with custom visual enhancements, physics models, procedural endless generation, an interactive layout designer, and a highly decoupled, modular codebase leveraging industry-standard design patterns.

---

## 🎮 Game Modes

*Mario Reflourished* offers three distinct gameplay modes tailored to different playstyles:

*   **Adventure Mode (Standard Level Progression)**: Traverse handcrafted stages filled with pipes, underwater swimming zones, toxic lava pits, hidden coin stashes, portals, and intense boss battles.
*   **Endless Mode (Auto-Scrolling Challenge)**: Put your reflexes to the test! Survive in procedurally loaded chunks while outrunning a deadly, advancing **Spike Wall**. The camera and hazard speeds scale dynamically over time. Compete for high scores saved in your profile.
*   **Custom Level Editor**: Create, customize, and load your own game layouts. Perfect for players who love level design and sandbox testing.

---

## ✨ Special & Advanced Features

### 🌟 Playable Characters & Animated Skins
*   **Selectable Characters**: Toggle between **Mario** and **Luigi** in the Character Selection menu.
*   **Dynamic Visual Transformations**: Full state tracking for both characters (e.g., standard "Small" vs. "Super/Big" power-up versions) with dedicated animations for walking, jumping, swimming, and idle states.

### ⚡ Comprehensive Power-Up System
Equip unique power-ups, each with active status durations and unique UI indicators:
*   🍄 **Super Mushroom**: Doubles the player's physical size and enables breaking solid brick blocks.
*   🔥 **Fire Flower**: Equips the player to fire bouncing, lethal fireballs at enemies.
*   👟 **Air Sneakers**: Enhances agility by significantly increasing jump heights.
*   🧲 **Magnet**: Generates a gravitational pull that draws nearby coins directly to the player.
*   🛡️ **Shield**: Surrounds the player with a protective bubble granting total invincibility.
*   ☁️ **Flying Nimbus**: Unleashes full flight capability, allowing players to drift freely across obstacles.

### 👾 Diverse Enemies & Epic Boss Fights
*   **Minions**: Face retro classics like **Goombas**, **Koopas** (leaves a kickable and lethal shell upon defeat), pipe-emerging **Piranha Plants**, **Birds** (with calm and angry aggression states), and towering **Banzai Bills**.
*   **Bowser Boss**: The supreme arch-enemy that breaths fireballs and features complex attack triggers.
*   **Sun Wukong (The Monkey King)**: An epic custom boss battle. Sun Wukong utilizes a legendary **Magic Rod** which he spins, throws, and retrieves dynamically to attack the player.

### 🖼️ Camera, Audio, & Visual Polish
*   **Interactive Zoom & Aspect Ratio**: Scroll the mouse wheel to dynamically zoom the camera in and out. Features automatic aspect-ratio lock to avoid image distortion on window resizing.
*   **Context-Aware Dynamic Audio**: Audio seamlessly transitions in real-time. For example, submerged mechanics trigger underwater melodies, entering pipes triggers underground themes, and victory flags cue triumphant fanfares.
*   **Persistent High Score Tracking**: Supports individual player profiles, logins, and persistent files recording coin tallies, peak scores, and history.

---

## 🛠️ Architectural & Design Patterns Applied

The project is architected with a strict emphasis on clean code, loose coupling, and robust object-oriented patterns:

### 1. State Pattern (Game State Stack)
*   **Concept**: Manages scenes as distinct state classes inheriting from a common interface.
*   **Implementation**: `Game` uses a `std::vector<std::pair<std::unique_ptr<Scene>, bool>> states` stack. This manages distinct UI views (`Welcome`, `Login`, `SelectCharacter`, `Play`, `VictoryScene`, etc.) and seamlessly handles overlapping scenes (e.g., drawing the HUD or overlaying the `Pause` menu over an active level without losing context).

### 2. Factory Method Pattern
*   **Concept**: Encapsulates concrete object creation, separating structural instantiation from gameplay logic.
*   **Implementation**: 
    *   `EntityFactory`: Spawns character instances, custom power-up entities, projectiles, and diverse enemies dynamically.
    *   `TileFactory`: Instantiates structural map components (Water, Lava, LuckyBlocks, Pipes, Portals) based on coordinate markers.

### 3. Command Pattern
*   **Concept**: Decouples UI triggers from concrete system responses by wrapping requests as standalone objects.
*   **Implementation**: Interactive menu elements (`Button` class) aggregate a list of abstract `Command*` pointers (e.g., `changeSceneCommand`, `writeTextCommand`). Clicking a button executes the encapsulated commands without exposing scene logic to the button's layout code.

### 4. Flyweight Pattern (Resource Manager)
*   **Concept**: Minimizes RAM usage and prevents expensive file-I/O overhead by loading heavy assets once and sharing them globally.
*   **Implementation**: The `Resources` utility class manages global static maps for textures, sound buffers, fonts, and active sounds. Entities access shared references to these resources instead of loading duplicate assets into memory.

### 5. Interpreter Pattern (Color-Based Level Parser)
*   **Concept**: Levels are designed visually as standard `.png` images, where individual pixel colors act as symbols representing game objects.
*   **Implementation**: The `Map` constructor parses map images pixel-by-pixel. It reads each pixel's RGBA integer value, resolves the symbol via `ColorManager::getObject`, and automatically triggers `TileFactory` or `EntityFactory` to assemble the interactive game board.

### 6. Template Method Pattern
*   **Concept**: Establishes an algorithm skeleton in a base class, allowing subclasses to override specific steps without modifying core loops.
*   **Implementation**: `EndlessMode` inherits from `AdventureMode`. It reuses the overarching entity management, rendering pipelines, and input updates of the adventure level, but injects custom procedurally generated maps and autonomous spike-wall scrolling physics.

### 7. Spatial Partitioning & View Culling
*   **Concept**: Boosts rendering performance by skipping rendering routines for objects currently off-screen.
*   **Implementation**: Inside `Map::render`, the engine calculates the distance between each tile and the camera center. Only tiles within a predetermined `RENDER_DISTANCE` are submitted to SFML's rendering context, preserving high frame rates (FPS).

---

## 🎨 Color-Based Level Design Guide

Levels are generated directly from 2D pixel drawings. To design or edit a level, open any map PNG (located in `Resources/Maps/`) using a pixel art editor (e.g., Paint.NET, Aseprite, Photoshop) and draw pixels using the following exact color mappings:

| Tile / Entity Type | RGBA Color Key | Hex Code | Description |
| :--- | :--- | :--- | :--- |
| **Ground Block** | `(105, 27, 34, 255)` | `#691B22` | Standard solid ground tile |
| **Brick Block** | `(212, 102, 47, 255)` | `#D4662F` | Breakable block (Super size required) |
| **Lucky Block** | `(255, 151, 87, 255)` | `#FF9757` | Item block containing coins/power-ups |
| **Solid Block** | `(156, 52, 26, 255)` | `#9C341A` | Unbreakable metal/stone block |
| **Pipe** | `(34, 177, 76, 255)` | `#22B14C` | Green pipeline entrance |
| **Pipe Destination**| `(53, 247, 106, 255)` | `#35F76A` | Portal exit endpoint for pipelines |
| **Lava Below** | `(237, 28, 36, 255)` | `#ED1C24` | Fatal liquid hazard (sub-surface) |
| **Lava Surface** | `(200, 28, 36, 255)` | `#C81C24` | Fluid lava top |
| **Water Below** | `(3, 169, 244, 255)` | `#03A9F4` | Swim-enabled water volume |
| **Water Surface** | `(100, 169, 244, 255)`| `#64A9F4` | Swim surface |
| **Barrier** | `(0, 0, 0, 255)` | `#000000` | Invisible barrier block |
| **Enemy Barrier** | `(255, 255, 255, 255)`| `#FFFFFF` | Invisible boundary block for enemy patrolling |
| **Goomba** | `(255, 128, 0, 255)` | `#FF8000` | Patrol enemy spawn point |
| **Koopa** | `(64, 128, 64, 255)` | `#408040` | Turtle enemy spawn point |
| **Bird** | `(200, 250, 100, 255)`| `#C8FA64` | Flying bird enemy spawn point |
| **Bowser** | `(145, 23, 228, 255)`| `#9117E4` | Boss Bowser spawn point |
| **Wukong** | `(255, 100, 200, 255)`| `#FF64C8` | Boss Wukong spawn point |
| **Coin** | `(255, 235, 59, 255)`| `#FFEB3B` | Floating coin collectable |
| **Player** | `(255, 0, 0, 255)` | `#FF0000` | Starting player spawn location |
| **Victory Flag** | `(100, 100, 100, 255)`| `#646464` | Level completion flag |

---

## ⌨️ Controls

Configure your inputs during gameplay:

| Key / Mouse Action | Action |
| :--- | :--- |
| **`A` / `Left Arrow`** | Move Left |
| **`D` / `Right Arrow`** | Move Right |
| **`W` / `Space`** | Jump / Swim Upward |
| **`S` / `Down Arrow`** | Enter Pipe (when standing on one) / Dive |
| **`J` / `Left Click`** | Shoot Fireball (when Fire Flower is active) |
| **`Esc`** | Pause / Resume Game |
| **`Mouse Wheel Scroll`**| Zoom View In / Out |
| **`Middle Mouse Click`**| Reset View Zoom Level |

---

## 🚀 Installation & Build Guide

The project is configured for compilation under **Visual Studio (MSVC)** on **Windows** platforms.

### Prerequisites
1. **IDE**: [Visual Studio 2019/2022](https://visualstudio.microsoft.com/) with C++ Desktop Development workload installed.
2. **Graphics Library**: SFML 2.5.1 (Visual C++ 15 MSVC 2017) or compatible binary libraries. 
   > *Note: Precompiled DLL files are already provided in the repository root directory for swift configuration.*

### Compilation Steps

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/Luke23127006/Mario-Reflourished.git
   cd Mario-Reflourished
   ```

2. **Open the Solution**:
   * Double-click `Mario Reflourished.sln` to open the project in Visual Studio.

3. **Configure Project Settings**:
   * Set the active solution platform to **x64** in the top toolbar.
   * Set the active configuration to **Release** (recommended for optimized framerates) or **Debug**.

4. **Link SFML (if not automated)**:
   * Right-click the project `Mario Reflourished` in the Solution Explorer $\rightarrow$ Select **Properties**.
   * Under **C/C++** $\rightarrow$ **General**, ensure **Additional Include Directories** points to your local SFML `include/` directory.
   * Under **Linker** $\rightarrow$ **General**, ensure **Additional Library Directories** points to your local SFML `lib/` directory.
   * Under **Linker** $\rightarrow$ **Input**, check that **Additional Dependencies** contains the required library binaries:
     * *Release*: `sfml-graphics.lib; sfml-window.lib; sfml-system.lib; sfml-audio.lib; sfml-network.lib;`
     * *Debug*: `sfml-graphics-d.lib; sfml-window-d.lib; sfml-system-d.lib; sfml-audio-d.lib; sfml-network-d.lib;`

5. **Run the Game**:
   * Press `F5` (or click **Local Windows Debugger**) to compile, link, and launch the application!