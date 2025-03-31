#include "../../cub3d.h"

/*
** Returns the color value of the pixel located at (x, y) within a texture.
** If coordinates are out of bounds, returns a fallback magenta color (0xFF00FF).
** Triggers an error if the pixel buffer is not properly initialised.
*/
int	get_pixel_color(t_map *map, int x, int y, int i)
{
	return (*(int *)(map->img[i].pixels
		+ (y * map->img[i].line_size + x * (map->img[i].bits_per_pixel / 8))));
}
