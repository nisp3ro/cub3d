#include "../include/cub3d.h"

/**
 * @brief Selects the appropriate door texture based on the animation counter.
 *
 * This function assigns a door texture from the game textures array based on the value of the counter `i`.
 * The textures are selected in 10,000 increments, cycling through DOOR1, DOOR2, DOOR3, and DOOR4.
 *
 * @param game Pointer to the t_game structure containing textures.
 * @param i The current animation counter value.
 * @param texture Pointer to a t_img structure where the selected texture will be stored.
 */
static void select_door_tex(t_game *game, int i, t_img *texture)
{
	if (i <= 10000)
		*texture = game->textures[DOOR1];
	else if (i <= 20000)
		*texture = game->textures[DOOR2];
	else if (i <= 30000)
		*texture = game->textures[DOOR3];
	else if (i <= 40000)
		*texture = game->textures[DOOR4];
}

/**
 * @brief Selects the correct wall or door texture for the current ray.
 *
 * This function determines which texture to use based on the map cell value and the side of the wall hit.
 * If the cell corresponds to a door (value 2), it selects a door texture based on a static counter.
 * Otherwise, it selects a wall texture based on the ray's direction.
 *
 * @param game Pointer to the t_game structure containing textures and map data.
 * @param rc Pointer to the t_ray_cast structure containing raycasting data.
 * @param texture Pointer to a t_img structure where the selected texture will be stored.
 */
static void select_texture(t_game *game, t_ray_cast *rc, t_img *texture)
{
	static int i;

	if (game->world_map[rc->map_y][rc->map_x] == 2)
	{
		if (i >= 40000)
			i = 0;
		select_door_tex(game, i, texture);
	}
	else if (rc->side == 1)
	{
		if (rc->ray_dir_y < 0)
			*texture = game->textures[NORTH];
		else
			*texture = game->textures[SOUTH];
	}
	else
	{
		if (rc->ray_dir_x < 0)
			*texture = game->textures[WEST];
		else
			*texture = game->textures[EAST];
	}
	i++;
}

/**
 * @brief Calculates the perpendicular distance from the player to the wall.
 *
 * Depending on whether the wall was hit vertically (side 0) or horizontally (side 1),
 * this function calculates the distance using the appropriate component of the ray direction.
 *
 * @param game Pointer to the t_game structure containing the player's position.
 * @param rc Pointer to the t_ray_cast structure containing raycasting information.
 * @return double The perpendicular wall distance.
 */
static double calculate_perp_wall_dist(t_game *game, t_ray_cast *rc)
{
	double perp_wall_dist;
	double adjustment;

	if (rc->side == 0)
	{
		adjustment = 1;
		if (rc->ray_dir_x < 0)
			adjustment = -1;
		perp_wall_dist = (rc->map_x - game->player_x + (1 - adjustment) / 2) / rc->ray_dir_x;
	}
	else
	{
		adjustment = 1;
		if (rc->ray_dir_y < 0)
			adjustment = -1;
		perp_wall_dist = (rc->map_y - game->player_y + (1 - adjustment) / 2) / rc->ray_dir_y;
	}
	return (perp_wall_dist);
}

/**
 * @brief Calculates wall rendering parameters for the current ray.
 *
 * This function computes the perpendicular wall distance, determines the height of the wall line,
 * and calculates the start and end positions on the screen where the wall should be drawn.
 * It also determines the texture number based on the map cell value.
 *
 * @param game Pointer to the t_game structure containing the player's position and map data.
 * @param rc Pointer to the t_ray_cast structure containing current ray data.
 * @param rcw Pointer to the t_ray_cast_draw structure where wall rendering parameters will be stored.
 */
static void calculate_wall_params(t_game *game, t_ray_cast *rc, t_ray_cast_draw *rcw)
{
	rcw->perp_wall_dist = calculate_perp_wall_dist(game, rc);
	rcw->line_height = (int)(HEIGHT / rcw->perp_wall_dist);
	rcw->draw_start = (HEIGHT - rcw->line_height) / 2;
	rcw->draw_end = (HEIGHT + rcw->line_height) / 2;
	if (rcw->draw_start < 0)
		rcw->draw_start = 0;
	if (rcw->draw_end >= HEIGHT)
		rcw->draw_end = HEIGHT - 1;
	rcw->tex_num = game->world_map[rc->map_y][rc->map_x] - 1;
}

/**
 * @brief Renders a single vertical column (stripe) of the 3D scene.
 *
 * This function calculates the necessary wall parameters, selects the appropriate texture,
 * computes texture coordinates, and then draws the wall column. It also draws the ceiling and floor.
 *
 * @param game Pointer to the t_game structure containing rendering and map data.
 * @param vars Pointer to the t_vars structure containing overall game data.
 * @param rc Pointer to the t_ray_cast structure with current raycasting information.
 */
void render_column(t_game *game, t_vars *vars, t_ray_cast *rc)
{
	t_ray_cast_draw rcw;
	t_img texture;

	calculate_wall_params(game, rc, &rcw);
	select_texture(game, rc, &texture);
	calculate_texture_coordinates(game, rc, &rcw, &texture);
	draw_wall_column(game, rc, &rcw, &texture);
	draw_ceiling_and_floor(rc, &rcw, vars);
}
