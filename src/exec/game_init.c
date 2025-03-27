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


/**
 * Handles game-related errors, cleans up resources, and exits the program.
 */
void	handle_game_error(t_map *map, char *message)
{
	printf(RED "\n[ERROR] %s" RST, message);
	free_texture_data(map);
	free_string_array(map->map_tab);
	destroy_images(map);
	if (map->mlx_win)
		mlx_destroy_window(map->mlx, map->mlx_win);
	if (map->mlx)
		mlx_destroy_display(map->mlx);
	free(map->mlx);
	exit(EXIT_FAILURE);
}

/**
 * Loads a single texture image from the given path and assigns it to the texture index.
 * Retrieves the image data address for a given texture.
 */
void	init_textures(t_map *map)
{
	int	 texture_idx;
	texture_idx = 0;
	while (texture_idx < 4)
	{
		if (!map->img[texture_idx].path)
			handle_game_error(map, "Missing texture path before loading XPM");
		printf("Texture[%d] path: %s\n", texture_idx, map->img[texture_idx].path);
		map->img[texture_idx].image = mlx_xpm_file_to_image(map->mlx,
				map->img[texture_idx].path, &map->img[texture_idx].width, &map->img[texture_idx].height);
		if (!map->img[texture_idx].image)
			handle_game_error(map, "Texture path is invalid or missing");
		texture_idx++;
	}
	map->img[4].image = mlx_new_image(map->mlx,
			map->display_width, map->display_height);
	if (!map->img[4].image)
		handle_game_error(map, "Main image creation failed");
	texture_idx = 0;
	while (texture_idx < 5)
	{
		map->img[texture_idx].pixels = mlx_get_data_addr(map->img[texture_idx].image,
				&map->img[texture_idx].bits_per_pixel, &map->img[texture_idx].line_size,
				&map->img[texture_idx].endian);
		if (!map->img[texture_idx].pixels)
			handle_game_error(map, "Image data address acquisition failed");
		texture_idx++;
	}
}

/**
 * Initializes game parameters including player direction and screen dimensions.
 */
void	init_game_stats(t_map *map)
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
	else if (map->p_dir == 'S')
	{
		map->plane_x = -0.66;
		map->plane_y = 0;
	}
	else if (map->p_dir == 'W')
	{
		map->plane_x = 0;
		map->plane_y = 0.66;
	}
	else if (map->p_dir == 'E')
	{
		map->plane_x = 0;
		map->plane_y = -0.66;
	}
}

/**
 * Creates and sets up the minimap.
 */
void	init_minimap(t_map *map)
{
	map->minimap.image = mlx_new_image(map->mlx,
			map->width_map * 7, map->height_map * 7);
	if (!map->minimap.image)
		handle_game_error(map, "Minimap image creation failed");
	map->minimap.pixels = mlx_get_data_addr(map->minimap.image,
			&map->minimap.bits_per_pixel, &map->minimap.line_size,
			&map->minimap.endian);
	if (!map->minimap.pixels)
		handle_game_error(map, "Minimap data address acquisition failed");
	draw_minimap(map);
}

/**
 * Starts the game by initializing the window, textures, minimap, and hooks.
 */
int	start_game(t_map *map)
{
	init_game_stats(map);
	map->mlx = mlx_init();
	if (!map->mlx)
		handle_game_error(map, "Display initialization failed");
	map->mlx_win = mlx_new_window(map->mlx, map->display_width,
			map->display_height, "Cub3D");
	if (!map->mlx_win)
		handle_game_error(map, "Window creation failed");
	init_textures(map);
	init_minimap(map);
	mlx_loop_hook(map->mlx, &render_frame, map);
	mlx_hook(map->mlx_win, 2, 1L << 0, handle_key_input, map);
	mlx_hook(map->mlx_win, 6, 1L << 6, handle_mouse_movement, map);
	mlx_hook(map->mlx_win, 17, 1L << 0, exit_game, map);
	mlx_loop(map->mlx);
	return (0);
}
