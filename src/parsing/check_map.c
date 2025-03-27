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

/* Places the player on the map based on the direction found in the map.
   Sets the player's orientation vector accordingly (dir_x and dir_y). */
void	set_player_position(t_map *map, char direction, int tile_row, int tile_col)
{
	map->pos_y = (double)tile_row;
	map->pos_x = (double)tile_col;
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

/* Iterates through the map array to determine maximum width (longest row),
   player spawn location, and total height of the map.
   Fails silently if more than one player position is found. */
void	set_map_dimensions(t_map *map, char **array, int row_index, int col_index)
{
	int	max_width;
	int	player_count;

	max_width = 0;
	player_count = 0;
	while (array[row_index])
	{
		col_index = 0;
		while (array[row_index][col_index])
		{
			if (is_allowed_char(array[row_index][col_index], "NSEW"))
			{
				set_player_position(map, array[row_index][col_index],
					row_index, col_index);
				player_count++;
			}
			col_index++;
		}
		if (col_index > max_width)
			max_width = col_index;
		row_index++;
	}
	if (player_count != 1)
		return ;
	map->width_map = max_width;
	map->height_map = row_index;
}

/* Confirms that all required texture paths and both RGB values for
   floor and ceiling have been assigned. Otherwise, triggers a parse error. */
void	verify_map_assets(t_map *map)
{
	int	index;

	index = 0;
	if (!map->img[0].path || !map->img[1].path
		|| !map->img[2].path || !map->img[3].path)
		handle_parse_error(map, RED"Error:\nMissing textures.\n"RST);
	while (index < 3)
	{
		if (map->rgb_floor[index] == -1 || map->rgb_sky[index] == -1)
			handle_parse_error(map, RED"Error:\nMissing colour values.\n"RST);
		index++;
	}
}

/* Determines the type of config line (texture or colour),
   splits it, and dispatches it to the appropriate assignment function.
   If the line is malformed, it triggers a parse error. */
static void	handle_config_line(t_map *map, char *line, char **split)
{
	if (!ft_strncmp(line, "NO", 2))
		assign_texture_path(map, &map->img[0].path, split);
	else if (!ft_strncmp(line, "SO", 2))
		assign_texture_path(map, &map->img[1].path, split);
	else if (!ft_strncmp(line, "WE", 2))
		assign_texture_path(map, &map->img[2].path, split);
	else if (!ft_strncmp(line, "EA", 2))
		assign_texture_path(map, &map->img[3].path, split);
	else if (!ft_strncmp(line, "F", 1))
		parse_rgb_map(map, map->rgb_floor, split);
	else if (!ft_strncmp(line, "C", 1))
		parse_rgb_map(map, map->rgb_sky, split);
}

/* Cleans the incoming line, checks if it's a valid config entry,
   and routes to the corresponding handler.
   Returns 1 when all required map values are loaded, 0 otherwise. */
int	analyse_map_line(t_map *map, char *line)
{
	char	*clean_line;
	char	**split;

	clean_line = ft_strtrim(line, " \t\n\r");
	split = NULL;
	if (!clean_line)
		handle_parse_error(map, RED"Memory allocation failed.\n"RST);
	if (clean_line[0] == '\0')
	{
		free(clean_line);
		return (0);
	}
	if ((!ft_strncmp(clean_line, "NO", 2) && clean_line[2] == ' ')
		|| (!ft_strncmp(clean_line, "SO", 2) && clean_line[2] == ' ')
		|| (!ft_strncmp(clean_line, "WE", 2) && clean_line[2] == ' ')
		|| (!ft_strncmp(clean_line, "EA", 2) && clean_line[2] == ' ')
		|| (!ft_strncmp(clean_line, "F", 1) && clean_line[1] == ' ')
		|| (!ft_strncmp(clean_line, "C", 1) && clean_line[1] == ' '))
		split = ft_split(clean_line, ' ');
	else
	{
		free(clean_line);
		handle_parse_error(map, RED"Error:\nInvalid texture/colour entry.\n"RST);
	}
	handle_config_line(map, clean_line, split);
	free(clean_line);
	if (map->img[0].path && map->img[1].path && map->img[2].path
		&& map->img[3].path && map->rgb_floor[0] != -1
		&& map->rgb_sky[0] != -1)
		return (1);
	return (0);
}
