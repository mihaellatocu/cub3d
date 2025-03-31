/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:25:44 by mtocu             #+#    #+#             */
/*   Updated: 2024/03/21 19:18:05 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		size;
	int		i;
	char	*str;

	i = 0;
	size = (ft_strlen(s1) + ft_strlen(s2));
	str = malloc(sizeof(char) * size + 1);
	str[size] = '\0';
	if (str == NULL)
		return (NULL);
	while (s1 && *s1)
	{
		str[i] = *s1;
		i++;
		s1++;
	}
	while (s2 && *s2)
	{
		str[i] = *s2;
		i++;
		s2++;
	}
	return (str);
}

/*
int	main(void)
{
	char *a = "abc";
	char *b = "";
	printf("%s\n", ft_strjoin(a, b));
}*/
