/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colours.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:12:47 by mtocu             #+#    #+#             */
/*   Updated: 2025/04/01 19:02:00 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** Validates the format of a texture path line and stores it in the map 
structure.
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
	int	prevWasComma;
	int	k;

	i = 0;
	comma = 0;
	prevWasComma = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!ft_isdigit(line[i]))
		return (0);
	while (line[i])
	{
		if (ft_isdigit(line[i]))
			prevWasComma = 0;
		else if (line[i] == ',')
		{
			comma++;
			if (prevWasComma)
				return (0);
			prevWasComma = 1;
		}
		else if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	k = i - 1;
	while (k >= 0 && ft_isspace(line[k]))
		k--;
	if (k >= 0 && !ft_isdigit(line[k]))
		return (0);
	return (comma == 2);
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
	int	k;

	i = 0;
	j = 0;
	while (j < 3)
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (!ft_isdigit(line[i]))
		{
			ft_printf("Error: expected digit at pos %d\n", i);
			return (0);
		}
		rgb[j] = ft_atoi(&line[i]);
		while (line[i] && ft_isdigit(line[i]))
			i++;
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (j < 2 && line[i++] != ',')
		{
			ft_printf("Error: expected comma at pos %d\n", i - 1);
			return (0);
		}
		j++;
	}
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i])
	{
		ft_printf("Error: extra characters after RGB values: '%s'\n", &line[i]);
		return (0);
	}
	k = -1;
	while (++k < 3)
	{
		if (rgb[k] < 0 || rgb[k] > 255)
		{
			ft_printf("Error: RGB value %d out of range\n", rgb[k]);
			return (0);
		}
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
void	parse_rgb_map(t_map *map, int *rgb, char *line)
{
	char	*ptr;

	// Find the first space after the identifier
	ptr = ft_strchr(line, ' ');
	if (!ptr)
		parse_err(map, "Error\nRGB line is incorrect\n");
	// Skip the space(s) to get to the RGB values
	while (*ptr && ft_isspace(*ptr))
		ptr++;
	// Now, ptr should point to something like "90, 54, 67"
	if (!parse_rgb_value(rgb, ptr))
		parse_err(map, "Error\nRGB line is incorrect\n");
}
