/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:19:16 by mtocu             #+#    #+#             */
/*   Updated: 2025/02/05 11:33:05 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** Checks if a given character 'c' exists in the string 'char_ok'.
** Returns 1 if found (i.e., valid), otherwise 0.
*/
int	is_allowed_char(char c, char *char_ok)
{
	int	i;

	i = 0;
	while (char_ok[i])
	{
		if (c == char_ok[i])
			return (1);
		i++;
	}
	return (0);
}

/*
** Custom implementation of strlen.
** Returns the length of the string, stopping at '\n' or '\0'.
** Used to trim newlines from the length calculation.
*/
int	cub3d_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	return (i);
}

/*
** Resizes a given string to the specified length.
** Pads the new string with spaces if it's shorter than 'size'.
** Frees the original string and returns the newly allocated one.
*/
char	*resize_line(char *str, int size)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = malloc(sizeof(char) * size + 1);
	if (!new_str)
		return (NULL);
	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	while (i < size)
	{
		new_str[i] = ' ';
		i++;
	}
	new_str[size] = '\0';
	if (str)
		free(str);
	return (new_str);
}

/*
** Concatenates two strings into a new string, separated by a '/'.
** Ignores newline characters when calculating size.
** Frees s1 after concatenation and returns the new string.
*/
char	*strjoin_line(char *s1, char *s2)
{
	int		size;
	int		i;
	char	*tab;

	i = 0;
	size = (cub3d_strlen(s1) + cub3d_strlen(s2));
	tab = malloc(sizeof(char) * size + 2);
	if (tab == NULL)
		return (NULL);
	while (s1 && s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		tab[i] = *s2;
		i++;
		s2++;
	}
	tab[size] = '/';
	tab[size + 1] = '\0';
	if (s1)
		free(s1);
	return (tab);
}
