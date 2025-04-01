/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_rendering.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:36:51 by mtocu             #+#    #+#             */
/*   Updated: 2025/04/01 18:38:22 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** Renders the minimap by looping through the entire map grid.
** Each tile is drawn as a 7x7 square based on its character:
** - '1' (wall) is black.
** - '0' (empty space) uses the ceiling colour.
** - 'N', 'S', 'E', 'W' (player position) is yellow.
** - Any other character is rendered dark grey.
*/
void	draw_minimap(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->map_tab[i])
	{
		j = 0;
		while (map->map_tab[i][j])
		{
			if (map->map_tab[i][j] == '1')
				draw_minimap_tile(map, j * 7, i * 7, 0x000000);
			else if (map->map_tab[i][j] == '0')
				draw_minimap_tile(map, j * 7, i * 7, \
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
** - Draws the player’s new position in yellow.
** - Restores the previous position with ceiling colour if moved.
** - Prevents redrawing if the player hasn't moved in that axis.
*/
void	update_minimap(t_map *map, int old_x, int old_y)
{
	draw_minimap_tile(map, (int)map->pos_x * 7, (int)map->pos_y * 7, 0xEEEE20);
	if ((int)map->pos_x != old_x)
		draw_minimap_tile(map, old_x * 7, old_y * 7, \
		compose_color(0, map->rgb_sky[0], map->rgb_sky[1], map->rgb_sky[2]));
	if ((int)map->pos_y != old_y)
		draw_minimap_tile(map, old_x * 7, old_y * 7, \
		compose_color(0, map->rgb_sky[0], map->rgb_sky[1], map->rgb_sky[2]));
}

/*
** Draws a single pixel on the minimap image buffer at (x, y).
** - Verifies the coordinates are within screen limits.
** - Writes the given colour at the computed memory location.
*/
void	minimap_place_pixel(t_map *map, int x, int y, int color)
{
	char	*pixel;

	if (y < 0 || y > map->display_height - 1 || x < 0
		|| x > map->display_width - 1)
		return ;
	pixel = (map->minimap.pixels + (y * map->minimap.line_size
				+ x * (map->minimap.bits_per_pixel / 8)));
	*(int *)pixel = color;
}

/*
** Draws a 7x7 square tile on the minimap starting at (x, y).
** - Used to represent a single tile (wall, space, player, etc).
** - Calls `minimap_place_pixel` for every pixel in the tile.
*/
void	draw_minimap_tile(t_map *map, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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
