#include "../include/cub3d.h"

/**
 * @brief Skips over value lines in the configuration file until the start of the map.
 *
 * This function advances the index through the file string, skipping over lines containing configuration
 * values (e.g., resolution, texture paths) until it finds a line that likely starts the map data (lines starting
 * with '0' or '1'). If no map data is found, it returns ERROR.
 *
 * @param file The file content as a string.
 * @param i Pointer to the current index in the file string.
 * @return int Returns OK if map data is found, otherwise ERROR.
 */
static int skip_vals_lines(char *file, int *i)
{
	while (file[*i])
	{
		while (file[*i] && file[*i] != '\n')
			(*i)++;
		if (file[*i] == '\0')
			break ;
		(*i)++;
		while (file[*i] && isspace(file[*i]))
			(*i)++;
		if (file[*i] && (file[*i] == '0' || file[*i] == '1'))
			break ;
	}
	if (!file[*i])
		return (ERROR);
	return (OK);
}

/**
 * @brief Checks for extra newline characters between the map rows.
 *
 * This function verifies that there are no unexpected blank lines within the map area.
 * It first skips the configuration value lines using skip_vals_lines(), then iterates through
 * the map portion to check that no extra newline appears within the map data. If an extra newline
 * is found before the end of the file, it returns ERROR.
 *
 * @param file The file content as a string.
 * @return int Returns OK if the map is valid, otherwise ERROR.
 */
static int check_n_between_map(char *file)
{
	int	i;

	i = 0;
	if (skip_vals_lines(file, &i) == ERROR)
		return (ERROR);
	while (file[i])
	{
		while (file[i] && file[i] != '\n')
			i++;
		if (file[i] == '\0')
			break ;
		i++;
		if (file[i] == '\n')
		{
			while (file[i] && (isspace(file[i]) || file[i] == '\n'))
				i++;
			if (file[i] == '\0')
				return (OK);
			else
				return (ERROR);
		}
	}
	return (OK);
}

/**
 * @brief Reads the map file content from the file descriptor into the t_vars structure.
 *
 * This function allocates a buffer and reads the entire file using read(). It then validates the file
 * by checking for unexpected blank lines between map rows. If the file is valid, it splits the content
 * into lines and passes it for further parsing. In case of any error, it performs necessary cleanup and exits.
 *
 * @param vars Pointer to the t_vars structure that holds map data and other variables.
 */
void read_fd_file(t_vars *vars)
{
	vars->buffer = ft_calloc(sizeof(char *), BUFF_SIZE);
	if (!vars->buffer)
		return (perror("malloc"), close(vars->map_path_fd),
			free(vars->map_path), exit(ERROR));
	vars->bytes_read = read(vars->map_path_fd, vars->buffer, BUFF_SIZE);
	if (vars->bytes_read == -1 || vars->buffer[BUFF_SIZE - 1] != '\0')
		return (perror("read"), close(vars->map_path_fd), free(vars->map_path),
			exit(ERROR));
	if (check_n_between_map(vars->buffer) == ERROR)
		return (ft_putstr_fd("Error:\nInvalid file.\n", STDERR_FILENO),
			exit(1));
	vars->file = ft_split(vars->buffer, '\n');
	if (!vars->file)
		(perror("read"), exit(ERROR));
	close(vars->map_path_fd);
	free(vars->buffer);
	parse_file(vars);
}

/**
 * @brief Checks if the map file exists and opens it.
 *
 * This function attempts to open the file at the specified path in read-only mode.
 * If the file cannot be opened, it prints an error message and exits the program.
 *
 * @param path The path to the map file.
 * @param vars Pointer to the t_vars structure for storing the file descriptor.
 * @return int Returns OK if the file is successfully opened, otherwise ERROR.
 */
int check_map_exists(char *path, t_vars *vars)
{
	vars->map_path_fd = open(path, O_RDONLY);
	if (vars->map_path_fd < 0)
		return (perror("open"), exit(ERROR), ERROR);
	return (OK);
}
