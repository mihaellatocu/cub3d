/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@.fr>                         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-30 19:29:44 by mtocu             #+#    #+#             */
/*   Updated: 2025-01-30 19:29:44 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ce fac daca am spatii in interior?
//len line poate fi trimis in main

#include "../cub3d.h"

int	check_cardinal(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

void	check_cardinal_points(t_map *file, int len_line, int i)
{
	int	j;

	j = 0;
	while (j < len_line)
	{
		if (check_cardinal(file->map[i][j]) == 1)
		{
			file->poz_x = i;
			file->poz_y = j;
			file->nr_cardinals++;
		}
		j++;
	}
}

void	check_left_wall(t_map *file, char *row, int i, int len_line)
{
	int	j;

	j = 0;
	while (j < len_line)
	{
		if (row[0] == '0' || check_cardinal(row[0]))
			ft_clean(file, RED "Error:\nThe left wall is not correct.\n" RST);
		else if (row[0] == ' ')
		{
			while (j < len_line)
			{
				while (row[j + 1] == ' ')
				{
					j++;
					if (i > 1 && i < file->nr_rows_map - 1 && j > 0 && j
						< len_line - 1 && ((file->map[i - 1][j] != '1' \
						&& file->map[i - 1][j] != ' ') || (file->map[i + 1][j]
						!= '1' && file->map[i + 1][j] != ' ')))
						ft_clean(file, RED"Error:\nLeft wall is invalid.\n"RST);
				}
				if (row[j + 1] == '1')
					return ;
				else
					ft_clean(file, RED "Error:\nLeft wall is invalid.\n" RST);
			}
		}
		j++;
	}
}

void	check_right_wall(t_map *file, char *row, int len_line, int i)
{
	int	prev;
	int	next;

	if (row[len_line] != '1')
		ft_clean (file, RED "Error:\nThe right wall is invalid." RST);
	if (i > 1)
	{
		prev = ft_strlen(file->map[i - 1]);
		if (prev > len_line + 1 && (file->map[i - 1][len_line + 1] == '0' \
		|| check_cardinal(file->map[i - 1][len_line + 1])))
			ft_clean (file, RED "Error:\nThe right wall edge is invalid." RST);
	}
	if (i < file->nr_rows_map - 2)
	{
		next = ft_strlen(file->map[i + 1]);
		if (next > len_line + 1 && (file->map[i + 1][len_line + 1] == '0' \
		|| check_cardinal(file->map[i + 1][len_line + 1])))
			ft_clean (file, RED "Error:\nThe right wall edge is invalid." RST);
	}
}

void	check_north_wall(t_map *file, int len_line)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (j < len_line)
	{
		if (file->map[i][j] == '0' || check_cardinal(file->map[i][j]))
			ft_clean(file, RED "Error:\nThe top row is incorrect." RST);
		else if (file->map[i][j] == ' ')
		{
			while (file->map[i + 1][j] == ' ')
			{
				i++;
				if (j > 0 && (file->map[i - 1][j - 1] != ' ' \
					&& file->map[i][j - 1] != '1'))
					ft_clean(file, RED "Error:\nThe top row is incorrect." RST);
				if (j + 1 < len_line && file->map[i - 1][j + 1] != ' ' \
					&& file->map[i][j + 1] != '1')
					ft_clean(file, RED "Error:\nThe top row is incorrect." RST);
			}
			if (file->map[i + 1][j] != '1')
				ft_clean(file, RED "Error:\nThe top row is incorrect." RST);
		}
		j++;
		i = 0;
	}
}

void	check_south_wall(t_map *file, int len_line)
{
	int	i;
	int	j;
	int	k;

	i = file->nr_rows_map - 1;
	j = 0;
	while (j < len_line)
	{
		if (file->map[i][j] != '1' && file->map[i][j] != ' ')
			ft_clean(file, RED "Error:\nThe south wall is incorrect.\n" RST);
		if (file->map[i][j] == ' ')
		{
			k = i;
			while (k > 0 && file->map[k][j] == ' ')
			{
				k--;
				if (j > 0 && j + 1 < len_line && file->map[k][j] == ' ' \
				&& ((file->map[k][j - 1] != '1' && file->map[k][j - 1] != ' ') \
				|| (file->map[k][j + 1] != '1' && file->map[k][j + 1] != ' ')))
					ft_clean(file, RED "Error:\nSouth wall not valid.\n" RST);
			}
			if (file->map[k][j] != '1' || k == 0)
				ft_clean(file, RED "Error:\nSouth wall is incorrect.\n" RST);
		}
		j++;
	}
}

void	remove_spaces_map(char *row)
{
	int	j;

	j = ft_strlen(row) - 1;
	while (j > 1 && row[j] == ' ')
	{
		row[j] = '\0';
		j--;
	}
}

int	check_map(t_map *file)
{
	int	i;
	int	len_line;

	i = 0;
	if (file->nr_rows_map < 2)
		ft_clean(file, RED "Error:\nThe map is incorrect.\n" RST);
	while (i < file->nr_rows_map)
	{
		remove_spaces_map(file->map[i]);
		len_line = ft_strlen(file->map[i]);
		printf("line is %d - and lenght line: %d\n", i, len_line);
		if (ft_strlen(file->map[i]) == 0)
			ft_clean(file, RED "Error:\nThe line is empty.\n" RST);
		check_cardinal_points(file, len_line, i);
		if (i == 0)
			check_north_wall(file, len_line);
		check_left_wall(file, file->map[i], i, len_line);
		check_right_wall(file, file->map[i], len_line - 1, i);
		i++;
	}
	len_line = ft_strlen(file->map[file->nr_rows_map -1]);
	check_south_wall(file, len_line);
	if (file->nr_cardinals != 1)
		ft_clean(file, RED "Error:\nNumber of cardinals are incorrect.\n" RST);
	return (0);
}
