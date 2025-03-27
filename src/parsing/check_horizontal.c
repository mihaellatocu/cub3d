/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_horizontal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:00:00 by mtocu             #+#    #+#             */
/*   Updated: 2025/03/27 00:00:00 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** Checks if a single horizontal line in the map is valid.
** Ensures all characters are allowed and that spaces are surrounded by walls.
*/
int	check_horizontal_line(t_map *map, char *line, int x)
{
	while (line[x] && line[x] == ' ')
		x++;
	if (x == 0 && !is_allowed_char(line[x], "1 "))
		return (0);
	while (line[x])
	{
		if (!is_allowed_char(line[x], "10NSEW "))
			handle_parse_error(map, "Error:\nInvalid character in map line.\n");
		if (line[x] == ' ')
		{
			if (x > 0 && line[x - 1] != '1')
				return (0);
			while (line[x] && line[x] == ' ')
				x++;
			if (line[x] && line[x] != '1')
				return (0);
		}
		else
			x++;
	}
	if (x > 0 && !is_allowed_char(line[x - 1], "1 "))
		return (0);
	return (1);
}

/*
** Iterates over each row in the map and checks horizontal line validity.
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
** Validates the entire map's horizontal and vertical wall structure.
** Prints diagnostic messages and frees map resources if validation fails.
*/
int	validate_map_structure(t_map *map)
{
	printf(B"-> Checking horizontal walls...\n"RST);
	if (!map || !map->map_tab)
		handle_parse_error(map, RED"Invalid map data."RST);
	if (!validate_horizontal(map, 0, 0))
	{
		printf(RED"[X] Horizontal wall check failed.\n"RST);
		free_texture_data(map);
		return (0);
	}
	printf(G"[✓] Horizontal walls are fine.\n"RST);
	printf(B"-> Checking vertical walls...\n"RST);
	if (!validate_vertical(map, 0, 0))
	{
		printf(RED"[X] Vertical wall check failed.\n"RST);
		free_texture_data(map);
		return (0);
	}
	printf(G"[✓] Vertical walls are fine.\n"RST);
	return (1);
}
