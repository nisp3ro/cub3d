#include "../include/cub3d.h"

/**
 * @brief Cleans up and exits the program.
 *
 * This function terminates the MLX loop, destroys the current image, textures, window,
 * and display, and frees all allocated memory for the game, map, paths, colors, and other
 * associated structures. It is called to perform a clean exit when the program terminates.
 *
 * @param vars Pointer to the t_vars structure containing all game-related data.
 */
void clean_exit(t_vars *vars)
{
	mlx_loop_end(vars->game->mlx);
	mlx_destroy_image(vars->game->mlx, vars->game->img.img);
	free_textures(vars->game);
	mlx_destroy_window(vars->game->mlx, vars->game->win);
	mlx_destroy_display(vars->game->mlx);
	free(vars->game->mlx);
	free_char_matrix(vars->file);
	free_int_matrix(vars, vars->game->world_map);
	free_paths(vars);
	free_colors(vars);
	free(vars->paths);
	free(vars->player);
	free(vars->colors);
	free(vars->game);
	free(vars);
}
