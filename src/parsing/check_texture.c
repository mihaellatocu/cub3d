/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:58:05 by mtocu             #+#    #+#             */
/*   Updated: 2025/03/27 00:00:00 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** Checks a vertical slice of the map from top to bottom at column [x].
** Ensures the column is enclosed properly:
** - Top must be '1' or space.
** - All characters must be valid ('1', '0', 'NSEW', ' ').
** - Spaces must be surrounded vertically by walls.
*/
int	check_vertical_column(char **column, int y, int x, int height)
{
	while (y < height)
	{
		if (y == 0 && !is_allowed_char(column[y][x], "1 "))
			return (0);
		if (!is_allowed_char(column[y][x], "10NSEW "))
			return (0);
		if (column[y][x] == ' ')
		{
			if (y > 0 && column[y - 1][x] != '1')
				return (0);
			while (y < height && column[y][x] == ' ')
				y++;
			if (y < height && column[y][x] != '1')
				return (0);
		}
		if (y < height)
			y++;
	}
	if (!is_allowed_char(column[y - 1][x], "1 "))
		return (0);
	return (1);
}

/*
** Iterates across all vertical columns of the map (from x = 0 to width).
** Uses check_vertical_column to validate wall closure for each column.
*/
int	validate_vertical(t_map *map, int y, int x)
{
	while (map->map_tab[y][x])
	{
		if (!check_vertical_column(map->map_tab, y, x, map->height_map))
			return (0);
		x++;
	}
	return (1);
}

/*
** Validates a single horizontal line of the map:
** - Must start with '1' or space.
** - All characters must be valid.
** - Spaces must be enclosed by walls on both sides.
** - Ends must be '1' or space.
*/
int	check_horizontal_line(t_map *map, char *line, int x)
{
	while (line[x])
	{
		if (x == 0 && !is_allowed_char(line[x], "1 "))
			return (0);
		if (!is_allowed_char(line[x], "10NSEW "))
			parse_err(map, "Error\nInvalid character on map\n");
		if (line[x] == ' ')
		{
			if (x > 0 && line[x - 1] != '1')
				return (0);
			while (line[x] && line[x] == ' ')
				x++;
			if (line[x] && line[x] != '1')
				return (0);
		}
		if (line[x])
			x++;
	}
	if (!is_allowed_char(line[x - 1], "1 "))
		return (0);
	return (1);
}

/*
** Iterates through each row (horizontal line) of the map.
** Verifies that all rows are properly enclosed using check_horizontal_line.
*/
int	validate_horizontal(t_map *map, int y, int x)
{
	while (map->map_tab[y])
	{
		if (!check_horizontal_line(map, map->map_tab[y], x))
			return (0);
		y++;
	}
	return (1);
}

/*
** Main wall validation function.
** Checks both horizontal and vertical enclosure of the map.
** If any check fails, texture memory is freed and returns 0.
*/
int	validate_map_walls(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	if (!validate_horizontal(map, y, x) || !validate_vertical(map, y, x))
	{
		free_texture_data(map);
		return (0);
	}
	return (1);
}
