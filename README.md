# Cub3D - A RayCaster Maze Engine

A dynamic 3D graphical maze engine built from scratch using ray-casting principles. Inspired by the legendary Wolfenstein 3D, this project demonstrates core computer graphics concepts including rendering pipelines, texture mapping, and collision detection.

**Language:** C | **Status:** Complete with Bonus Features ✅

## 🎮 Overview

Cub3D is a 42 school project that implements a first-person maze exploration experience using ray-casting algorithm. Navigate through textured 3D mazes, interact with doors, view a minimap, and experience smooth, responsive gameplay with collision detection.

### Key Features

**Mandatory:**
- ✅ Full 3D maze rendering using DDA ray-casting algorithm
- ✅ Directional textured walls (North, South, East, West)
- ✅ Customizable floor and ceiling colors
- ✅ Smooth WASD keyboard navigation + arrow key rotation
- ✅ `.cub` scene file format for dynamic map loading
- ✅ Proper memory management and error handling

**Bonus:**
- 🎯 Minimap system with ray visualization
- 💥 Wall collision detection
- 🖱️ Mouse-controlled camera rotation
- 🚪 Interactive door system
- 🎬 Animated sprite rendering

## 🏗️ Technical Highlights

**What I Learned:**
- Ray-casting fundamentals and DDA algorithm optimization
- X11 graphics programming with MinilibX
- Memory-safe C with 42 Norm compliance
- Complex data structures for spatial mapping
- Real-time rendering optimization techniques

## 🚀 Quick Start

### Requirements
- GCC compiler with `-Wall -Wextra -Werror`
- MinilibX (included)
- Linux/POSIX system

### Build & Run
```bash
# Compile
make

# Run with a map file
./cub3D maps/maptest.cub

# Compile with bonus features
make bonus
```

### Controls
| Key | Action |
|-----|--------|
| `W/A/S/D` | Move forward/left/backward/right |
| `←` `→` | Rotate view |
| `ESC` | Exit |
| `M` | Toggle mouse (bonus) |
| `R` | Show rays on minimap (bonus) |
| Mouse | Rotate camera (bonus) |

## 📂 Map Format

Maps are `.cub` files containing three sections:

**1. Textures** - Path to wall images:
```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
```

**2. Colors** - RGB values (0-255):
```
F 220,100,0      # Floor
C 225,30,0       # Ceiling
```

**3. Map** - Player spawn must be N/S/E/W, surrounded by walls (1), spaces (0):
```
111111
100101
101001
1100N1
111111
```

## 📚 Resources Used

- [Ray Casting Algorithm](https://lodev.org/cgtutor/raycasting.html) - Core implementation guide
- [MinilibX Documentation](https://github.com/42Paris/minilibx-linux)
- [42 Norm Standards](https://github.com/42School/42cursus)

## 📁 Project Structure

```
cub3D/
├── inc/              # Header files
├── src/
│   ├── main.c        # Entry point
│   ├── parsing/      # .cub file parsing
│   ├── raycast/      # Ray-casting engine
│   ├── render.c      # Pixel rendering
│   └── hooks.c       # Input handling
├── maps/             # Example maps
├── textures/         # XPM texture files
└── Makefile
```

## Developers

| [<img src="https://avatars.githubusercontent.com/u/54179576?v=4" width=115><br><sub>Cassiano Gross</sub>](https://github.com/Zorug) | [<img src="https://avatars.githubusercontent.com/u/159490163?v=4" width=115><br><sub>Ti</sub>](https://github.com/CreaTico6) |
| :---: | :---: |
