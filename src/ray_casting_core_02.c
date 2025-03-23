#include "../include/cub3d.h"

/**
 * @brief Draws the ceiling and floor with a fog effect.
 *
 * This function draws the ceiling from the top of the screen to the start of the wall,
 * and the floor from the end of the wall to the bottom of the screen. It calculates a
 * current distance factor for each pixel row and applies a fog effect through the functions
 * put_pixel_fog_ceiling() and put_pixel_fog_floor().
 *
 * @param rc Pointer to the t_ray_cast structure containing the current column (x) of the screen.
 * @param rcw Pointer to the t_ray_cast_draw structure containing drawing parameters (draw_start and draw_end).
 * @param vars Pointer to the t_vars structure containing overall game data.
 */
void draw_ceiling_and_floor(t_ray_cast *rc, t_ray_cast_draw *rcw, t_vars *vars)
{
	int		x;
	double	current_dist;

	x = rc->x;
	rcw->y = 0;
	while (rcw->y < rcw->draw_start)
	{
		current_dist = 1.0;
		if (HEIGHT - 2 * rcw->y != 0)
			current_dist = HEIGHT / (double)(HEIGHT - 2 * rcw->y);
		put_pixel_fog_ceiling(vars, x, rcw->y, current_dist);
		rcw->y++;
	}
	rcw->y = rcw->draw_end;
	while (rcw->y < HEIGHT)
	{
		current_dist = 1.0;
		if (2 * rcw->y - HEIGHT != 0)
			current_dist = HEIGHT / (double)(2 * rcw->y - HEIGHT);
		put_pixel_fog_floor(vars, x, rcw->y, current_dist);
		rcw->y++;
	}
}

/**
 * @brief Draws a vertical wall column with texture mapping and fog effect.
 *
 * This function iterates from the start to the end of the wall column (draw_start to draw_end)
 * and computes the corresponding texture coordinate (tex_y) for each pixel. It then retrieves the
 * color from the texture and applies a fog effect via put_pixel_fog_walls() before drawing the pixel.
 *
 * @param game Pointer to the t_game structure containing game data and the image buffer.
 * @param rc Pointer to the t_ray_cast structure containing the current column (x) and ray data.
 * @param rcw Pointer to the t_ray_cast_draw structure with wall rendering parameters.
 * @param texture Pointer to the t_img structure containing the texture data.
 */
void draw_wall_column(t_game *game, t_ray_cast *rc, t_ray_cast_draw *rcw, t_img *texture)
{
	rcw->y = rcw->draw_start;
	while (rcw->y < rcw->draw_end)
	{
		rcw->d = rcw->y * 256 - HEIGHT * 128 + rcw->line_height * 128;
		rcw->tex_y = ((rcw->d * texture->height) / rcw->line_height) / 256;
		if (rcw->tex_y < 0)
			rcw->tex_y = 0;
		else if (rcw->tex_y >= texture->height)
			rcw->tex_y = texture->height - 1;
		rcw->color = *(unsigned int *)(texture->addr + (rcw->tex_y * texture->line_length + rcw->tex_x * (texture->bpp / 8)));
		put_pixel_fog_walls(&game->img, rc->x, rcw);
		rcw->y++;
	}
}

/**
 * @brief Calculates texture coordinates for the wall hit by the ray.
 *
 * This function determines the precise point where the ray hits the wall by calculating wall_x,
 * the fractional part of the wall hit location. It then computes the corresponding x-coordinate (tex_x)
 * within the texture. For certain directions, the texture coordinate is flipped to ensure proper mapping.
 *
 * @param game Pointer to the t_game structure containing the player's position.
 * @param rc Pointer to the t_ray_cast structure containing the current ray information.
 * @param rcw Pointer to the t_ray_cast_draw structure where calculated drawing parameters will be stored.
 * @param texture Pointer to the t_img structure containing the texture data.
 */
void calculate_texture_coordinates(t_game *game, t_ray_cast *rc, t_ray_cast_draw *rcw, t_img *texture)
{
	if (rc->side == 0)
		rcw->wall_x = game->player_y + rcw->perp_wall_dist * rc->ray_dir_y;
	else
		rcw->wall_x = game->player_x + rcw->perp_wall_dist * rc->ray_dir_x;
	rcw->wall_x -= floor(rcw->wall_x);
	rcw->tex_x = (int)(rcw->wall_x * (double)(texture->width));
	if ((rc->side == 0 && rc->ray_dir_x > 0) || (rc->side == 1 && rc->ray_dir_y < 0))
		rcw->tex_x = texture->width - rcw->tex_x - 1;
}
