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
** Validates and assigns the texture path to a given direction.
** Expects exactly 2 entries: identifier and path.
** Also trims newline or whitespace from the path string.
*/
void	assign_texture_path(t_map *map, char **path, char **split_line)
{
	char	*trimmed;
	int		i;

	i = 0;
	while (split_line[i])
		i++;
	if (i == 3 && split_line[2][0] == '\n')
		free(split_line[i--]);
	if (i != 2 || *path)
	{
		free_string_array(split_line);
		handle_parse_error(map,
			"Error:\nInvalid or duplicate texture path.\n");
	}
	trimmed = ft_strtrim(split_line[1], "\n ");
	if (!trimmed)
		handle_parse_error(map, "Error:\nMemory allocation failed.\n");
	*path = trimmed;
	free_string_array(split_line);
}

/*
** Validates if a string is a valid RGB line format (e.g., 255,200,123).
** Requires the line to start/end with a digit and contain exactly two commas.
*/
int	parse_rgb_line(char *line)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	if (!ft_isdigit(line[0]) ||
		!ft_isdigit(line[custom_strlen(line) - 1]) ||
		custom_strlen(line) > 11)
		return (0);
	while (line[i])
	{
		if (line[i] == ',')
		{
			comma++;
			if (line[i + 1] == ',')
				return (0);
		}
		else if (!ft_isdigit(line[i]))
			return (0);
		i++;
	}
	return (comma == 2);
}

/*
** Extracts and validates three RGB integer values from a line.
** Returns 0 if values are not within [0,255] or format is invalid.
*/
int	parse_rgb_values(int *rgb, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!parse_rgb_line(line))
		return (0);
	while (j < 3 && line[i])
	{
		if (j == 0)
		{
			rgb[j++] = ft_atoi(line);
		}
		else if (line[i] == ',')
		{
			rgb[j++] = ft_atoi(line + i + 1);
		}
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
** Parses the RGB line into three integers and assigns it to the target array.
** Frees split_line and throws an error if validation fails.
*/
void	parse_rgb_map(t_map *map, int *rgb, char **split_line)
{
	int	i;

	i = 0;
	while (split_line[i])
		i++;
	if (i == 3 && split_line[2][0] == '\n')
		free(split_line[i--]);
	if (i != 2 || !parse_rgb_values(rgb, split_line[1]))
	{
		free_string_array(split_line);
		handle_parse_error(map, "Error:\nInvalid RGB color format.\n");
	}
	free_string_array(split_line);
}