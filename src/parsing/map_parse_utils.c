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
** Checks if a given character 'c' exists within the allowed characters string.
** Returns 1 if found, 0 otherwise.
*/
int	is_allowed_char(char c, char *allowed)
{
	int	i;

	i = 0;
	while (allowed[i])
	{
		if (c == allowed[i])
			return (1);
		i++;
	}
	return (0);
}

/*
** Returns the length of a string until a newline or null terminator is found.
** Useful for handling raw map lines that may include '\n'.
*/
int	custom_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	return (i);
}

/*
** Resizes a map line to a given width.
** Truncates if too long or pads with spaces if too short.
** Always null-terminates the returned string.
*/
char	*resize_line(char *str, int size)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = malloc(sizeof(char) * (size + 1));
	if (!new_str)
		return (NULL);
	while (str && str[i] && i < size)
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

void	copy_and_append_newline(char *dest, char *s1, char *s2, size_t len1)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < len1)
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		dest[i++] = s2[j++];
	}
	dest[i++] = '\n';
	dest[i] = '\0';
}

/*
** Concatenates two strings with a newline in between.
** Allocates a new string, frees the first, and returns the result.
*/
char	*join_lines(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*joined;

	len1 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	len2 = 0;
	if (s2)
		len2 = ft_strlen(s2);
	joined = malloc(len1 + len2 + 2);
	if (!joined)
		return (NULL);
	copy_and_append_newline(joined, s1, s2, len1);
	free(s1);
	return (joined);
}
