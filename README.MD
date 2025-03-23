#  :suspect: Cub3D 125/100

Cub3D is a 3D game project inspired by classic raycasting engines. It simulates a first-person view in a maze-like environment by casting rays from the player's position to determine visible walls, floors, and ceilings. This project implements a basic version of a raycasting engine using the MiniLibX (MLX) graphics library.

---

## Overview

Cub3D uses raycasting (often mistaken with raytracing) to render a 3D scene from a 2D map. The core idea is to cast a ray for every vertical stripe (column) of the screen and calculate where that ray intersects with walls in the map. The intersection information is used to determine the height of the wall slice, texture mapping, and to apply a fog effect that simulates depth. Key features include:

- **Raycasting Engine:** 
  - Computes ray directions for each column.
  - Uses the Digital Differential Analysis (DDA) algorithm to find wall intersections.
  - Calculates perpendicular wall distances to correct the fish-eye effect.
  - Maps textures onto wall slices with proper scaling.
  - Applies a fog effect to walls, ceilings, and floors based on distance.

- **Minimap & Movement:**
  - Renders a minimap showing the player's position.
  - Supports player movement (forward, backward, strafing) and rotation.

- **Additional Effects:**
  - Fog effects on floors, ceilings, and walls add realism.
  - Doors and animations enhance the visual experience in BONUS mode.

---

## Installation & Compilation

To compile Cub3D, simply run:

```sh
make
```

For BONUS mode (doors with animations, minimap and mouse camara control), run:

```sh
make bonus
```

### Cleaning Up

- `make clean` – Removes object files.
- `make fclean` – Removes object files and the final executable.
- `make re` – Fully recompiles the project.
- `make rebonus` – Fully recompiles the bonus project.

---

## Usage

Run the program with:

```sh
./cub3d <map_file.cub>
```

The map file should have a `.cub` extension and contain all necessary configurations (texture paths, colors, and the 2D map layout).

---

## Implementation Details

### Raycasting

Cub3D’s rendering engine uses raycasting to create a 3D effect from a 2D map. Here's a brief overview of the process:

1. **Ray Direction Calculation:**  
   For each vertical screen column, a ray is cast by calculating its direction using the player's current position, view direction, and the camera plane. This defines the “camera_x” value that scales the plane vector.

2. **DDA Algorithm:**  
   The Digital Differential Analysis (DDA) algorithm is used to step through the map grid until a wall is hit. Depending on the distance to the next x- or y-side, the ray advances in that direction, marking a hit when it encounters a wall (or door).

3. **Perpendicular Distance & Wall Height:**  
   Once a wall is hit, the perpendicular distance from the player to the wall is computed. This distance is used to calculate the height of the wall slice on the screen, thereby correcting for the fish-eye effect.

4. **Texture Mapping:**  
   Based on the point of impact, the corresponding texture coordinates are calculated and the wall slice is drawn using texture data. The textures are selected based on the side of the wall hit and additional logic for doors.

5. **Fog Effect:**  
   A fog effect is applied to the ceiling, floor, and walls based on the distance from the player. This darkens the colors with increasing distance, adding depth to the scene.

### Additional Notes

- **Memory Management:**  
  Although my code is free of memory leaks, please note that the `mlx_mouse_hide` function in the version of MLX provided for this project allocates memory without offering corresponding functions to free it. This is an inherent issue with the library version, not with my code.

---

## Acknowledgements
I would like to express my sincere gratitude to my colleague [jvidal-t](https://github.com/Flingocho)
 for his invaluable help on this project.

## License

This project is part of the 42 School curriculum. Feel free to explore the repository, provide feedback, or contribute improvements.

Happy coding!
