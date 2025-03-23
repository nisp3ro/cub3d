#include "../include/cub3d.h"

/**
 * @brief Handles mouse movement to rotate the player.
 *
 * This function is called when the mouse is moved. It calculates the angle difference based on
 * the deviation from the center of the window and rotates the player accordingly using the
 * rotate_player() function. After processing the movement, the mouse pointer is reset to the
 * center of the window.
 *
 * @param x The current x-coordinate of the mouse.
 * @param y The current y-coordinate of the mouse (unused).
 * @param game Pointer to the game structure containing necessary data.
 * @return int Always returns 0.
 */
int mouse_move(int x, int y, t_game *game)
{
	static int	center_x;
	double		angle;

	(void)y;
	center_x = WIDTH / 2;
	if (x != center_x)
	{
		angle = (x - center_x) * 0.001;
		rotate_player(game, angle);
		mlx_mouse_move(game->mlx, game->win, center_x, HEIGHT / 2);
	}
	return (0);
}

/**
 * @brief Draws alternating title images to the window.
 *
 * This function loads two XPM images from the "textures" directory and alternates them
 * on the window for 25 iterations, creating a simple animated effect. Each image is displayed
 * for 100 milliseconds. If an image fails to load, appropriate cleanup is performed.
 *
 * @param mlx Pointer to the MLX instance.
 * @param win Pointer to the MLX window.
 */
void draw_images(void *mlx, void *win)
{
	void	*img1;
	void	*img2;
	int		i;

	img1 = mlx_xpm_file_to_image(mlx, "textures/title01.xpm", &(int){WIDTH}, &(int){HEIGHT});
	if (!img1)
		return ;
	img2 = mlx_xpm_file_to_image(mlx, "textures/title02.xpm", &(int){WIDTH}, &(int){HEIGHT});
	if (!img2)
		return ((void)mlx_destroy_image(mlx, img1));
	i = 0;
	while (i < 25)
	{
		if (i % 2 == 0)
			mlx_put_image_to_window(mlx, win, img1, 0, 0);
		else
			mlx_put_image_to_window(mlx, win, img2, 0, 0);
		usleep(100000);
		i++;
	}
	mlx_destroy_image(mlx, img1);
	mlx_destroy_image(mlx, img2);
}

/**
 * @brief Entry point of the Cub3D program.
 *
 * This function initializes game variables, checks command line arguments and map validity,
 * loads textures, and displays an animated title screen. It sets up various MLX hooks for key
 * presses, key releases, mouse movements (bonus mode), and window closing, then enters the main
 * rendering loop. Finally, it cleans up resources upon exit.
 *
 * @param argc The number of command line arguments.
 * @param argv Array of command line argument strings.
 * @return int Returns 0 if the program completes successfully.
 */
int main(int argc, char *argv[])
{
	t_vars	*vars;

	init_vars(&vars);
	if (!(check_args(argc, argv, vars) == OK && check_map_valid(vars) == OK))
		exit(1);
	load_textures(vars);
	draw_images(vars->game->mlx, vars->game->win);
	mlx_mouse_hide(vars->game->mlx, vars->game->win);
	mlx_hook(vars->game->win, 2, 1L << 0, key_press, vars);
	mlx_hook(vars->game->win, 3, 1L << 1, key_release, vars->game);
	mlx_hook(vars->game->win, 17, 0, close_window, vars);
	mlx_loop_hook(vars->game->mlx, render, vars);
	if (BONUS)
	{
		mlx_mouse_move(vars->game->mlx, vars->game->win, WIDTH / 2, HEIGHT / 2);
		mlx_hook(vars->game->win, 6, 1L << 6, mouse_move, vars->game);
	}
	mlx_loop(vars->game->mlx);
	clean_exit(vars);
	return (0);
}
