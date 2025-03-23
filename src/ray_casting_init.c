#include "../include/cub3d.h"

/**
 * @brief Performs the Digital Differential Analysis (DDA) algorithm.
 *
 * This function advances the ray step-by-step until it hits a wall. It compares side distances 
 * and increments the appropriate distance and map coordinate based on the smallest value.
 * The process stops when the ray hits a cell that is not empty (i.e., not 0 or 3).
 *
 * @param game Pointer to the t_game structure containing the world map and player data.
 * @param rc Pointer to the t_ray_cast structure containing current raycasting data.
 */
static void perform_dda(t_game *game, t_ray_cast *rc)
{
	while (!(rc->hit))
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (game->world_map[rc->map_y][rc->map_x] != 0 &&
			game->world_map[rc->map_y][rc->map_x] != 3)
			rc->hit = 1;
	}
}

/**
 * @brief Processes raycasting for a single column.
 *
 * This function performs the DDA algorithm to determine where a ray hits a wall, and then calls
 * render_column() to draw the vertical slice (column) corresponding to that ray.
 *
 * @param game Pointer to the t_game structure containing game data.
 * @param vars Pointer to the t_vars structure containing overall game data.
 * @param rc Pointer to the t_ray_cast structure with current raycasting information.
 */
void process_ray_casting(t_game *game, t_vars *vars, t_ray_cast *rc)
{
	perform_dda(game, rc);
	render_column(game, vars, rc);
}

/**
 * @brief Initializes the step and initial side distance for the ray.
 *
 * This function determines the direction to step in the grid (step_x, step_y) based on the ray direction.
 * It also calculates the initial side distances (side_dist_x, side_dist_y) from the current position to the
 * next x or y side.
 *
 * @param game Pointer to the t_game structure containing player position.
 * @param rc Pointer to the t_ray_cast structure where step values and side distances will be stored.
 */
void initialize_step_and_sidedist(t_game *game, t_ray_cast *rc)
{
	if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (game->player_x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - game->player_x) * rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (game->player_y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - game->player_y) * rc->delta_dist_y;
	}
}

/**
 * @brief Initializes the starting grid position and delta distances for a ray.
 *
 * This function sets the initial map coordinates (map_x, map_y) based on the player's position.
 * It then calculates the delta distances (delta_dist_x, delta_dist_y), which represent the distance the ray
 * must travel to move from one x-side to the next and one y-side to the next.
 *
 * @param game Pointer to the t_game structure containing the player's position.
 * @param rc Pointer to the t_ray_cast structure where the starting position and delta distances will be stored.
 */
void initialize_ray_position(t_game *game, t_ray_cast *rc)
{
	rc->map_x = (int)game->player_x;
	rc->map_y = (int)game->player_y;
	rc->delta_dist_x = fabs(1 / rc->ray_dir_x);
	rc->delta_dist_y = fabs(1 / rc->ray_dir_y);
}

/**
 * @brief Calculates the direction of the ray for the current screen column.
 *
 * This function computes the camera plane coordinate (camera_x) for the current column (rc->x)
 * and then calculates the ray direction vector (ray_dir_x, ray_dir_y) by adding the scaled plane vector
 * to the player's direction vector.
 *
 * @param game Pointer to the t_game structure containing the player's direction and camera plane.
 * @param rc Pointer to the t_ray_cast structure where the ray direction will be stored.
 */
void calculate_ray_direction(t_game *game, t_ray_cast *rc)
{
	rc->camera_x = 2 * rc->x / (double)WIDTH - 1;
	rc->ray_dir_x = game->dir_x + game->plane_x * rc->camera_x;
	rc->ray_dir_y = game->dir_y + game->plane_y * rc->camera_x;
}
