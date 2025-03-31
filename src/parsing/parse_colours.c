/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colours.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:12:47 by mtocu             #+#    #+#             */
/*   Updated: 2025/02/05 11:33:44 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** Validates the format of a texture path line and stores it in the map structure.
** - Expects exactly 2 elements in split_line (e.g., "NO path/to/file").
** - Handles an optional newline-only third string caused by splitting.
** - Stores the path in *path, trimming trailing newline if necessary.
*/
void	assign_texture_path(t_map *map, char **path, char **split_line)
{
	int	i;

	i = 0;
	while (split_line[i])
		i++;
	if (i == 3 && split_line[2][0] == '\n')
		free(split_line[i--]);
	if (i != 2 || *path)
	{
		free_str_array(split_line);
		parse_err(map, "Error\nTexture line is incorrect\n");
	}
	*path = ft_strjoin(*path, split_line[1]);
	if (path[0][cub3d_strlen(*path)] == '\n')
		path[0][cub3d_strlen(*path)] = '\0';
	free_str_array(split_line);
}

/*
** Checks if an RGB string has valid formatting.
** - Must start and end with a digit.
** - Should not contain repeated commas or non-digit/non-comma characters.
** - Must contain exactly two commas and be under 12 characters in length.
*/
int	parse_rgb(char *line)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	if (!ft_isdigit(line[0]) || !ft_isdigit(line[cub3d_strlen(line) - 1])
		|| cub3d_strlen(line) > 11)
		return (0);
	while (line[i + 1])
	{
		if (line[i] == ',')
			comma++;
		if (line[i] == ',' && line[i + 1] && line[i + 1] == ',')
			return (0);
		else if ((!ft_isdigit(line[i])) && line[i] != ',')
			return (0);
		i++;
	}
	if (comma != 2)
		return (0);
	return (1);
}

/*
** Parses and assigns RGB values from a valid string to an int array.
** - Uses `ft_atoi` to convert each section of the string.
** - Verifies that each RGB value is between 0 and 255.
** - Returns 1 on success, 0 on invalid format or out-of-bounds values.
*/
int	parse_rgb_value(int *rgb, char *line)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	if (!parse_rgb(line))
		return (0);
	while (line[i])
	{
		if (i == 0)
			rgb[0] = ft_atoi(line);
		else if (line[i] == ',')
			rgb[j++] = ft_atoi(line + i + 1);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (0);
		i++;
	}
	return (1);
}

/*
** Processes and validates RGB input split from a line.
** - Ensures the line contains 2 valid arguments (prefix + RGB).
** - Handles cases where extra spaces lead to a third empty split.
** - Calls `parse_rgb_value()` to assign RGB values to the map.
** - Exits with an error if any check fails.
*/
void	parse_rgb_map(t_map *map, int *rgb, char **split_line)
{
	int	i;

	i = 0;
	while (split_line[i])
		i++;
	if (i == 3 && split_line[2][0] == '\n')
		free(split_line[i--]);
	if ((i != 2) || !parse_rgb_value(rgb, split_line[1]))
	{
		free_str_array(split_line);
		parse_err(map, "Error\nRGB line is incorrect\n");
	}
	free_str_array(split_line);
}
