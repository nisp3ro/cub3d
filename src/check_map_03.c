#include "../include/cub3d.h"

/**
 * @brief Recursively performs a flood fill on the map to check for enclosure.
 *
 * This function starts at a given cell (row, col) and recursively marks reachable cells with
 * the character 'F'. It stops the recursion when it reaches a boundary (cell is '1', a space, or already 'F')
 * or if the indices go out of bounds. If the recursion reaches an invalid position, the function returns ERROR.
 *
 * @param vars Pointer to the t_vars structure containing the map.
 * @param row The current row index.
 * @param col The current column index.
 * @param size The total number of rows in the map.
 * @return int Returns OK if the flood fill completes successfully, or ERROR if an invalid position is encountered.
 */
static int f_fill(t_vars *vars, int row, int col, int size)
{
	int row_length;

	if (row < 0 || row >= size)
		return (ERROR);
	row_length = ft_strlen(vars->map[row]);
	if (col < 0 || col >= row_length)
		return (ERROR);
	if (vars->map[row][col] == '1' || vars->map[row][col] == ' ' || vars->map[row][col] == 'F')
		return (OK);
	vars->map[row][col] = 'F';
	if (f_fill(vars, row - 1, col, size) == ERROR)
		return (ERROR);
	if (f_fill(vars, row + 1, col, size) == ERROR)
		return (ERROR);
	if (f_fill(vars, row, col - 1, size) == ERROR)
		return (ERROR);
	if (f_fill(vars, row, col + 1, size) == ERROR)
		return (ERROR);
	return (OK);
}

/**
 * @brief Initiates the flood fill algorithm from the player's starting position.
 *
 * This function calls f_fill() using the player's starting coordinates stored in vars->player.
 *
 * @param vars Pointer to the t_vars structure containing map and player data.
 * @param size The total number of rows in the map.
 * @return int Returns OK if the flood fill completes successfully, or ERROR if an error occurs.
 */
static int flood_fill(t_vars *vars, int size)
{
	return (f_fill(vars, vars->player->x_start, vars->player->y_start, size));
}

/**
 * @brief Checks if the map is enclosed using a flood fill algorithm.
 *
 * This function validates that the map is properly enclosed (i.e., there are no openings)
 * by performing a flood fill starting from the player's starting position. It first determines
 * the size of the map, then calls flood_fill(). If the player's starting position is invalid or
 * the flood fill fails, it returns ERROR.
 *
 * @param vars Pointer to the t_vars structure containing the map and player data.
 * @return int Returns OK if the map is enclosed, or ERROR if it is not.
 */
int check_flood(t_vars *vars)
{
	int size;

	size = 0;
	if (vars->player->x_start < 0 || vars->player->y_start < 0)
		return (ERROR);
	while (vars->map[size])
		size++;
	return (flood_fill(vars, size));
}
