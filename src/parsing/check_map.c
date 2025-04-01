/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:29:44 by mtocu             #+#    #+#             */
/*   Updated: 2025/03/27 17:30:00 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** Called when a player starting direction character 
** ('N', 'S', 'E', 'W') is found.
** Stores the player's initial position (i, j) and sets the direction 
** vector (dir_x, dir_y)
** according to the compass direction. This direction is used for 
** movement and raycasting.
*/
void	set_player_position(t_map *map, char direction, int i, int j)
{
	map->pos_y = (double)i;
	map->pos_x = (double)j;
	map->p_dir = direction;
	if (direction == 'N')
	{
		map->dir_x = 0;
		map->dir_y = -1;
	}
	else if (direction == 'S')
	{
		map->dir_x = 0;
		map->dir_y = 1;
	}
	else if (direction == 'W')
	{
		map->dir_x = -1;
		map->dir_y = 0;
	}
	else if (direction == 'E')
	{
		map->dir_x = 1;
		map->dir_y = 0;
	}
}

/*
** Iterates through the map lines (array) to determine:
** - The maximum line length (width of map)
** - The total number of lines (height of map)
** - The player's spawn position using set_player_position
** The function also checks that exactly one player position is defined;
** if not, the map dimensions are not set.
*/

void	set_map_dimensions(t_map *map, char **array, int i, int j)
{
	int	tmp;
	int	count_player;

	tmp = 0;
	count_player = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			if (is_allowed_char(array[i][j], "NSEW"))
			{
				set_player_position(map, array[i][j], i, j);
				count_player++;
			}
			j++;
		}
		if (j > tmp)
			tmp = j;
		i++;
	}
	if (count_player != 1)
		return ;
	map->width_map = tmp;
	map->height_map = i;
}


/*
** Validates that all textures and RGB colours 
** (floor and ceiling) have been set.
** If any texture is missing or if any RGB component is -1 (unset), 
** an error is raised.
*/
void	check_stat(t_map *map)
{
	int	i;

	i = 0;
	if (!map->img[0].path || !map->img[1].path
		|| !map->img[2].path || !map->img[3].path)
		parse_err(map, RED "Error\nMissing textures\n" RST);
	while (i < 3)
	{
		if (map->rgb_floor[i] == -1 || map->rgb_sky[i] == -1)
			parse_err(map, RED "Error\nMissing colors\n" RST);
		i++;
	}
}

/*
** Parses configuration lines at the top of the .cub file.
** These lines specify texture paths and RGB values for the 
** floor and ceiling.
** - Accepts 6 configuration lines: NO, SO, WE, EA, F, C.
** - Uses a static counter (i) to stop parsing config lines 
** after all 6 are read.
** - If any line is invalid, a parsing error is triggered.
** - Once all 6 entries are processed, it calls check_stat() 
** to confirm all are set.
**
** Returns:
**   - 0 if the line was valid but config is not yet complete
**   - 1 when all 6 configuration lines have been processed
*/
int	analyze_map_line(t_map *map, char *line)
{
	static int	i = 0;

	while (i < 6)
	{
		ft_printf("Debug: raw line: '%s'\n", line);
		if (line[0] == ' ' && !line[1])
			return (0);
		if (!ft_strncmp(line, "NO ", 3))
			assign_texture_path(map, &map->img[0].path, ft_split(line, ' '));
		else if (!ft_strncmp(line, "SO ", 3))
			assign_texture_path(map, &map->img[1].path, ft_split(line, ' '));
		else if (!ft_strncmp(line, "WE ", 3))
			assign_texture_path(map, &map->img[2].path, ft_split(line, ' '));
		else if (!ft_strncmp(line, "EA ", 3))
			assign_texture_path(map, &map->img[3].path, ft_split(line, ' '));
		else if (!ft_strncmp(line, "F ", 2))
			parse_rgb_map(map, map->rgb_floor, line);
		else if (!ft_strncmp(line, "C ", 2))
			parse_rgb_map(map, map->rgb_sky, line);
		
		else
			parse_err(map,RED "Error\nIncorrect data on texture/color\n" RST);
		i++;
		return (0);
	}
	check_stat(map);
	return (1);
}
