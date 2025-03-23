#include "../include/cub3d.h"

/**
 * @brief Rotates the player's direction and camera plane.
 *
 * This function updates the player's direction vector (dir_x, dir_y) and camera plane vector
 * (plane_x, plane_y) by applying a rotation transformation using the given angle.
 *
 * @param game Pointer to the t_game structure containing the player's current state.
 * @param angle The angle (in radians) by which to rotate the player's view.
 */
void rotate_player(t_game *game, double angle)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = game->dir_x;
	game->dir_x = game->dir_x * cos(angle) - game->dir_y * sin(angle);
	game->dir_y = old_dir_x * sin(angle) + game->dir_y * cos(angle);
	old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos(angle) - game->plane_y * sin(angle);
	game->plane_y = old_plane_x * sin(angle) + game->plane_y * cos(angle);
}

/**
 * @brief Moves the player forward.
 *
 * This function calculates a new position based on the player's current direction and MOVE_SPEED.
 * It then checks the world_map to determine if the new position is walkable (i.e., an empty space or an open door)
 * before updating the player's position.
 *
 * @param game Pointer to the t_game structure containing the player's position and map data.
 */
void move_forward(t_game *game)
{
	double new_x;
	double new_y;
	double offset_x;
	double offset_y;

	new_x = game->player_x + game->dir_x * MOVE_SPEED;
	new_y = game->player_y + game->dir_y * MOVE_SPEED;
	offset_x = 0.2;
	offset_y = 0.2;
	if (game->dir_x < 0)
		offset_x = -0.2;
	if (game->dir_y < 0)
		offset_y = -0.2;
	if (game->world_map[(int)(game->player_y)][(int)(new_x + offset_x)] == 0
		|| game->world_map[(int)(game->player_y)][(int)(new_x + offset_x)] == 3)
		game->player_x = new_x;
	if (game->world_map[(int)(new_y + offset_y)][(int)(game->player_x)] == 0
		|| game->world_map[(int)(new_y + offset_y)][(int)(game->player_x)] == 3)
		game->player_y = new_y;
}

/**
 * @brief Moves the player backward.
 *
 * This function calculates a new position by subtracting the player's direction vector scaled by MOVE_SPEED.
 * It checks the world_map to verify that the new position is free (an empty space or an open door)
 * before updating the player's position.
 *
 * @param game Pointer to the t_game structure containing the player's position and map data.
 */
void move_backward(t_game *game)
{
	double new_x;
	double new_y;
	double offset_x;
	double offset_y;

	new_x = game->player_x - game->dir_x * MOVE_SPEED;
	new_y = game->player_y - game->dir_y * MOVE_SPEED;
	offset_x = -0.2;
	offset_y = -0.2;
	if (game->dir_x < 0)
		offset_x = 0.2;
	if (game->dir_y < 0)
		offset_y = 0.2;
	if (game->world_map[(int)(game->player_y)][(int)(new_x + offset_x)] == 0
		|| game->world_map[(int)(game->player_y)][(int)(new_x + offset_x)] == 3)
		game->player_x = new_x;
	if (game->world_map[(int)(new_y + offset_y)][(int)(game->player_x)] == 0
		|| game->world_map[(int)(new_y + offset_y)][(int)(game->player_x)] == 3)
		game->player_y = new_y;
}

/**
 * @brief Moves the player to the right (strafe right).
 *
 * This function calculates a new position based on the player's camera plane (which is perpendicular
 * to the direction vector) scaled by MOVE_SPEED, then checks the world_map to ensure the position is walkable
 * before updating the player's coordinates.
 *
 * @param game Pointer to the t_game structure containing the player's position and map data.
 */
void move_right(t_game *game)
{
	double new_x;
	double new_y;
	double offset_x;
	double offset_y;

	new_x = game->player_x + game->plane_x * MOVE_SPEED;
	new_y = game->player_y + game->plane_y * MOVE_SPEED;
	offset_x = 0.2;
	offset_y = 0.2;
	if (game->plane_x < 0)
		offset_x = -0.2;
	if (game->plane_y < 0)
		offset_y = -0.2;
	if (game->world_map[(int)(game->player_y)][(int)(new_x + offset_x)] == 0
		|| game->world_map[(int)(game->player_y)][(int)(new_x + offset_x)] == 3)
		game->player_x = new_x;
	if (game->world_map[(int)(new_y + offset_y)][(int)(game->player_x)] == 0
		|| game->world_map[(int)(new_y + offset_y)][(int)(game->player_x)] == 3)
		game->player_y = new_y;
}

/**
 * @brief Moves the player to the left (strafe left).
 *
 * This function calculates a new position by subtracting the player's camera plane scaled by MOVE_SPEED,
 * then verifies that the new position is not obstructed (empty space or open door) before updating the player's position.
 *
 * @param game Pointer to the t_game structure containing the player's position and map data.
 */
void move_left(t_game *game)
{
	double new_x;
	double new_y;
	double offset_x;
	double offset_y;

	new_x = game->player_x - game->plane_x * MOVE_SPEED;
	new_y = game->player_y - game->plane_y * MOVE_SPEED;
	offset_x = -0.2;
	offset_y = -0.2;
	if (game->plane_x < 0)
		offset_x = 0.2;
	if (game->plane_y < 0)
		offset_y = 0.2;
	if (game->world_map[(int)(game->player_y)][(int)(new_x + offset_x)] == 0
		|| game->world_map[(int)(game->player_y)][(int)(new_x + offset_x)] == 3)
		game->player_x = new_x;
	if (game->world_map[(int)(new_y + offset_y)][(int)(game->player_x)] == 0
		|| game->world_map[(int)(new_y + offset_y)][(int)(game->player_x)] == 3)
		game->player_y = new_y;
}
