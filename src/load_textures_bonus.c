#include "../include/cub3d.h"

/**
 * @brief Loads the first door texture from the file "textures/door_1.xpm".
 *
 * This function copies the path to a temporary buffer, loads the XPM image using MLX,
 * and sets up the image data address. If the texture fails to load, it prints an error
 * message and exits the program.
 *
 * @param game Pointer to the t_game structure containing MLX data.
 */
static void door1(t_game *game)
{
	char path[20];

	ft_strcpy(path, "textures/door_1.xpm");
	game->textures[4].img = mlx_xpm_file_to_image(game->mlx, path,
			&game->textures[4].width, &game->textures[4].height);
	if (!game->textures[4].img)
		return (ft_putstr_fd("Error:\nInvalid texture.\n", STDERR_FILENO),
			exit(1));
	game->textures[4].addr = mlx_get_data_addr(game->textures[4].img,
			&game->textures[4].bpp, &game->textures[4].line_length,
			&game->textures[4].endian);
}

/**
 * @brief Loads the second door texture from the file "textures/door_2.xpm".
 *
 * This function copies the path to a temporary buffer, loads the XPM image using MLX,
 * and sets up the image data address. If the texture fails to load, it prints an error
 * message and exits the program.
 *
 * @param game Pointer to the t_game structure containing MLX data.
 */
static void door2(t_game *game)
{
	char path[20];

	ft_strcpy(path, "textures/door_2.xpm");
	game->textures[5].img = mlx_xpm_file_to_image(game->mlx, path,
			&game->textures[5].width, &game->textures[5].height);
	if (!game->textures[5].img)
		return (ft_putstr_fd("Error:\nInvalid texture.\n", STDERR_FILENO),
			exit(1));
	game->textures[5].addr = mlx_get_data_addr(game->textures[5].img,
			&game->textures[5].bpp, &game->textures[5].line_length,
			&game->textures[5].endian);
}

/**
 * @brief Loads the third door texture from the file "textures/door_3.xpm".
 *
 * This function copies the path to a temporary buffer, loads the XPM image using MLX,
 * and sets up the image data address. If the texture fails to load, it prints an error
 * message and exits the program.
 *
 * @param game Pointer to the t_game structure containing MLX data.
 */
static void door3(t_game *game)
{
	char path[20];

	ft_strcpy(path, "textures/door_3.xpm");
	game->textures[6].img = mlx_xpm_file_to_image(game->mlx, path,
			&game->textures[6].width, &game->textures[6].height);
	if (!game->textures[6].img)
		return (ft_putstr_fd("Error:\nInvalid texture.\n", STDERR_FILENO),
			exit(1));
	game->textures[6].addr = mlx_get_data_addr(game->textures[6].img,
			&game->textures[6].bpp, &game->textures[6].line_length,
			&game->textures[6].endian);
}

/**
 * @brief Loads the fourth door texture from the file "textures/door_4.xpm".
 *
 * This function copies the path to a temporary buffer, loads the XPM image using MLX,
 * and sets up the image data address. If the texture fails to load, it prints an error
 * message and exits the program.
 *
 * @param game Pointer to the t_game structure containing MLX data.
 */
static void door4(t_game *game)
{
	char path[20];

	ft_strcpy(path, "textures/door_4.xpm");
	game->textures[7].img = mlx_xpm_file_to_image(game->mlx, path,
			&game->textures[7].width, &game->textures[7].height);
	if (!game->textures[7].img)
		return (ft_putstr_fd("Error:\nInvalid texture.\n", STDERR_FILENO),
			exit(1));
	game->textures[7].addr = mlx_get_data_addr(game->textures[7].img,
			&game->textures[7].bpp, &game->textures[7].line_length,
			&game->textures[7].endian);
}

/**
 * @brief Loads all door textures for bonus mode.
 *
 * This function calls door1(), door2(), door3(), and door4() to load the door textures
 * used in the bonus version of Cub3D.
 *
 * @param vars Pointer to the t_vars structure containing game data.
 * @return int Returns OK on success.
 */
int load_textures_bonus(t_vars *vars)
{
	door1(vars->game);
	door2(vars->game);
	door3(vars->game);
	door4(vars->game);
	return (OK);
}
