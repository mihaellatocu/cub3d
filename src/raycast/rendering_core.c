#include "../../cub3d.h"

/*
** Combines four values into a single 32-bit ARGB color integer.
** Used for specifying pixel colors.
*/
int	compose_color(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/*
** Fills the background of the frame.
** The top half is filled with sky color, and the bottom half with floor color.
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
				place_pixel(map, x, y, compose_color(0,
					map->rgb_sky[0], map->rgb_sky[1], map->rgb_sky[2]));
			else
				place_pixel(map, x, y, compose_color(0,
					map->rgb_floor[0], map->rgb_floor[1], map->rgb_floor[2]));
			y++;
		}
		x++;
	}
}

/*
** Main render loop for one frame.
** Draws the background, walls via raycasting, and overlays the minimap.
*/
int	render_frame(t_map *map)
{
	render_background(map);
	execute_raycasting(map);
	mlx_put_image_to_window(map->mlx, map->mlx_win, map->img[4].image, 0, 0);
	mlx_put_image_to_window(map->mlx, map->mlx_win, map->minimap.image, 10, 10);
	return (0);
}
