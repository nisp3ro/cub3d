#include "../include/cub3d.h"

/**
 * @brief Loads the north wall texture from the specified path.
 *
 * This function loads the north wall texture using the path stored in vars->paths->no.
 * It creates an image using mlx_xpm_file_to_image and retrieves its address using mlx_get_data_addr.
 * If the texture fails to load or the address is NULL, an error message is printed and the program exits.
 *
 * @param vars Pointer to the t_vars structure containing game and texture data.
 */
static void north(t_vars *vars)
{
	t_game	*game;

	game = vars->game;
	game->textures[0].img = mlx_xpm_file_to_image(game->mlx, vars->paths->no,
			&game->textures[0].width, &game->textures[0].height);
	if (!game->textures[0].img)
		return (ft_putstr_fd("Error:\nInvalid texture.\n", STDERR_FILENO),
			exit(1));
	game->textures[0].addr = mlx_get_data_addr(game->textures[0].img,
			&game->textures[0].bpp, &game->textures[0].line_length,
			&game->textures[0].endian);
	if (game->textures[0].addr == NULL)
		exit(1);
}

/**
 * @brief Loads the south wall texture from the specified path.
 *
 * This function loads the south wall texture using the path stored in vars->paths->so.
 * It creates an image with mlx_xpm_file_to_image and obtains its address via mlx_get_data_addr.
 * If the texture fails to load or the address retrieval fails, an error message is printed and the program exits.
 *
 * @param vars Pointer to the t_vars structure containing game and texture data.
 */
static void south(t_vars *vars)
{
	t_game	*game;

	game = vars->game;
	game->textures[1].img = mlx_xpm_file_to_image(game->mlx, vars->paths->so,
			&game->textures[1].width, &game->textures[1].height);
	if (!game->textures[1].img)
		return (ft_putstr_fd("Error:\nInvalid texture.\n", STDERR_FILENO),
			exit(1));
	game->textures[1].addr = mlx_get_data_addr(game->textures[1].img,
			&game->textures[1].bpp, &game->textures[1].line_length,
			&game->textures[1].endian);
	if (game->textures[1].addr == NULL)
		exit(1);
}

/**
 * @brief Loads the east wall texture from the specified path.
 *
 * This function loads the east wall texture using the path stored in vars->paths->ea.
 * It creates an image with mlx_xpm_file_to_image and obtains its address with mlx_get_data_addr.
 * In case of an error during texture loading or address retrieval, it prints an error message and exits.
 *
 * @param vars Pointer to the t_vars structure containing game and texture data.
 */
static void east(t_vars *vars)
{
	t_game	*game;

	game = vars->game;
	game->textures[2].img = mlx_xpm_file_to_image(game->mlx, vars->paths->ea,
			&game->textures[2].width, &game->textures[2].height);
	if (!game->textures[2].img)
		return (ft_putstr_fd("Error:\nInvalid texture.\n", STDERR_FILENO),
			exit(1));
	game->textures[2].addr = mlx_get_data_addr(game->textures[2].img,
			&game->textures[2].bpp, &game->textures[2].line_length,
			&game->textures[2].endian);
	if (game->textures[2].addr == NULL)
		exit(1);
}

/**
 * @brief Loads the west wall texture from the specified path.
 *
 * This function loads the west wall texture using the path stored in vars->paths->we.
 * It creates an image with mlx_xpm_file_to_image and retrieves its address using mlx_get_data_addr.
 * If the texture fails to load or if the address is NULL, it prints an error message and exits.
 *
 * @param vars Pointer to the t_vars structure containing game and texture data.
 */
static void west(t_vars *vars)
{
	t_game	*game;

	game = vars->game;
	game->textures[3].img = mlx_xpm_file_to_image(game->mlx, vars->paths->we,
			&game->textures[3].width, &game->textures[3].height);
	if (!game->textures[3].img)
		return (ft_putstr_fd("Error:\nInvalid texture.\n", STDERR_FILENO),
			exit(1));
	game->textures[3].addr = mlx_get_data_addr(game->textures[3].img,
			&game->textures[3].bpp, &game->textures[3].line_length,
			&game->textures[3].endian);
	if (game->textures[3].addr == NULL)
		exit(1);
}

/**
 * @brief Loads all wall textures and bonus textures (if enabled).
 *
 * This function calls north(), south(), east(), and west() to load the corresponding wall textures.
 * If BONUS mode is enabled, it also calls load_textures_bonus() to load additional textures.
 *
 * @param vars Pointer to the t_vars structure containing game and texture data.
 * @return int Returns OK on successful texture loading.
 */
int load_textures(t_vars *vars)
{
	north(vars);
	south(vars);
	east(vars);
	west(vars);
	if (BONUS)
		load_textures_bonus(vars);
	return (OK);
}
