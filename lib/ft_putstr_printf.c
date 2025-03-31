#include "ft_printf.h"

int	ft_putstr_printf(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
	{
		ft_putstr_printf("(null)", 1);
		return (6);
	}
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	return (i);
}
