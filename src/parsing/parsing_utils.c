/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:27:37 by mtocu             #+#    #+#             */
/*   Updated: 2025/04/01 18:29:27 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** Verifies if the parsed map is correctly enclosed by walls.
** - Calls `validate_map_walls()` to check both horizontal and 
vertical boundaries.
** - Prints a coloured error message if validation fails.
** - Returns 1 if the map is valid, otherwise 0.
*/
int	error_map(t_map *map)
{
	if (!validate_map_walls(map))
	{
		ft_printf(RED "Error\nMap not closed\n" RST);
		return (0);
	}
	return (1);
}

/*
** Handles parsing-related errors by cleaning memory and exiting.
** - Frees the map structure: `map_tab`, `line`, `map_line`, and texture paths.
** - Displays a custom error message (should include a newline).
** - Terminates the program with `EXIT_FAILURE`.
*/
void	parse_err(t_map *map, char *message)
{
	ft_printf(message);
	if (map->map_tab)
		free_str_array(map->map_tab);
	if (map->line)
		free(map->line);
	if (map->map_line)
		free(map->map_line);
	free_texture_data(map);
	exit (EXIT_FAILURE);
}

/*
** Computes the map dimensions and ensures all rows are equally wide.
** - Uses `set_map_dimensions()` to set `map->width_map` and `height_map`.
** - If multiple or no players are found, dimensions will be zero, 
triggering an error.
** - Resizes all lines to match the maximum width (for proper vertical parsing).
** - Ensures all rows are the same length by appending spaces if needed.
*/
void	fix_size_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	set_map_dimensions(map, map->map_tab, i, j);
	if (map->height_map == 0 && map->width_map == 0)
		parse_err(map, RED "Error\nOnly one player is required on map\n" RST);
	while (map->map_tab[i])
	{
		if (cub3d_strlen(map->map_tab[i]) <= map->width_map)
		{
			map->map_tab[i] = resize_line(map->map_tab[i], map->width_map);
			if (!map->map_tab[i])
				parse_err(map, RED "Error\nMalloc error\n" RST);
		}
		i++;
	}
}

/*
** Reads and accumulates map lines from a file descriptor.
** - Uses `get_next_line()` to read one line at a time.
** - If a line is empty (newline), it's converted to a space to preserve spacing.
** - `analyze_map_line()` is used to parse and validate 
** config lines (textures/RGB).
** - Valid map lines are appended with `/` using `strjoin_line()`.
** - Checks for invalid use of `/` in the map and exits if found.
** - Splits the resulting `map_line` by `/` into the `map_tab` array.
** - Calls `fix_size_map()` to normalize line lengths.
*/
void	read_map_lines(int fd, t_map *map)
{
	while (42)
	{
		map->line = get_next_line(fd);
		if (!map->line)
			break ;
		if (map->line[0] == '\n')
			map->line[0] = ' ';
		if (analyze_map_line(map, map->line) == 1)
		{
			if (ft_strchr(map->line, '/'))
				parse_err(map, RED "Error\nInvalid character in map\n" RST);
			map->map_line = strjoin_line(map->map_line, map->line);
		}
		free(map->line);
	}
	map->map_tab = ft_split(map->map_line, '/');
	free(map->map_line);
	map->map_line = NULL;
	fix_size_map(map);
}

/*
** Entry point for parsing the map file after opening it.
** - Calls `read_map_lines()` to load and store the map.
** - Then runs `error_map()` to check wall validity.
** - If parsing is successful, closes the file and returns 1.
** - Returns 0 if map validation fails.
*/
int	parse_map(t_map *map, int fd)
{
	read_map_lines(fd, map);
	if (!error_map(map))
		return (0);
	close(fd);
	return (1);
}
