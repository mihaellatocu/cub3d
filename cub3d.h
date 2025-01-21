#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include "lib/libft.h"
# include "get_next_line.h"
# include <X11/keysym.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h> // pt printf()
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h> // pt open()

typedef struct s_map
{
	char*	north; // save path next to NO
	char* 	south;
	char* 	west;
	char*	east;

	int		f_red; // Floor Red
	int 	f_green;
	int 	f_blue;
	int		c_red; // Ceiling red
	int 	c_green;
	int 	c_blue;

	char**	map;
} 			t_map;


// Parsing 

void	validate_args(int argc, char **argv);
void	init_textures_variables(t_map *file);
void	read_line(char* line, t_map *file); // reading each line of the file and save the 


void free_variables(t_map *file);

#endif