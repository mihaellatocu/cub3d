#include "../../cub3d.h"

/*
** Places a pixel at (x, y) in the final frame image buffer with the given color.
** Only plots the pixel if the coordinates are within the display bounds.
*/
void	place_pixel(t_map *map, int x, int y, int color)
{
	char	*pixel;

	if (y < 0 || y > map->display_height - 1
		|| x < 0 || x > map->display_width - 1)
		return ;
	pixel = (map->img[4].pixels + (y * map->img[4].line_size
			+ x * (map->img[4].bits_per_pixel / 8)));
	*(int *)pixel = color;
}

/*
** Calculates the height of the vertical wall slice, and where it should start and end.
** Ensures the values are clamped within the screen bounds.
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
** Computes which part of the texture to use for the vertical wall slice.
** Handles orientation adjustments and calculates texture stepping.
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
** Draws a vertical textured column onto the frame.
** Determines which texture to use based on wall direction.
*/
void	draw_column_texture(t_map *map, int x)
{
	int	line_height;

	define_column(map, &line_height, &map->start, &map->end);
	define_texture_coords(map, map->start, line_height);
	while (map->start < map->end)
	{
		map->tex_y = (int)map->tex_pos & (128 - 1);
		map->tex_pos += map->step;
		if (map->wall_side == 1 && map->ray_dir_y < 0)
			place_pixel(map, x, map->start,
				get_pixel_color(map, map->tex_x, map->tex_y, DIR_SOUTH));
		else if (map->wall_side == 1 && map->ray_dir_y > 0)
			place_pixel(map, x, map->start,
				get_pixel_color(map, map->tex_x, map->tex_y, DIR_NORTH));
		else if (map->wall_side == 0 && map->ray_dir_x < 0)
			place_pixel(map, x, map->start,
				get_pixel_color(map, map->tex_x, map->tex_y, DIR_WEST));
		else if (map->wall_side == 0 && map->ray_dir_x > 0)
			place_pixel(map, x, map->start,
				get_pixel_color(map, map->tex_x, map->tex_y, DIR_EAST));
		map->start++;
	}
}