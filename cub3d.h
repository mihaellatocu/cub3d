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

#define RST "\033[0m"    /* Reset to default color */
#define BOLD "\033[1m"   /* Bold */
#define U "\033[4m"      /* Underline */
#define RED "\033[1;31m" /* Red */
#define G "\033[1;32m"   /* Green */
#define Y "\033[1;33m"   /* Yellow */
#define B "\033[1;34m"   /* Blue */
#define M "\033[1;35m"   /* Magenta */
#define C "\033[1;36m"   /* Cyan */
#define W "\033[1;37m"   /* White */

#define PINK "\033[1;95m"        /* Pink (Bright Magenta) */
#define SALMON      "\033[38;5;210m" 
#define LIGHT_CORAL "\033[1;31m" /* Light Coral */

typedef struct s_map
{
	char*	north; // save path next to NO
	char* 	south;
	char* 	west;
	char*	east;

	int		floor[3];
	int		f_red; // Floor Red
	int 	f_green;
	int 	f_blue;
	int		c_red; // Ceiling red
	int 	c_green;
	int 	c_blue;

	char**	map;
	bool 	error;
} 			t_map;


// Parsing 

void	validate_args(int argc, char **argv);
void	init_textures_variables(t_map *file);
void	read_line(char* line, t_map *file); // reading each line of the file and save the 

//void pick_color(char *line, char* trimmed_lines, t_map *file);
void pick_color(char *line, t_map *file);
int valid_colours(char *line, t_map *file);
void ft_clean(char *line, t_map *file);


void free_variables(t_map *file);

#endif