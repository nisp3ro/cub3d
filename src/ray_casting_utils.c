#include "../include/cub3d.h"

/**
 * @brief Applies a fog effect to a given color based on the distance.
 *
 * This function blends the input color with the fog color (black, 0x000000) based on a fog factor,
 * which is computed as the ratio of the current distance to the maximum distance. The resulting color is darker
 * with increasing distance.
 *
 * @param color The original color (in hexadecimal).
 * @param distance The current distance at which the color is being rendered.
 * @param max_distance The distance at which the fog effect is maximal.
 * @return int The new color after applying the fog effect.
 */
static int apply_fog(int color, double distance, double max_distance)
{
	double fog_factor;
	int    fog_color;
	int    rgb[3];
	int    fog[3];
	int    new[3];

	fog_color = 0x000000;
	fog_factor = distance / max_distance;
	if (fog_factor > 1.0)
		fog_factor = 1.0;
	rgb[0] = (color >> 16) & 0xFF;
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = color & 0xFF;
	fog[0] = (fog_color >> 16) & 0xFF;
	fog[1] = (fog_color >> 8) & 0xFF;
	fog[2] = fog_color & 0xFF;
	new[0] = (int)(rgb[0] * (1.0 - fog_factor) + fog[0] * fog_factor);
	new[1] = (int)(rgb[1] * (1.0 - fog_factor) + fog[1] * fog_factor);
	new[2] = (int)(rgb[2] * (1.0 - fog_factor) + fog[2] * fog_factor);
	return ((new[0] << 16) | (new[1] << 8) | new[2]);
}

/**
 * @brief Puts a pixel on the floor with a fog effect.
 *
 * This function retrieves the floor color (in hexadecimal) from vars->colors->f_hex, applies a fog effect based on the
 * provided fogDistance, and draws the pixel on the game's image at the given (x, y) coordinate.
 *
 * @param vars Pointer to the t_vars structure containing game and color data.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param fogDistance The distance used to compute the fog factor.
 */
void put_pixel_fog_floor(t_vars *vars, int x, int y, double fogDistance)
{
	t_img	*img;
	double	max_distance;
	char	*dst;

	img = &vars->game->img;
	max_distance = 10.0;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)dst = apply_fog(vars->colors->f_hex, fogDistance, max_distance);
	}
}

/**
 * @brief Puts a pixel on the ceiling with a fog effect.
 *
 * This function retrieves the ceiling color (in hexadecimal) from vars->colors->c_hex, applies a fog effect based on the
 * provided fogDistance, and draws the pixel on the game's image at the specified (x, y) coordinate.
 *
 * @param vars Pointer to the t_vars structure containing game and color data.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param fogDistance The distance used to compute the fog factor.
 */
void put_pixel_fog_ceiling(t_vars *vars, int x, int y, double fogDistance)
{
	t_img	*img;
	double	max_distance;
	char	*dst;

	img = &vars->game->img;
	max_distance = 10.0;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)dst = apply_fog(vars->colors->c_hex, fogDistance, max_distance);
	}
}

/**
 * @brief Puts a pixel on a wall with a fog effect applied.
 *
 * This function applies a fog effect to the given wall color stored in rcw->color based on the perpendicular wall distance,
 * and draws the pixel at the current column (x) and row (rcw->y) on the provided image.
 *
 * @param img Pointer to the t_img structure representing the image to draw on.
 * @param x The x-coordinate (column) of the pixel.
 * @param rcw Pointer to the t_ray_cast_draw structure containing the current drawing parameters.
 */
void put_pixel_fog_walls(t_img *img, int x, t_ray_cast_draw *rcw)
{
	double	max_distance;
	char	*dst;

	max_distance = 10.0;
	if (x >= 0 && x < WIDTH && rcw->y >= 0 && rcw->y < HEIGHT)
	{
		dst = img->addr + (rcw->y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)dst = apply_fog(rcw->color, rcw->perp_wall_dist, max_distance);
	}
}
