/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:36:11 by mtocu             #+#    #+#             */
/*   Updated: 2025/04/01 18:36:27 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** Draws a single pixel on the screen at (x, y) with a specific colour.
** - First checks if the coordinates are within display boundaries.
** - Then calculates the memory location of the pixel and sets its value.
** - Uses the 5th image buffer (index 4), which represents the screen.
*/
void	place_pixel(t_map *map, int x, int y, int color)
{
	char	*pixel;

	if (y < 0 || y > map->display_height - 1 || x < 0
		|| x > map->display_width - 1)
		return ;
	pixel = (map->img[4].pixels + (y * map->img[4].line_size
				+ x * (map->img[4].bits_per_pixel / 8)));
	*(int *)pixel = color;
}

/*
** Calculates the height and vertical start/end points of the wall slice.
** - Line height is based on the inverse of perpendicular wall distance.
** - Start and end define the vertical range for drawing the wall texture.
** - Ensures the range does not go out of display bounds.
*/
void	define_column(t_map *map, int *line_height, int *start, int *end)
{
	*line_height = map->display_height / map->perpwalldist;
	*start = -*line_height / 2 + map->display_height / 2;
	if (*start < 0)
		*start = 0;
	*end = *line_height / 2 + map->display_height / 2;
	if (*end >= map->display_height)
		*end = map->display_height - 1;
}

/*
** Determines which part of the wall texture to display for a given ray.
** - wall_x: the exact position the wall was hit (used for texture x-axis).
** - tex_x: horizontal position in the texture image.
** - Handles texture flipping based on direction of the ray and wall side.
** - Calculates step: how much to move vertically in the texture per
** screen pixel.
** - tex_pos: starting position within the texture based on wall height.
*/
void	define_texture_coords(t_map *map, int start, int line_height)
{
	if (map->wall_side == 0)
		map->wall_x = map->pos_y + map->perpwalldist * map->ray_dir_y;
	else
		map->wall_x = map->pos_x + map->perpwalldist * map->ray_dir_x;
	map->wall_x -= floor(map->wall_x);
	map->tex_x = map->wall_x * 128;
	if (map->wall_side == 0 && map->ray_dir_x > 0)
		map->tex_x = 128 - map->tex_x - 1;
	if (map->wall_side == 1 && map->ray_dir_y < 0)
		map->tex_x = 128 - map->tex_x - 1;
	map->step = 1.0 * 128 / line_height;
	map->tex_pos = (start - map->display_height / 2
			+ line_height / 2) * map->step;
}

/*
** Helper to draw one pixel column of a wall using the correct texture.
** - Gets the pixel color from the selected texture at the right coordinates.
** - Sends it to the framebuffer using `place_pixel`.
*/
void	draw(t_map *map, int x, int texture)
{
	int	color;

	color = get_pixel_color(map, map->tex_x, map->tex_y, texture);
	place_pixel(map, x, map->start, color);
}

/*
** Draws a vertical column of textured wall pixels at position x on screen.
** - Sets up the height and position of the column with `define_column`.
** - Prepares texture alignment with `define_texture_coords`.
** - Loops through each vertical pixel in the column to render it.
** - Selects the proper texture (N, S, E, W) based on ray direction and side.
*/
void	draw_col_texture(t_map *map, int x)
{
	int	line_height;

	define_column(map, &line_height, &map->start, &map->end);
	define_texture_coords(map, map->start, line_height);
	while (map->start < map->end)
	{
		map->tex_y = (int)map->tex_pos & (128 - 1);
		map->tex_pos += map->step;
		if (map->wall_side == 1 && map->ray_dir_y < 0)
			draw(map, x, DIR_SOUTH);
		else if (map->wall_side == 1 && map->ray_dir_y > 0)
			draw(map, x, DIR_NORTH);
		else if (map->wall_side == 0 && map->ray_dir_x < 0)
			draw(map, x, DIR_WEST);
		else if (map->wall_side == 0 && map->ray_dir_x > 0)
			draw(map, x, DIR_EAST);
		map->start++;
	}
}
