/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:23:26 by mtocu             #+#    #+#             */
/*   Updated: 2025/02/05 13:25:47 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define RST "\033[0m"    /* Reset to default color */
# define BOLD "\033[1m"   /* Bold */
# define U "\033[4m"      /* Underline */
# define RED "\033[1;31m" /* Red */
# define G "\033[1;32m"   /* Green */
# define Y "\033[1;33m"   /* Yellow */
# define B "\033[1;34m"   /* Blue */
# define M "\033[1;35m"   /* Magenta */
# define C "\033[1;36m"   /* Cyan */
# define W "\033[1;37m"   /* White */
# define PINK "\033[1;95m"        /* Pink (Bright Magenta) */
# define SALMON      "\033[38;5;210m" 
# define LIGHT_CORAL "\033[1;31m" /* Light Coral */

typedef struct s_map
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;

	int		floor[3];
	int		ceiling[3];

	char	*floor_str;
	char	*ceiling_str;

	char	**map;
	char	**temp_map;
	int		nr_rows_map;
	bool	error;

	int		poz_x;
	int		poz_y;
	int		nr_cardinals;

	void	*mlx;
	void	*win;
	
}			t_map;


// Parsing 

int		validate_args(int argc, char **argv);
void	init_textures_variables(t_map *file);
void	read_line(char *line, t_map *file);

//void pick_color(char *line, char* trimmed_lines, t_map *file);
void	pick_color(char *line, t_map *file);
int		valid_colours(char *line, t_map *file);
void	check_texture_paths(t_map *file,  char *path);



//           MAP
void	create_map(char *line, t_map *file);
int		valid_elements(char *line);
void	print_map(t_map *file);
void	check_map(t_map *file);
int		check_cardinal(char c);
void	check_cardinal_points(t_map *file, int len_line, int i);
int		check_spaces(t_map *file, int len_line, int i, int j);
void	check_left_wall(t_map *file, char *row, int len_line);
void	check_right_wall(t_map *file, char *row, int len_line, int i);
void	check_north_wall(t_map *file, int len_line);
void	check_south_wall(t_map *file, int len_line);
void	remove_spaces_map(char *row);

//			FREE
void	free_variables(t_map *file);
void	free_matrix(t_map *file);
void	free_temp_matrix(t_map *file);
void	ft_clean(t_map *file, char *str);

//			EXEC
void	execution(t_map *file);

#endif