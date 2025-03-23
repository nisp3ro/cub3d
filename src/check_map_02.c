#include "../include/cub3d.h"

/**
 * @brief Sets the initial direction and camera plane for the player when starting facing North.
 *
 * @param vars Pointer to the t_vars structure containing game data.
 */
static void set_start_n(t_vars *vars)
{
	vars->game->dir_x = 0;
	vars->game->dir_y = -1;
	vars->game->plane_x = 0.66;
	vars->game->plane_y = 0;
}

/**
 * @brief Sets the initial direction and camera plane for the player when starting facing South.
 *
 * @param vars Pointer to the t_vars structure containing game data.
 */
static void set_start_s(t_vars *vars)
{
	vars->game->dir_x = 0;
	vars->game->dir_y = 1;
	vars->game->plane_x = -0.66;
	vars->game->plane_y = 0;
}

/**
 * @brief Sets the initial direction and camera plane for the player when starting facing East.
 *
 * @param vars Pointer to the t_vars structure containing game data.
 */
static void set_start_e(t_vars *vars)
{
	vars->game->dir_x = 1;
	vars->game->dir_y = 0;
	vars->game->plane_x = 0;
	vars->game->plane_y = 0.66;
}

/**
 * @brief Sets the initial direction and camera plane for the player when starting facing West.
 *
 * @param vars Pointer to the t_vars structure containing game data.
 */
static void set_start_w(t_vars *vars)
{
	vars->game->dir_x = -1;
	vars->game->dir_y = 0;
	vars->game->plane_x = 0;
	vars->game->plane_y = -0.66;
}

/**
 * @brief Checks if a character in the map is valid and sets the player's starting parameters.
 *
 * This function verifies that the character c is valid in the context of the map.
 * Valid characters include: '1' (wall), '0' (empty space), space, 'N', 'S', 'W', 'E' for the player's
 * starting position, and (if BONUS is enabled) 'D' for a special element. If the character represents a starting
 * position (N, S, E, or W), the function sets the player's start orientation, starting position (centered in the cell),
 * and the corresponding initial direction and camera plane.
 *
 * @param vars Pointer to the t_vars structure containing game data.
 * @param c The character from the map to check.
 * @param i The current row index in the map.
 * @param j The current column index in the map.
 * @return int Returns OK if the character is valid, otherwise ERROR.
 */
int check_valid_charset(t_vars *vars, char c, int i, int j)
{
	if (c == '1' || c == '0' || c == ' ' || c == 'N' || c == 'S' || c == 'W'
		|| c == 'E' || (BONUS && c == 'D'))
	{
		/* If the character is one of the starting position identifiers,
		   set up the player's initial state. */
		if (!(c == '1' || c == '0' || c == ' ' || (BONUS && c == 'D')))
		{
			vars->map[i][j] = '0'; /* Replace starting marker with empty space */
			vars->player->start_orientation = c;
			vars->game->player_x = j + 0.5;
			vars->game->player_y = i + 0.5;
			vars->player->x_start = i;
			vars->player->y_start = j;
			if (c == 'N')
				set_start_n(vars);
			else if (c == 'S')
				set_start_s(vars);
			else if (c == 'E')
				set_start_e(vars);
			else if (c == 'W')
				set_start_w(vars);
		}
		return (OK);
	}
	return (ERROR);
}
