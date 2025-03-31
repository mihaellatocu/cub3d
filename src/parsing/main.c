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
** Validates that the given filename ends with the ".cub" extension.
** Returns 1 if valid, 0 otherwise.
*/
int	ft_test_extension(char *argv)
{
	int	i;
	int	j;

	i = ft_strlen(argv);
	j = 0;
	i -= 4;
	while (argv[i] != '\0')
	{
		if (j == 0 && argv[i] != '.')
			return (0);
		if (j == 1 && argv[i] != 'c')
			return (0);
		if (j == 2 && argv[i] != 'u')
			return (0);
		if (j == 3 && argv[i] != 'b')
			return (0);
		i++;
		j++;
	}
	return (1);
}

/*
** Checks if the provided file path has a valid .cub extension,
** and if the file can be opened and is not empty.
** Returns 1 if valid, 0 otherwise.
*/
int	validate_args(char *argv)
{
	int		fd;
	int		result;
	char	test[1];

	if (!ft_test_extension(argv))
	{
		ft_printf("Error\nBad extension\n");
		return (0);
	}
	fd = open(argv, O_RDONLY);
	result = read(fd, test, 1);
	if (result <= 0)
	{
		if (result == 0)
			ft_printf("Error\nEmpty file\n");
		else if (result < 0)
			ft_printf("Error\nInvalid entry\n");
		return (0);
	}
	close(fd);
	return (1);
}

/*
** Initializes the t_map structure to default values.
** Resets all fields before parsing the map and loading textures.
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
		map->img[i].path = NULL;
		i++;
	}
	map->minimap.image = NULL;
}

/*
** Entry point of the program.
** Validates arguments, parses the map, and starts the game loop.
*/
int	main(int ac, char **av)
{
	t_map	map;
	int		fd;

	init_map_data(&map);
	if (ac != 2)
		parse_err(&map, "Error\nOne argument required\n");
	if (!validate_args(av[1]))
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd <= 0)
	{
		ft_printf("Error\nFailed to open file\n");
		return (37);
	}
	if (!parse_map(&map, fd))
	{
		free_str_array(map.map_tab);
		return (38);
	}
	start_game(&map);
	return (0);
}
