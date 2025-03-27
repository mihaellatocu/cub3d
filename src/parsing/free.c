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
** Destroys all images stored in the map, including minimap image,
** and sets their pointers to NULL to avoid use-after-free.
*/
void	destroy_images(t_map *map)
{
	int	i;

	i = 0;
	if (map->mlx)
	{
		while (i < 5)
		{
			if (map->img[i].image)
			{
				mlx_destroy_image(map->mlx, map->img[i].image);
				map->img[i].image = NULL;
			}
			i++;
		}
		if (map->minimap.image)
		{
			mlx_destroy_image(map->mlx, map->minimap.image);
			map->minimap.image = NULL;
		}
	}
}

/*
** Frees dynamically allocated file path strings for textures in the map.
*/
void	free_texture_data(t_map *map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (map->img[i].path)
		{
			free(map->img[i].path);
			map->img[i].path = NULL;
		}
		i++;
	}
}

/*
** Frees a null-terminated array of strings and the array itself.
*/
void	free_string_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/*
** Performs full cleanup of allocated resources and exits the program.
*/
int	exit_game(t_map *map)
{
	free_texture_data(map);
	free_string_array(map->map_tab);
	destroy_images(map);
	if (map->mlx_win)
		mlx_destroy_window(map->mlx, map->mlx_win);
	if (map->mlx)
	{
		mlx_destroy_display(map->mlx);
		free(map->mlx);
	}
	exit(EXIT_SUCCESS);
}