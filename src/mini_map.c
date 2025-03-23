#include "../include/cub3d.h"

/**
 * @brief Draws a filled square of a given color on the window.
 *
 * This function draws a square tile on the minimap using mlx_pixel_put(). The square's position
 * is calculated based on the provided x and y cell coordinates, the TILE_SIZE, and a predefined MAP_OFFSET.
 *
 * @param game Pointer to the t_game structure containing MLX data.
 * @param x The x-coordinate (in map cells) where the square will be drawn.
 * @param y The y-coordinate (in map cells) where the square will be drawn.
 * @param color The color of the square, in hexadecimal.
 */
static void draw_square(t_game *game, int x, int y, int color)
{
	int start_x;
	int start_y;
	int i;
	int j;

	start_x = MAP_OFFSET + x * TILE_SIZE;
	start_y = MAP_OFFSET + y * TILE_SIZE;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_pixel_put(game->mlx, game->win, start_x + j, start_y + i, color);
			j++;
		}
		i++;
	}
}

/**
 * @brief Draws the cells of the minimap.
 *
 * This function iterates over the visible portion of the map defined by the minimap bounds (vals).
 * Each cell is drawn as a square using draw_square(), with different colors for walls (color: white)
 * and empty spaces (color: black).
 *
 * @param game Pointer to the t_game structure containing map and MLX data.
 * @param vals Pointer to the t_minimap structure that holds the minimap bounds.
 */
static void draw_cells(t_game *game, t_minimap *vals)
{
	int y;
	int x;
	int color;

	y = vals->start_y;
	while (y <= vals->end_y)
	{
		x = vals->start_x;
		while (x <= vals->end_x)
		{
			if (game->world_map[y][x] == 1)
				color = 0xFFFFFF;
			else
				color = 0x000000;
			draw_square(game, x - vals->start_x, y - vals->start_y, color);
			x++;
		}
		y++;
	}
}

/**
 * @brief Clamps the minimap bounds to valid map indices.
 *
 * This function ensures that the minimap boundaries do not exceed the dimensions of the actual map.
 * It adjusts the start and end indices for both x and y dimensions so they lie within [0, map_width - 1]
 * and [0, map_height - 1] respectively.
 *
 * @param game Pointer to the t_game structure containing map dimensions.
 * @param vals Pointer to the t_minimap structure that holds the minimap bounds.
 */
static void clamp_minimap_bounds(t_game *game, t_minimap *vals)
{
	if (vals->start_x < 0)
		vals->start_x = 0;
	if (vals->start_y < 0)
		vals->start_y = 0;
	if (vals->end_x >= game->map_width)
		vals->end_x = game->map_width - 1;
	if (vals->end_y >= game->map_height)
		vals->end_y = game->map_height - 1;
}

/**
 * @brief Draws the minimap on the game window.
 *
 * This function calculates the minimap boundaries based on the player's current position and a defined
 * MINIMAP_RADIUS. It then clamps these boundaries to the dimensions of the map, draws the visible cells,
 * and finally draws the player's position as a red square on the minimap.
 *
 * @param game Pointer to the t_game structure containing the player's position, map dimensions, and MLX data.
 */
void draw_minimap(t_game *game)
{
	t_minimap vals;

	vals.start_x = (int)(game->player_x) - MINIMAP_RADIUS;
	vals.start_y = (int)(game->player_y) - MINIMAP_RADIUS;
	vals.end_x = (int)(game->player_x) + MINIMAP_RADIUS;
	vals.end_y = (int)(game->player_y) + MINIMAP_RADIUS;
	clamp_minimap_bounds(game, &vals);
	draw_cells(game, &vals);
	draw_square(game, game->player_x - vals.start_x, game->player_y - vals.start_y, 0xFF0000);
}
