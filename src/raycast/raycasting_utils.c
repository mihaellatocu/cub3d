#include "../../cub3d.h"

/*
** Returns the color value of the pixel located at (x, y) within a texture.
** If coordinates are out of bounds, returns a fallback magenta color (0xFF00FF).
** Triggers an error if the pixel buffer is not properly initialised.
*/
int	get_pixel_color(t_map *map, int x, int y, int tex_idx)
{
	t_texture	*tex;
	char		*pixel_addr;

	tex = &map->img[tex_idx];
	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0xFF00FF);
	if (!tex->pixels)
		handle_game_error(map, "Texture pixels is NULL");
	pixel_addr = tex->pixels + (y * tex->line_size
			+ x * (tex->bits_per_pixel / 8));
	return (*(int *)pixel_addr);
}