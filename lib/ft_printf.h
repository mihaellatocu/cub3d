#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# if defined (APPLE)
#  define PTR_NULL "0x0"
# elif linux
#  define PTR_NULL "(nil)"
# endif

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

int	ft_format(const char *format, va_list args);
int	ft_printf(const char *format, ...);
int	ft_putchar_printf(char c, int fd);
int	ft_putnbr_printf(int n, int fd);
int	ft_putstr_printf(char *s, int fd);

#endif
