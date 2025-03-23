#include "../include/cub3d.h"

/**
 * @brief Frees a null-terminated array of strings.
 *
 * This function iterates over the given matrix of strings and frees each individual string,
 * then frees the matrix pointer itself.
 *
 * @param mtx The null-terminated array of strings to free.
 */
void free_char_matrix(char **mtx)
{
	int i;

	i = 0;
	while (mtx[i])
		free(mtx[i++]);
	free(mtx);
}

/**
 * @brief Frees a 2D integer matrix.
 *
 * This function frees each row of the integer matrix and then frees the matrix pointer.
 * The number of rows to free is determined by vars->game->map_height.
 *
 * @param vars Pointer to the t_vars structure, used to get the map height.
 * @param mtx The 2D integer matrix to free.
 */
void free_int_matrix(t_vars *vars, int **mtx)
{
	int i;

	i = 0;
	while (i < vars->game->map_height)
		free(mtx[i++]);
	free(mtx);
}

/**
 * @brief Frees the allocated memory for texture path strings.
 *
 * This function frees each of the texture path strings (north, south, west, east)
 * stored in the vars->paths structure.
 *
 * @param vars Pointer to the t_vars structure containing texture path data.
 */
void free_paths(t_vars *vars)
{
	free(vars->paths->no);
	free(vars->paths->so);
	free(vars->paths->we);
	free(vars->paths->ea);
}

/**
 * @brief Frees the allocated memory for color configuration strings.
 *
 * This function frees the ceiling and floor color strings stored in the vars->colors structure.
 *
 * @param vars Pointer to the t_vars structure containing color configuration data.
 */
void free_colors(t_vars *vars)
{
	free(vars->colors->c);
	free(vars->colors->f);
}

/**
 * @brief Destroys texture images and frees associated resources.
 *
 * This function iterates through the texture array in the game structure and destroys each
 * image using mlx_destroy_image(). For bonus mode, it continues to process additional textures.
 *
 * @param game Pointer to the t_game structure containing texture and MLX instance data.
 */
void free_textures(t_game *game)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
	while (BONUS && i < 8)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
}
