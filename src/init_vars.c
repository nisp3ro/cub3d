#include "../include/cub3d.h"

/**
 * @brief Initializes the game environment.
 *
 * This function sets up the MLX (MiniLibX) environment, creates the window and an image buffer,
 * and initializes the pointer for the world map. Depending on the BONUS flag, it creates either
 * a standard window ("Cub3d") or a bonus version window ("Cub3d_bonus").
 *
 * @param vars Pointer to the t_vars structure containing game data.
 */
static void init_game(t_vars *vars)
{
	vars->game->mlx = mlx_init();
	if (!vars->game->mlx)
		return (perror("mlx"), exit(ERROR));
	if (BONUS)
		vars->game->win = mlx_new_window(vars->game->mlx, WIDTH, HEIGHT, "Cub3d_bonus");
	else
		vars->game->win = mlx_new_window(vars->game->mlx, WIDTH, HEIGHT, "Cub3d");
	if (!vars->game->win)
		return (perror("mlx"), exit(ERROR));
	vars->game->img.img = mlx_new_image(vars->game->mlx, WIDTH, HEIGHT);
	if (!vars->game->img.img)
		return (perror("mlx"), exit(ERROR));
	vars->game->img.addr = mlx_get_data_addr(vars->game->img.img,
			&vars->game->img.bpp, &vars->game->img.line_length, &vars->game->img.endian);
	vars->game->world_map = NULL;
}

/**
 * @brief Initializes the main variables and structures for the game.
 *
 * This function allocates and initializes the primary structures used by the program,
 * including t_vars, t_game, t_player, t_paths, and t_colors. It also sets default values
 * for file-related fields and calls init_game() to set up the MLX environment.
 *
 * @param vars Double pointer to the t_vars structure that will be allocated and initialized.
 */
void init_vars(t_vars **vars)
{
	*vars = ft_calloc(1, sizeof(t_vars));
	if (!*vars)
		return (perror("malloc"), exit(ERROR));
	(*vars)->game = ft_calloc(1, sizeof(t_game));
	(*vars)->player = ft_calloc(1, sizeof(t_player));
	(*vars)->paths = ft_calloc(1, sizeof(t_paths));
	(*vars)->colors = ft_calloc(1, sizeof(t_colors));
	if (!(*vars)->game || !(*vars)->player || !(*vars)->paths || !(*vars)->colors)
		return (perror("malloc"), exit(ERROR));
	(*vars)->map_path_fd = 0;
	(*vars)->bytes_read = 0;
	(*vars)->map_path = NULL;
	(*vars)->buffer = NULL;
	(*vars)->file = NULL;
	(*vars)->map = NULL;
	init_game((*vars));
}
