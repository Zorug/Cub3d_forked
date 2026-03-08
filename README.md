*This project has been created as part of the 42 curriculum by cgross-s, tnuno-mo*

# Cub3D - A RayCaster Maze Engine

## Description

Cub3D is a 42 school project that implements a dynamic 3D graphical representation of a maze from a first-person perspective using ray-casting principles. Inspired by the legendary Wolfenstein 3D (1992), this project demonstrates core graphics programming concepts including ray-casting algorithms, texture mapping, and real-time rendering.

### Objective

The goal of this project is to create an immersive first-person maze exploration experience using ray-casting. Players navigate through a textured 3D maze while learning fundamental computer graphics concepts and optimization techniques.

### Key Features

**Mandatory Features:**
- Full 3D maze rendering using ray-casting algorithm
- Textured walls with directional variations (North, South, East, West)
- Customizable floor and ceiling colors
- Smooth keyboard navigation (WASD movement + arrow key rotation)
- ESC key to exit cleanly
- `.cub` scene file format for map and configuration loading
- Proper error handling and memory management
- Compliance with 42 school C norm

**Bonus Features:**
- Minimap system with ray visualization
- Wall collision detection
- Mouse-controlled camera rotation
- Interactive door system
- Animated sprites

## Instructions

### Requirements

- CC compiler with `-Wall -Wextra -Werror` flags
- MinilibX graphics library (included in the project)
- Linux operating system
- POSIX-compliant system

### Compilation

```bash
make
```

To compile with bonus features:

```bash
make bonus
```

To clean up object files:

```bash
make clean
```

To remove all generated files:

```bash
make fclean
```

To recompile everything:

```bash
make re
```

### Execution

Run the program with a `.cub` map file as argument:

```bash
./cub3D maps/maptest.cub
```

### Map Format

Maps must be `.cub` files containing:

1. **Textures** - Path to wall textures for each direction:
   ```
   NO ./path/to/north_texture.xpm
   SO ./path/to/south_texture.xpm
   WE ./path/to/west_texture.xpm
   EA ./path/to/east_texture.xpm
   ```

2. **Colors** - RGB values for floor and ceiling:
   ```
   F 220,100,0
   C 225,30,0
   ```

3. **Map** - Must be surrounded by walls (1), contain empty spaces (0), and exactly one player spawn point (N/S/E/W):
   ```
   111111
   100101
   101001
   1100N1
   111111
   ```

### Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `A` | Strafe left |
| `S` | Move backward |
| `D` | Strafe right |
| `←` `→` | Look left/right |
| `ESC` | Exit program |
| `M` | Toggle mouse cursor (bonus) |
| `R` | Toggle ray visualization on minimap (bonus) |
| Mouse | Rotate camera (bonus) |

## Resources

### Ray-Casting Theory

- [Ray Casting Algorithm Overview](https://en.wikipedia.org/wiki/Ray_casting) - Wikipedia article explaining the fundamentals
- [Lodev.org Ray-Casting Tutorial](https://lodev.org/cgtutor/raycasting.html) - Comprehensive ray-casting implementation guide
- [Wolfenstein 3D Postmortem](https://www.youtube.com/watch?v=A-5eVs8B6T0) - John Carmack's presentation on Wolfenstein 3D architecture

### Graphics Programming

- [MinilibX Documentation](https://github.com/42Paris/minilibx-linux) - Official MinilibX documentation
- [Computer Graphics: Principles and Practice](https://www.elsevier.com/books/computer-graphics/foley/978-0-321-39952-2) - Classic graphics textbook

### 42 School Resources

- [42 Norm Documentation](https://github.com/42School/42cursus/blob/master/00_Libft/en.norm.md) - C coding standards
- [Libft Project](https://github.com/42Paris/libft) - 42's C utility library

## AI Usage

AI tools were used to assist with:

- **README structure** - Planning and organizing project documentation
- **Optimization suggestions** - Identifying potential performance improvements in ray-casting calculations
- **Debugging assistance** - He before iun
All AI-generated content was and tested.

## Project Structure

```
Cub3D/
├── inc/                 # Header files
├── src/                 # Source code
│   ├── main.c          # Entry point
│   ├── parsing/        # Map parsing
│   ├── raycast/        # Ray-casting engine
│   ├── render.c        # Rendering pipeline
│   └── hooks.c         # Event handlers
├── libft/              # 42 utility library
├── minilibx-linux/     # Graphics library
├── maps/               # Example map files
├── textures/           # Texture assets
├── Makefile            # Build configuration
└── README.md           # This file
```

## Notes

- Memory must be properly freed on exit to avoid leaks
- Invalid map files produce descriptive error messages
- Textures must be in XPM format
- Color values must be in range [0, 255]

---

**Last Updated:** 7th March 2026
