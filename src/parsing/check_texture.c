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
** Checks if the space above the current cell is valid.
** If the above character exists and is not a wall ('1'), returns 0 (invalid).
*/
int	is_valid_space_above(char **column, int y, int x)
{
	int	row_len;

	if (y > 0 && column[y - 1])
	{
		row_len = ft_strlen(column[y - 1]);
		if (x < row_len && column[y - 1][x] != '1')
			return (0);
	}
	return (1);
}

/*
** Returns the character at position [y][x] in the map,
** or a space character if the index is out of bounds.
*/
char	get_column_char(char **column, int y, int x)
{
	int	row_len;

	if (!column[y])
		return (' ');
	row_len = ft_strlen(column[y]);
	if (x < row_len)
		return (column[y][x]);
	return (' ');
}

/*
** Skips over empty spaces in a vertical column.
** Checks that the next non-space character is a wall ('1').
*/
int	skip_spaces_check_wall(char **column, int *y, int x, int height)
{
	char	current;

	while (*y < height && column[*y])
	{
		current = get_column_char(column, *y, x);
		if (current != ' ')
			break ;
		(*y)++;
	}
	if (*y < height && column[*y])
	{
		current = get_column_char(column, *y, x);
		if (current != '1')
			return (0);
	}
	return (1);
}

/*
** Validates a vertical column in the map.
** Ensures that spaces are enclosed and valid characters are used.
*/
int	check_vertical_column(char **column, int y, int x, int height)
{
	char	current;

	while (y < height && column[y])
	{
		current = get_column_char(column, y, x);
		if (y == 0 && !is_allowed_char(current, "1 "))
			return (0);
		if (!is_allowed_char(current, "10NSEW "))
			return (0);
		if (current == ' ')
		{
			if (!is_valid_space_above(column, y, x))
				return (0);
			if (!skip_spaces_check_wall(column, &y, x, height))
				return (0);
			continue ;
		}
		y++;
	}
	if (y > 0 && column[y - 1])
	{
		current = get_column_char(column, y - 1, x);
		if (!is_allowed_char(current, "1 "))
			return (0);
	}
	return (1);
}

/*
** Iterates over each column index and validates vertical structure for the map.
*/
int	validate_vertical(t_map *map, int y, int x)
{
	int	max_width;

	if (!map || !map->map_tab)
		return (0);
	max_width = map->width_map;
	while (x < max_width)
	{
		if (!check_vertical_column(map->map_tab, y, x, map->height_map))
			return (0);
		x++;
	}
	return (1);
}