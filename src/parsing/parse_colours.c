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

void	check_value(int value, char first_letter, int k, t_map *file)
{
	if (k >= 3 || value < 0 || value > 255)
		ft_clean(file, RED "Error:\nColour nr or value is invalid." RST);
	else if (value >= 0 && value <= 255)
	{
		if (first_letter == 'F')
			file->floor[k] = value;
		else if (first_letter == 'C')
			file->ceiling[k] = value;
	}
}

void	pick_color(char *line, t_map *file)
{
	int		i;
	char	temp_nr[4];
	int		j;
	int		k;

	i = 1;
	k = 0;
	while (line[i])
	{
		j = 0;
		while (line[i] == ' ' || line[i] == ',')
			i++;
		while (line[i] >= '0' && line[i] <= '9')
			temp_nr[j++] = line[i++];
		temp_nr[j] = '\0';
		if (temp_nr[0] != '\0')
			check_value(ft_atoi(temp_nr), line[0], k, file);
		k++;
	}
}

int	valid_colours(char *line, t_map *file)
{
	int	i;

	i = 1;
	if (line == NULL)
		return (0);
	while (line[i])
	{
		if ((line[i] != ' ' && line[i] != ',' && line[i] < '0')
			|| (line[i] > '9'))
			ft_clean(file, "Error:\nThe colour configuration is incorrect.\n");
		i++;
	}
	return (1);
}

void	ft_clean(t_map *file, char *str)
{
	free_variables(file);
	printf("ft_clean called %s\n", str);
	exit (1);
}
