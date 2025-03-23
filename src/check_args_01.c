#include "../include/cub3d.h"

/**
 * @brief Checks if the correct number of command line arguments is provided.
 *
 * This function verifies that the number of arguments is exactly 2 (the program name and one additional argument).
 *
 * @param argc The number of command line arguments.
 * @return int Returns OK if argc is 2, otherwise returns ERROR.
 */
static int check_args_number(int argc)
{
	if (argc == 2)
		return (OK);
	return (ERROR);
}

/**
 * @brief Checks if the provided map file has the correct ".cub" extension.
 *
 * This function retrieves the length of the first command line argument and then
 * compares the last 4 characters of the string with ".cub". If they match, the extension is valid.
 *
 * @param argv Array of command line argument strings.
 * @return int Returns OK if the file extension is ".cub", otherwise returns ERROR.
 */
static int check_argv_extension(char *argv[])
{
	int	i;

	i = ft_strlen(argv[1]);
	if (ft_strncmp(&argv[1][i - 4], ".cub", 4) == OK)
		return (OK);
	return (ERROR);
}

/**
 * @brief Validates the command line arguments and reads the map file.
 *
 * This function checks that the correct number of arguments is provided, that the map file
 * has a ".cub" extension, and that the map exists. If all conditions are met, it reads the file's
 * content into the t_vars structure. If any check fails, an error message is printed and the program exits.
 *
 * @param argc The number of command line arguments.
 * @param argv Array of command line argument strings.
 * @param vars Pointer to the t_vars structure to store map data and other variables.
 * @return int Returns OK if all checks pass and the file is successfully read, otherwise the program exits.
 */
int check_args(int argc, char *argv[], t_vars *vars)
{
	if (check_args_number(argc) == OK && check_argv_extension(argv) == OK
		&& check_map_exists(argv[1], vars) == OK)
	{
		read_fd_file(vars);
		return (OK);
	}
	else
	{
		ft_putstr_fd("Error:\nProblem with arguments.\n", STDERR_FILENO);
		exit(ERROR);
	}
	return (ERROR);
}
