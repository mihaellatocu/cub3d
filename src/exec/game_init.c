/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:30:00 by mtocu             #+#    #+#             */
/*   Updated: 2025/03/27 15:00:00 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** Handles fatal game errors by displaying a message and 
** cleaning up all resources.
** Frees all textures, map data, destroys window and display,
** and exits the program with failure status.
*/
void	handle_game_err(t_map *map, char *message)
{
	ft_printf(message);
	free_texture_data(map);
	free_str_array(map->map_tab);
	destroy_img(map);
	if (map->mlx_win)
		mlx_destroy_window(map->mlx, map->mlx_win);
	if (map->mlx)
		mlx_destroy_display(map->mlx);
	free(map->mlx);
	exit (EXIT_FAILURE);
}

/*
** Loads the four wall textures from the provided paths using MiniLibX.
** Also creates the main render image and obtains direct memory access
** to each texture and image buffer.
** If any of these fail, the function calls handle_game_err().
*/
void	init_textures(t_map *map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		map->img[i].image = mlx_xpm_file_to_image(map->mlx, map->img[i].path,
				&map->img[i].width, &map->img[i].height);
		if (!map->img[i].image)
			handle_game_err(map,RED "Error\nPath texture is incorrect\n" RST);
		i++;
	}
	map->img[4].image = mlx_new_image(map->mlx,
			map->display_width, map->display_height);
	if (!map->img[4].image)
		handle_game_err(map, RED "Error\nImage initialisation has failed\n" RST);
	i = 0;
	while (i < 5)
	{
		map->img[i].pixels = mlx_get_data_addr(map->img[i].image,
				&map->img[i].bits_per_pixel, &map->img[i].line_size, &map->img[i].endian);
		if (!map->img[i].pixels)
			handle_game_err(map,RED "Error\nImage initialisation has failed\n" RST);
		i++;
	}
}

/*
** Sets initial values for player movement speed, screen resolution,
** and the camera plane vector based on the initial player direction.
** The camera plane is perpendicular to the direction vector and is
** used to determine the Field of view in raycasting.
*/
void	check_game_init(t_map *map)
{
	map->speed = 0.09;
	map->rot_speed = 0.09;
	map->display_width = 1940;
	map->display_height = 1280;
	if (map->p_dir == 'N')
	{
		map->plane_x = 0.66;
		map->plane_y = 0;
	}
	if (map->p_dir == 'S')
	{
		map->plane_x = -0.66;
		map->plane_y = 0;
	}
	if (map->p_dir == 'W')
	{
		map->plane_x = 0;
		map->plane_y = 0.66;
	}
	if (map->p_dir == 'E')
	{
		map->plane_x = 0;
		map->plane_y = -0.66;
	}
}

/*
** Creates the minimap image based on the dimensions of the map.
** Retrieves memory access to the image and calls the
** draw_minimap function.
** If image creation fails, triggers a fatal error.
*/
void	init_minimap(t_map *map)
{
	map->minimap.image = mlx_new_image(map->mlx,
			map->width_map * 7, map->height_map * 7);
	if (!map->minimap.image)
		handle_game_err(map,RED "Error\nMinimap creation has failed\n" RST);
	map->minimap.pixels = mlx_get_data_addr(map->minimap.image,
			&map->minimap.bits_per_pixel, &map->minimap.line_size, &map->minimap.endian);
	if (!map->minimap.pixels)
		handle_game_err(map,RED "Error\nMinimap creation has failed\n" RST);
	draw_minimap(map);
}

/*
** Creates the minimap image based on the dimensions of the map.
** Retrieves memory access to the image and calls the draw_minimap function.
** If image creation fails, triggers a fatal error.
*/
int	start_game(t_map *map)
{
	check_game_init(map);
	map->mlx = mlx_init();
	if (!map->mlx)
		handle_game_err(map,RED "Error\nInitialisation of display has failed\n" RST);
	map->mlx_win = mlx_new_window(map->mlx, map->display_width,
			map->display_height, "Cub3D");
	if (!map->mlx_win)
		handle_game_err(map,RED "Error\nInitialisation of window has failed\n" RST);
	init_textures(map);
	init_minimap(map);
	mlx_loop_hook(map->mlx, &render_frame, map);
	mlx_hook(map->mlx_win, 2, 1L << 0, handle_key_input, map);
	mlx_hook(map->mlx_win, 6, 1L << 6, mouse_movement, map);
	mlx_hook(map->mlx_win, 17, 1L << 0, exit_game, map);
	mlx_loop(map->mlx);
	return (0);
}
