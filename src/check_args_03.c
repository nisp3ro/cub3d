#include "../include/cub3d.h"

/**
 * @brief Sets the floor and ceiling color values from a configuration line.
 *
 * This function checks if the configuration line starts with 'F' (floor) or 'C' (ceiling)
 * and sets the corresponding color value after trimming whitespace. If a color has already been set,
 * it prints an error and exits.
 *
 * @param vars Pointer to the t_vars structure containing configuration data.
 * @param value The configuration line containing the color value.
 * @return int Returns OK on success, or ERROR if memory allocation fails.
 */
int set_value_03(t_vars *vars, char *value)
{
	if (ft_strncmp(value, "F", 1) == OK)
	{
		if (vars->colors->f)
			return (ft_putstr_fd("Error:\nInvalid file.\n", STDERR_FILENO),
				exit(1), 1);
		vars->colors->f = ft_strtrim(value + 2, " \t");
		if (!vars->colors->f)
			return (perror("malloc"), ERROR);
	}
	else if (ft_strncmp(value, "C", 1) == OK)
	{
		if (vars->colors->c)
			return (ft_putstr_fd("Error:\nInvalid file.\n", STDERR_FILENO),
				exit(1), 1);
		vars->colors->c = ft_strtrim(value + 2, " \t");
		if (!vars->colors->c)
			return (perror("malloc"), ERROR);
	}
	return (OK);
}

/**
 * @brief Sets the west and east texture paths or delegates to set_value_03.
 *
 * This function checks if the configuration line starts with "WE" (west) or "EA" (east) and sets
 * the corresponding texture path after trimming whitespace. If a texture path has already been set,
 * it prints an error and exits. If the configuration line does not match these prefixes,
 * it calls set_value_03() to handle other cases.
 *
 * @param vars Pointer to the t_vars structure containing configuration data.
 * @param value The configuration line containing the texture path or color value.
 * @return int Returns OK on success, or ERROR if an error occurs.
 */
static int set_value_02(t_vars *vars, char *value)
{
	if (ft_strncmp(value, "WE", 2) == OK)
	{
		if (vars->paths->we)
			return (ft_putstr_fd("Error:\nInvalid file.\n", STDERR_FILENO),
				exit(1), 1);
		vars->paths->we = ft_strtrim(value + 3, " \t");
		if (!vars->paths->we)
			return (perror("malloc"), ERROR);
	}
	else if (ft_strncmp(value, "EA", 2) == OK)
	{
		if (vars->paths->ea)
			return (ft_putstr_fd("Error:\nInvalid file.\n", STDERR_FILENO),
				exit(1), 1);
		vars->paths->ea = ft_strtrim(value + 3, " \t");
		if (!vars->paths->ea)
			return (perror("malloc"), ERROR);
	}
	else if (set_value_03(vars, value) == ERROR)
		return (ERROR);
	return (OK);
}

/**
 * @brief Sets a configuration value based on its identifier.
 *
 * This function checks the beginning of the configuration line to determine which
 * parameter is being set. If the line starts with "NO" (north), "SO" (south), "WE" (west),
 * "EA" (east), or a color identifier ("F" or "C"), the corresponding field in the
 * t_vars structure is set. If the line starts with '1', it indicates the beginning of the map,
 * and the function returns 2.
 *
 * @param vars Pointer to the t_vars structure containing configuration data.
 * @param value The configuration line.
 * @return int Returns 2 if the map starts, OK on success, or ERROR if an error occurs.
 */
static int set_value(t_vars *vars, char *value)
{
	if (value[0] == '1')
		return (2);
	else if (ft_strncmp(value, "NO", 2) == OK)
	{
		if (vars->paths->no)
			return (ft_putstr_fd("Error:\nInvalid file.\n", STDERR_FILENO),
				exit(1), 1);
		vars->paths->no = ft_strtrim(value + 3, " \t");
		if (!vars->paths->no)
			return (perror("malloc"), ERROR);
	}
	else if (ft_strncmp(value, "SO", 2) == OK)
	{
		if (vars->paths->so)
			return (ft_putstr_fd("Error:\nInvalid file.\n", STDERR_FILENO),
				exit(1), 1);
		vars->paths->so = ft_strtrim(value + 3, " \t");
		if (!vars->paths->so)
			return (perror("malloc"), ERROR);
	}
	else if (set_value_02(vars, value) == ERROR)
		return (ERROR);
	return (OK);
}

/**
 * @brief Parses the configuration file content to set game parameters and map.
 *
 * This function iterates through the lines of the configuration file stored in vars->file,
 * skipping any leading whitespace. For each non-empty line, it calls set_value() to process
 * the configuration parameter. When a line starting with '1' (indicating the start of the map)
 * is encountered, it calls assign_colors() to process color values and assigns the remaining lines
 * as the map data.
 *
 * @param vars Pointer to the t_vars structure containing configuration data and the file split into lines.
 */
void parse_file(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars->file[i])
	{
		j = 0;
		while (vars->file[i][j] != '\0' && isspace(vars->file[i][j]))
			j++;
		if (vars->file[i][j] != '\0')
		{
			if (set_value(vars, &vars->file[i][j]) == 2)
			{
				assign_colors(vars);
				vars->map = &vars->file[i];
				break ;
			}
		}
		i++;
	}
}
