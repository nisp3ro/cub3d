#include "../include/cub3d.h"

/**
 * @brief Converts the map characters into an integer matrix.
 *
 * This function iterates through each row and column of the map (stored as strings)
 * and assigns integer values to the world_map matrix in the game structure:
 * - '0' is converted to 0 (empty space).
 * - 'D' is converted to 2 (special element, e.g., door).
 * - All other characters (including walls and spaces) are set to 1.
 *
 * @param vars Pointer to the t_vars structure containing the map and game data.
 */
static void set_matrix_int(t_vars *vars)
{
	int i;
	int j;
	int row_length;

	i = 0;
	while (i < vars->game->map_height)
	{
		row_length = ft_strlen(vars->map[i]);
		j = 0;
		while (j < vars->game->map_width)
		{
			if (j < row_length && vars->map[i][j] == '0')
				vars->game->world_map[i][j] = 0;
			else if (j < row_length && vars->map[i][j] == 'D')
				vars->game->world_map[i][j] = 2;
			else
				vars->game->world_map[i][j] = 1;
			j++;
		}
		i++;
	}
}

/**
 * @brief Determines the dimensions of the map and allocates the world_map matrix.
 *
 * This function calculates the maximum width and total height of the map by iterating through
 * the map string array. It then allocates memory for a 2D integer matrix (world_map) based on
 * these dimensions and fills it using set_matrix_int(). Finally, it performs a flood-fill check
 * to ensure the map's validity.
 *
 * @param vars Pointer to the t_vars structure containing the map and game data.
 * @return int Returns OK on success, or ERROR if a memory allocation or flood-fill check fails.
 */
static int map_dimensions(t_vars *vars)
{
	int i;

	i = 0;
	while (vars->map[i])
	{
		if ((size_t)vars->game->map_width < ft_strlen(vars->map[i]))
			vars->game->map_width = ft_strlen(vars->map[i]);
		i++;
	}
	vars->game->map_height = i;
	i = 0;
	vars->game->world_map = calloc(vars->game->map_height, sizeof(int *));
	if (!vars->game->world_map)
		return (perror("malloc"), exit(1), ERROR);
	while (i < vars->game->map_height)
	{
		vars->game->world_map[i] = calloc(vars->game->map_width, sizeof(int));
		if (!vars->game->world_map[i++])
			return (perror("malloc"), exit(1), ERROR);
	}
	set_matrix_int(vars);
	if (check_flood(vars) == ERROR)
		return (ft_putstr_fd("Error:\nInvalid map.\n", STDERR_FILENO), exit(1), ERROR);
	return (OK);
}

/**
 * @brief Checks that there is exactly one starting position in the map.
 *
 * This function iterates over the map and counts the occurrences of starting position characters:
 * 'N', 'S', 'E', or 'W'. If exactly one starting position is found, it returns OK; otherwise, it prints
 * an error message and returns ERROR.
 *
 * @param map Array of strings representing the map.
 * @return int Returns OK if exactly one starting position exists, otherwise ERROR.
 */
static int check_repeated_position(char **map)
{
	int i;
	int j;
	int counter;

	i = 0;
	counter = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
				counter++;
			j++;
		}
		i++;
	}
	if (counter == 1)
		return (OK);
	ft_putstr_fd("Error:\nInvalid map.\n", STDERR_FILENO);
	return (ERROR);
}

/**
 * @brief Validates the map content and dimensions.
 *
 * This function performs several checks on the map:
 * - It ensures there is exactly one starting position by calling check_repeated_position().
 * - It verifies that each character in the map is valid by calling check_valid_charset().
 * - It replaces any space characters with '1' (considered as walls).
 * - Finally, it calculates the map dimensions, allocates the world_map matrix, and performs a flood-fill
 *   check to ensure that the map is properly closed.
 *
 * @param vars Pointer to the t_vars structure containing the map and game data.
 * @return int Returns OK if the map is valid, otherwise ERROR.
 */
int check_map_valid(t_vars *vars)
{
	int i;
	int j;

	i = 0;
	if (check_repeated_position(vars->map) == ERROR)
		exit(ERROR);
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (check_valid_charset(vars, vars->map[i][j], i, j) == ERROR)
				return (ft_putstr_fd("Error:\nInvalid map.\n", STDERR_FILENO), ERROR);
			if (vars->map[i][j] == ' ')
				vars->map[i][j] = '1';
			j++;
		}
		i++;
	}
	if (map_dimensions(vars) == ERROR)
		return (ERROR);
	return (OK);
}
