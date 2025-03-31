/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:00:27 by mtocu             #+#    #+#             */
/*   Updated: 2024/03/21 19:17:23 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (*s2 == '\0')
		return ((char *)s1);
	while (s1[i] && i < n)
	{
		if (s1[i] == *s2)
		{
			if (ft_strncmp(s1 + i, s2, ft_strlen(s2)) == 0
				&& ft_strlen(s2) + i <= n)
				return ((char *)s1 + i);
		}
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char *s1 = "aaabcabcad";
	char *s2 = "c";
	//char *ptr;
	//ptr = ft_strnstr(s1, s2, 3);
	//printf("%d\n", strnstr(s1, s2, 10));
	printf("%s\n", ft_strnstr(s1, s2, 10));
	//char	*str;
//	ABCDg
//	ABCDE
}*/
