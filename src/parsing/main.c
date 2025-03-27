/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:04:46 by mtocu             #+#    #+#             */
/*   Updated: 2025/02/05 13:33:02 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** Validates the command line arguments.
** Ensures exactly one argument is passed, the file can be opened,
** and it has a ".cub" extension.
*/
int	validate_args(int argc, char **argv)
{
	int	len;
	int	fd;

	if (argc < 2)
		return (printf(RED "Error:\nThe Map was not provided.\n" RST), 1);
	else if (argc != 2)
		return (printf(RED "Error\nMultiple arguments provided.\n" RST), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (printf(RED "Error:\nError opening the file.\n" RST), 1);
	close(fd);
	len = ft_strlen(argv[1]);
	if (!ft_strnstr(argv[1] + len - 4, ".cub", len))
		return (printf(RED "Error:\nWrong '.cub' format\n" RST), 1);
	return (0);
}

/*
** Initializes all fields in the map structure to safe defaults.
** Prepares the map struct for parsing and game setup.
*/
void	init_map_data(t_map *map)
{
	int	i;

	i = 0;
	map->map_tab = NULL;
	map->width_map = 0;
	map->height_map = 0;
	map->rgb_floor[0] = -1;
	map->rgb_floor[1] = -1;
	map->rgb_floor[2] = -1;
	map->rgb_sky[0] = -1;
	map->rgb_sky[1] = -1;
	map->rgb_sky[2] = -1;
	map->line = NULL;
	map->map_line = NULL;
	while (i < 5)
	{
		map->img[i].image = NULL;
		map->img[i].pixels = NULL;
		if (i < 4)
			map->img[i].path = NULL;
		i++;
	}
	map->minimap.image = NULL;
	map->minimap.pixels = NULL;
}

/*
** Program entry point.
** Validates arguments, initializes data, parses the map,
** and starts the game loop.
*/
int	main(int argc, char **argv)
{
	t_map	map;
	int		fd;

	init_map_data(&map);
	if (validate_args(argc, argv) == 1)
		exit(1);
	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
	{
		printf(RED "Error\nFailed to open file\n" RST);
		return (37);
	}
	if (!parse_map(&map, fd))
	{
		free_string_array(map.map_tab);
		return (38);
	}
	start_game(&map);
	return (0);
}
