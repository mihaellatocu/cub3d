/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:39:17 by mtocu             #+#    #+#             */
/*   Updated: 2025/04/01 18:39:18 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** Combines transparency and RGB values into a single 32-bit color integer.
** This is used for pixel drawing. `t` stands for transparency (alpha).
** Format: 0xTTRRGGBB
*/
int	compose_color(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/*
** Draws the background of the game screen.
** The upper half is filled with the sky color, and the lower half with
 the floor color.
** This is done by looping through every pixel on screen and using `place_pixel`.
*/
void	render_background(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	while (x < map->display_width)
	{
		y = 0;
		while (y < map->display_height)
		{
			if (y < map->display_height / 2)
				place_pixel(map, x, y, compose_color(0, map->rgb_sky[0],
						map->rgb_sky[1], map->rgb_sky[2]));
			else
				place_pixel(map, x, y, compose_color(0, map->rgb_floor[0],
						map->rgb_floor[1], map->rgb_floor[2]));
			y++;
		}
		++x;
	}
}

/*
** Main rendering function called each frame.
** 1. Draws background (sky and floor).
** 2. Executes raycasting to draw walls.
** 3. Displays the rendered main image and minimap in the game window.
** Returns 0 to comply with mlx_loop_hook signature.
*/
int	render_frame(t_map *map)
{
	render_background(map);
	exec_raycasting(map);
	mlx_put_image_to_window(map->mlx, map->mlx_win, map->img[4].image, 0, 0);
	mlx_put_image_to_window(map->mlx, map->mlx_win,
		map->minimap.image, 10, 10);
	return (0);
}
