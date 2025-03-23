#include "../include/cub3d.h"

/**
 * @brief Closes the window and exits the program.
 *
 * This function is triggered when the user requests to close the window.
 * It calls clean_exit() to free resources and then terminates the program.
 *
 * @param vars Pointer to the t_vars structure containing all game data.
 * @return int Always returns 0.
 */
int close_window(t_vars *vars)
{
	clean_exit(vars);
	exit(0);
	return (0);
}

/**
 * @brief Manages door state changes adjacent to the player.
 *
 * This function checks the positions surrounding the player's current location.
 * If a door (represented by 2) is found and the door cooldown has expired, it toggles the door state
 * to open (3) or closed (2) accordingly. The door_cooldown is set to 5 after a change.
 *
 * @param game Pointer to the t_game structure containing game data.
 */
static void manage_door(t_game *game)
{
	int player_x;
	int player_y;

	player_x = (int)game->player_x;
	player_y = (int)game->player_y;
	if (game->door_cooldown > 0)
		return ;
	if (game->world_map[player_y][player_x + 1] == 2)
		game->world_map[player_y][player_x + 1] = 3;
	else if (game->world_map[player_y][player_x - 1] == 2)
		game->world_map[player_y][player_x - 1] = 3;
	else if (game->world_map[player_y + 1][player_x] == 2)
		game->world_map[player_y + 1][player_x] = 3;
	else if (game->world_map[player_y - 1][player_x] == 2)
		game->world_map[player_y - 1][player_x] = 3;
	else if (game->world_map[player_y][player_x + 1] == 3)
		game->world_map[player_y][player_x + 1] = 2;
	else if (game->world_map[player_y][player_x - 1] == 3)
		game->world_map[player_y][player_x - 1] = 2;
	else if (game->world_map[player_y + 1][player_x] == 3)
		game->world_map[player_y + 1][player_x] = 2;
	else if (game->world_map[player_y - 1][player_x] == 3)
		game->world_map[player_y - 1][player_x] = 2;
	game->door_cooldown = 5;
}

/**
 * @brief Updates the player's movement based on key inputs.
 *
 * This function checks the state of various movement keys (W, A, S, D for movement, left/right arrows for rotation)
 * and calls the corresponding movement functions. In BONUS mode, it also manages door state changes if the 'E' key is pressed.
 *
 * @param game Pointer to the t_game structure containing movement state and game data.
 */
void update_movement(t_game *game)
{
	if (game->key_w)
		move_forward(game);
	if (game->key_s)
		move_backward(game);
	if (game->key_d)
		move_right(game);
	if (game->key_a)
		move_left(game);
	if (game->key_left)
		rotate_player(game, -ROT_SPEED);
	if (game->key_right)
		rotate_player(game, ROT_SPEED);
	if (BONUS && game->key_e)
		manage_door(game);
}

/**
 * @brief Handles key press events.
 *
 * This function sets the appropriate flags in the game structure when specific keys are pressed.
 * Pressing the Escape key (key code 65307) will close the window.
 *
 * @param key The key code of the pressed key.
 * @param vars Pointer to the t_vars structure containing the game state.
 * @return int Always returns 0.
 */
int key_press(int key, t_vars *vars)
{
	if (key == 65307)
		close_window(vars);
	if (key == 119)
		vars->game->key_w = 1;
	if (key == 115)
		vars->game->key_s = 1;
	if (key == 97)
		vars->game->key_a = 1;
	if (key == 100)
		vars->game->key_d = 1;
	if (key == 65361)
		vars->game->key_left = 1;
	if (key == 65363)
		vars->game->key_right = 1;
	if (BONUS && key == 101)
		vars->game->key_e = 1;
	return (0);
}

/**
 * @brief Handles key release events.
 *
 * This function resets the key flags in the game structure when specific keys are released,
 * stopping the corresponding movement or rotation.
 *
 * @param key The key code of the released key.
 * @param game Pointer to the t_game structure containing the game state.
 * @return int Always returns 0.
 */
int key_release(int key, t_game *game)
{
	if (key == 119)
		game->key_w = 0;
	if (key == 115)
		game->key_s = 0;
	if (key == 97)
		game->key_a = 0;
	if (key == 100)
		game->key_d = 0;
	if (key == 65361)
		game->key_left = 0;
	if (key == 65363)
		game->key_right = 0;
	if (BONUS && key == 101)
		game->key_e = 0;
	return (0);
}
