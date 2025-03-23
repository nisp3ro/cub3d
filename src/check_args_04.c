#include "../include/cub3d.h"

/**
 * @brief Assigns RGB values and computes hexadecimal color codes.
 *
 * This helper function takes two arrays of strings (temp for ceiling and temp2 for floor)
 * representing the red, green, and blue components of the respective colors. It converts these
 * values from strings to integers, stores them in the vars->colors structure, and computes the
 * hexadecimal color codes by bit-shifting and OR-ing the RGB components.
 *
 * @param vars Pointer to the t_vars structure containing color information.
 * @param temp Array of strings representing the ceiling RGB values.
 * @param temp2 Array of strings representing the floor RGB values.
 */
static void assign_colors_2(t_vars *vars, char **temp, char **temp2)
{
	vars->colors->c_r = ft_atoi(temp[0]);
	vars->colors->c_g = ft_atoi(temp[1]);
	vars->colors->c_b = ft_atoi(temp[2]);
	vars->colors->f_r = ft_atoi(temp2[0]);
	vars->colors->f_g = ft_atoi(temp2[1]);
	vars->colors->f_b = ft_atoi(temp2[2]);
	vars->colors->c_hex = (vars->colors->c_r << 16)
		| (vars->colors->c_g << 8) | (vars->colors->c_b);
	vars->colors->f_hex = (vars->colors->f_r << 16)
		| (vars->colors->f_g << 8) | (vars->colors->f_b);
}

/**
 * @brief Parses color strings and assigns color values.
 *
 * This function splits the ceiling and floor color strings (stored in vars->colors->c and vars->colors->f)
 * by commas to extract the individual RGB components. It verifies that each color contains exactly three components.
 * Then, it calls assign_colors_2() to convert and assign the RGB values and compute the hexadecimal color codes.
 * Finally, it frees the temporary arrays used for splitting.
 *
 * @param vars Pointer to the t_vars structure containing color configuration.
 */
void assign_colors(t_vars *vars)
{
	int		i;
	char	**temp;
	char	**temp2;

	i = 0;
	temp = ft_split(vars->colors->c, ',');
	if (!temp)
		return (perror("malloc"), exit(1));
	while (temp[i])
		i++;
	if (i != 3)
		return (ft_putstr_fd("Error:\nInvalid map.\n", STDERR_FILENO), exit(1));
	i = 0;
	temp2 = ft_split(vars->colors->f, ',');
	if (!temp2)
		return (perror("malloc"), exit(1));
	while (temp2[i])
		i++;
	if (i != 3)
		return (ft_putstr_fd("Error:\nInvalid map.\n", STDERR_FILENO), exit(1));
	assign_colors_2(vars, temp, temp2);
	free_char_matrix(temp);
	free_char_matrix(temp2);
}
