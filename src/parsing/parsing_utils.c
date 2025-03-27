#include "../../cub3d.h"

/*
** Validates if the map is fully enclosed by walls.
** Uses validate_map_structure to perform checks.
*/
int	validate_map_walls(t_map *map)
{
	if (!validate_map_structure(map))
	{
		printf(RED "Error:\nMap is not properly enclosed by walls.\n" RST);
		return (0);
	}
	return (1);
}

/*
** Handles parsing-related errors by cleaning up allocated resources
** and exiting the program with failure.
*/
void	handle_parse_error(t_map *map, char *message)
{
	printf(RED "%s" RST, message);
	if (map->map_tab)
		free_string_array(map->map_tab);
	if (map->line)
		free(map->line);
	if (map->map_line)
		free(map->map_line);
	free_texture_data(map);
	exit(EXIT_FAILURE);
}

/*
** Adjusts the map dimensions and ensures all rows are the same width
** by resizing each line to match the widest one.
*/
void	adjust_map_size(t_map *map)
{
	int	i;

	i = 0;
	set_map_dimensions(map, map->map_tab, 0, 0);
	if (map->height_map == 0 && map->width_map == 0)
		handle_parse_error(map,
			"Error:\nMap must contain exactly one player.\n");
	while (map->map_tab[i])
	{
		if (custom_strlen(map->map_tab[i]) <= map->width_map)
		{
			map->map_tab[i] = resize_line(map->map_tab[i], map->width_map);
			if (!map->map_tab[i])
				handle_parse_error(map,
					"Error:\nMemory allocation failed while resizing map line.\n");
		}
		i++;
	}
}

/*
** Reads and separates the config section and map layout from the input file.
** Collects map lines into a single joined string for later splitting.
*/
void	read_map_lines(int fd, t_map *map)
{
	char	*line;
	int		in_map;

	in_map = 0;
	while ((line = get_next_line(fd)))
	{
		if (!in_map)
		{
			if (analyse_map_line(map, line) == 1)
			{
				in_map = 1;
				free(line);
				continue ;
			}
		}
		else
		{
			if (line[0] != '\n')
				map->map_line = join_lines(map->map_line, line);
		}
		free(line);
	}
}

/*
** Main map parsing function: reads, processes, and validates the map.
** Converts raw lines into a 2D array and ensures the map is valid.
*/
int	parse_map(t_map *map, int fd)
{
	read_map_lines(fd, map);
	if (!map->map_line)
		handle_parse_error(map, "No map data found after config.");
	map->map_tab = ft_split(map->map_line, '\n');
	free(map->map_line);
	map->map_line = NULL;
	if (!map->map_tab)
		handle_parse_error(map, "Failed to split map into a 2D array.");
	set_map_dimensions(map, map->map_tab, 0, 0);
	if (!validate_map_walls(map))
		handle_parse_error(map,
			"Map is not properly enclosed by walls.");
	return (1);
}
