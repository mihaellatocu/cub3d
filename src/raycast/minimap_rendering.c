#include "../../cub3d.h"

/*
** Renders the minimap based on the map layout.
** Tiles are coloured depending on content: wall, space, or player start.
*/
void	draw_minimap(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map_tab[i])
	{
		j = 0;
		while (map->map_tab[i][j])
		{
			if (map->map_tab[i][j] == '1')
				draw_minimap_tile(map, j * 7, i * 7, 0x000000);
			else if (map->map_tab[i][j] == '0')
				draw_minimap_tile(map, j * 7, i * 7,
					compose_color(0, map->rgb_sky[0], map->rgb_sky[1], map->rgb_sky[2]));
			else if (is_allowed_char(map->map_tab[i][j], "NSEW"))
				draw_minimap_tile(map, j * 7, i * 7, 0xEEEE20);
			else
				draw_minimap_tile(map, j * 7, i * 7, 0x050505);
			j++;
		}
		i++;
	}
}

/*
** Updates the player's position on the minimap.
** If the player has moved, redraws the old tile background.
*/
void	update_minimap(t_map *map, int old_x, int old_y)
{
	draw_minimap_tile(map, (int)map->pos_x * 7,
		(int)map->pos_y * 7, 0xEEEE20);
	if ((int)map->pos_x != old_x || (int)map->pos_y != old_y)
		draw_minimap_tile(map, old_x * 7, old_y * 7,
			compose_color(0, map->rgb_sky[0], map->rgb_sky[1], map->rgb_sky[2]));
}

/*
** Places a pixel at (x, y) in the minimap image with the given colour.
** Ensures drawing is within bounds of the minimap buffer.
*/
void	minimap_place_pixel(t_map *map, int x, int y, int color)
{
	char	*pixel;

	if (y < 0 || y > map->display_height - 1
		|| x < 0 || x > map->display_width - 1)
		return ;
	pixel = (map->minimap.pixels + (y * map->minimap.line_size
			+ x * (map->minimap.bits_per_pixel / 8)));
	*(int *)pixel = color;
}

/*
** Draws a 7x7 square tile on the minimap at the specified (x, y) position.
** Each tile represents a map cell (wall, floor, player, etc).
*/
void	draw_minimap_tile(t_map *map, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 7)
	{
		j = 0;
		while (j < 7)
		{
			minimap_place_pixel(map, x + j, y + i, color);
			j++;
		}
		i++;
	}
}