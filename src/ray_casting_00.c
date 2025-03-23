#include "../include/cub3d.h"

/**
 * @brief Puts a pixel of a given color onto the image, if within bounds.
 *
 * This function calculates the address for the pixel at (x, y) in the image buffer and sets its color.
 * It ensures that the pixel coordinates are within the defined WIDTH and HEIGHT limits.
 *
 * @param img Pointer to the image structure containing image data and parameters.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color to set the pixel (in hexadecimal).
 */
static void put_pixel_clear(t_img *img, int x, int y, int color)
{
	char *dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

/**
 * @brief Clears the entire image by filling it with black.
 *
 * This function iterates over every pixel in the image and sets its color to 0x000000 (black),
 * effectively clearing any previous rendering.
 *
 * @param img Pointer to the image structure to be cleared.
 */
static void clear_image(t_img *img)
{
	int x;
	int y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel_clear(img, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

/**
 * @brief Renders the 3D scene using raycasting.
 *
 * This function iterates over each vertical stripe (pixel column) of the window and performs
 * raycasting to determine what should be rendered at that column. It calculates the ray direction,
 * initializes ray positions and steps, and processes ray casting for each column.
 *
 * @param vars Pointer to the t_vars structure containing overall game data.
 * @param game Pointer to the t_game structure containing game-specific parameters for rendering.
 */
static void render_scene(t_vars *vars, t_game *game)
{
	t_ray_cast rc;

	rc.x = 0;
	while (rc.x < WIDTH)
	{
		calculate_ray_direction(game, &rc);
		initialize_ray_position(game, &rc);
		initialize_step_and_sidedist(game, &rc);
		rc.hit = 0;
		process_ray_casting(game, vars, &rc);
		rc.x++;
	}
}

/**
 * @brief Main render loop function.
 *
 * This function clears the image, updates player movement, renders the 3D scene via raycasting,
 * and then displays the final image to the window. In BONUS mode, it also draws a minimap.
 * Additionally, it manages the door cooldown timer.
 *
 * @param vars Pointer to the t_vars structure containing all game-related data.
 * @return int Always returns 0.
 */
int render(t_vars *vars)
{
	clear_image(&vars->game->img);
	update_movement(vars->game);
	render_scene(vars, vars->game);
	mlx_put_image_to_window(vars->game->mlx, vars->game->win, vars->game->img.img, 0, 0);
	if (BONUS)
		draw_minimap(vars->game);
	if (vars->game->door_cooldown > 0)
		vars->game->door_cooldown--;
	return (0);
}
