/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:29:45 by mtocu             #+#    #+#             */
/*   Updated: 2025/02/05 11:33:08 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** Frees all allocated MLX images used for rendering the game and minimap.
** This prevents memory leaks from textures and minimap image buffers.
** Checks if MLX is initialised before trying to destroy images.
*/
void	destroy_img(t_map *map)
{
	int	i;

	i = 0;
	if (map->mlx)
	{
		while (i < 5)
		{
			if (map->img[i].image)
				mlx_destroy_image(map->mlx, map->img[i].image);
			i++;
		}
		if (map->minimap.image)
			mlx_destroy_image(map->mlx, map->minimap.image);
	}
}

/*
** Frees all dynamically allocated file paths for the texture images.
** These are loaded from the map config (e.g., ./textures/wall_N.xpm).
*/
void	free_texture_data(t_map *map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (map->img[i].path)
			free(map->img[i].path);
		i++;
	}
}

/*
** Frees an array of strings (e.g., the map array).
** Each line is freed individually, then the array itself is freed.
*/
void	free_str_array(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	if (str)
		free(str);
}

/*
** Frees all allocated resources and cleanly exits the program.
** This includes textures, map lines, MLX images, window, and display.
** Prevents memory leaks and ensures proper shutdown.
*/
int	exit_game(t_map *map)
{
	free_texture_data(map);
	free_str_array(map->map_tab);
	destroy_img(map);
	mlx_destroy_window(map->mlx, map->mlx_win);
	mlx_destroy_display(map->mlx);
	free(map->mlx);
	exit (0);
}
