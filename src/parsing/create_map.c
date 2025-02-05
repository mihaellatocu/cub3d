/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:19:16 by mtocu             #+#    #+#             */
/*   Updated: 2025/02/05 11:33:05 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	free_matrix(t_map *file)
{
	int	k;

	k = 0;
	while (k < file->nr_rows_map && file->map[k])
	{
		free(file->map[k]);
		k++;
	}
	free(file->map);
}

void	free_temp_matrix(t_map *file)
{
	int	k;

	k = 0;
	while (k < file->nr_rows_map && file->temp_map[k])
	{
		free(file->temp_map[k]);
		k++;
	}
	free(file->temp_map);
}

void	error_malloc(void)
{
	printf("Error: Memory allocation failed.\n");
	exit(1);
}

void	create_map(char *line, t_map *file)
{
	int	i;

	i = -1;
	file->temp_map = malloc(sizeof (char *) * (file->nr_rows_map + 2));
	if (!file->temp_map)
		error_malloc();
	while (++i < file->nr_rows_map)
		file->temp_map[i] = ft_strdup(file->map[i]);
	file->temp_map[i] = ft_strdup(line);
	file->temp_map[i + 1] = NULL;
	free_matrix(file);
	file->nr_rows_map++;
	file->map = malloc(sizeof(char *) * (file->nr_rows_map + 1));
	if (!file->map)
		error_malloc();
	i = 0;
	while (file->temp_map[i])
	{
		file->map[i] = ft_strdup(file->temp_map[i]);
		i++;
	}
	free_temp_matrix(file);
}

int	valid_elements(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N'
			&& line[i] != 'E' && line[i] != 'W'
			&& line[i] != 'S' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	print_map(t_map *file)
{
	int	i;
	int	j;

	j = 0;
	for (i = 0; i < file->nr_rows_map; i++)
	{
		printf("my map is:  _");
		for (j = 0; j < ft_strlen(file->map[i]); j++)
		{
			printf("%c ", file->map[i][j]);
		}
		printf("_\n");
	}
}