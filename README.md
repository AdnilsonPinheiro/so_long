# so_long

A small 2D grid-based game where the player must collect all collectibles and reach the exit. This implementation follows the typical 42-school "so_long" project goals: read and validate a map file, render the map with MiniLibX, and support player movement and simple collision logic.

Badges
- Language: ![C](https://img.shields.io/badge/language-C-orange)
- Status: ![Status](https://img.shields.io/badge/status-completed-brightgreen)

## Demo

![so_long demo](assets/so_long_demo.gif)


## Table of contents
- [About](#about)
- [Features](#features)
- [Requirements](#requirements)
- [Map format](#map-format)
- [Controls](#controls)
- [Build & Run](#build--run)
- [Examples](#examples)
- [Testing & Validation](#testing--validation)
- [Development notes](#development-notes)
- [Contributing](#contributing)
- [License](#license)
- [Author](#author)
- [Contact](#contact)

## About
so_long is a compact project to practice low-level graphics, file parsing, and game logic in C. The program loads a rectangular map from a `.ber` file, validates it (walls, required elements), and runs a simple window where the player navigates to collect items and reach the exit.

This repo focuses on clarity, correctness, and portability across POSIX systems using gcc and the MiniLibX graphics library.

## Features
- Parse and validate map files (.ber)
- Render map tiles using MiniLibX
- Player movement with collision detection
- Collectibles counter and exit activation
- Move counter displayed in terminal
- Simple, dependency-free C code (aside from MiniLibX)

## Requirements
- POSIX-compatible OS (Linux or macOS)
- C compiler (gcc or clang)
- make
- MiniLibX (configured for your platform)

On Debian/Ubuntu you may need:
```bash
sudo apt-get install build-essential libx11-dev libxext-dev libbsd-dev
```
On macOS install MiniLibX via whatever method you use for your workflow.

## Map format
- File extension: `.ber`
- Map must be rectangular (all rows same length).
- Map must be surrounded by walls (`1`).
- Required elements:
  - Player: `P` (exactly one)
  - Exit: `E` (exactly one)
  - Collectibles: `C` (at least one)
- Walkable floor: `0`
- Example map:
```
111111
1P0C01
100001
1C0E11
111111
```

## Controls
- W / Up arrow: move up
- A / Left arrow: move left
- S / Down arrow: move down
- D / Right arrow: move right
- ESC / Window close: exit game

(Controls may vary slightly depending on your MiniLibX key mappings — see `key_hook` in the source.)

## Build & Run
Clone the repository, then build with the Makefile:

```bash
git clone https://github.com/AdnilsonPinheiro/so_long.git
cd so_long
make
```

Common Make targets:
- `make` — build the binary (usually `so_long`)
- `make clean` — remove object files
- `make fclean` — remove binary and object files
- `make re` — rebuild (fclean + all)
- `make test` — run a series of different maps on valgrind

Run the game with a map file:
```bash
./so_long maps/example.ber
```

If MiniLibX is not in a standard location, update the Makefile LDFLAGS/INCLUDES to point at your MiniLibX installation.

## Examples
Provided example maps are in the `maps/` directory. Try:
```bash
./so_long maps/level1.ber
```
Watch the terminal for the move counter or any validation errors printed at startup.

## Testing & Validation
- In this repository you will find a `test_script` and a `test_bonus` file, both of which run the program with the supplied maps on valgrind.
- The valgrind report of each run is then stored in a separate folder, allowing for easy checks for memory leaks.

## Development notes
- Split responsibilities: parsing/validation, rendering, input handling, and game logic.
- Keep memory ownership clear; free parsed maps and resources on exit.
- Test edge cases for map validation: non-rectangular maps, missing player/collectible/exit, open borders.
- If targeting the 42 norm, follow the project-specific style/headers.

## Contributing
Contributions and improvements are welcome. Suggested workflow:
1. Fork the repository
2. Create a branch: `git checkout -b feat/your-feature`
3. Add tests or maps for your change
4. Open a pull request describing the change

Please follow the repository coding conventions and include clear commit messages.

## License
This project is provided under the MIT License by default. Replace with another license if you prefer. See the LICENSE file for details.

## Author
- Adnilson Pinheiro — https://github.com/AdnilsonPinheiro

## Contact
For issues or improvements, open an issue or pull request on this repository.
