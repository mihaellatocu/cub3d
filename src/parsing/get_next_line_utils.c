/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:52:09 by mtocu             #+#    #+#             */
/*   Updated: 2025/02/05 11:33:15 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../get_next_line.h"
#include <stdint.h>

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*a;
	int				n;
	void			*ptr;

	if ((count >= SIZE_MAX || size >= SIZE_MAX) && count && size)
		return (NULL);
	ptr = (void *)malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	a = ptr;
	n = count * size;
	while (n)
	{
		*a = '\0';
		a++;
		n--;
	}
	return (ptr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	unsigned char	*new_str;
	int				j;
	int				i;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	new_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	while (s1 && i < ft_strlen(s1))
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2 && j < ft_strlen(s2))
	{
		new_str[i + j] = s2[j];
		j++;
	}
	new_str[i + j] = '\0';
	return ((char *)new_str);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}
