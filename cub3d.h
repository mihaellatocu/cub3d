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

/* ============================ */
/*        LIBRARIES            */
/* ============================ */

# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include "lib/libft.h"
# include "get_next_line.h"
# include "config.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <stddef.h>
# include <math.h>
# include <limits.h>

/* ============================ */
/*         COLOURS             */
/* ============================ */

# define RST "\033[0m"
# define BOLD "\033[1m"
# define U "\033[4m"
# define RED "\033[1;31m"
# define G "\033[1;32m"
# define Y "\033[1;33m"
# define B "\033[1;34m"
# define M "\033[1;35m"
# define C "\033[1;36m"
# define W "\033[1;37m"
# define PINK "\033[1;95m"
# define SALMON "\033[38;5;210m"
# define LIGHT_CORAL "\033[1;31m"

/* ============================ */
/*        KEY CODES            */
/* ============================ */

# define KEY_ESCAPE		65307
# define KEY_SPACE		32
# define KEY_FORWARD	119
# define KEY_LEFTWARD	97
# define KEY_BACKWARD	115
# define KEY_RIGHTWARD	100
# define ARROW_UP		65362
# define ARROW_DOWN	65364
# define ARROW_LEFT	65361
# define ARROW_RIGHT	65363

/* ============================ */
/*         ENUMS               */
/* ============================ */

enum e_dir
{
	DIR_NORTH = 0,
	DIR_SOUTH = 1,
	DIR_EAST = 2,
	DIR_WEST = 3
};

/* ============================ */
/*        ENTRY POINT          */
/* ============================ */

void	init_map_data(t_map *map);
int		validate_args(int argc, char **argv);

/* ============================ */
/*           MEMORY            */
/* ============================ */

void	destroy_images(t_map *map);
void	free_texture_data(t_map *map);
void	free_string_array(char **array);
int		exit_game(t_map *map);

/* ============================ */
/*           PARSING           */
/* ============================ */

void	handle_parse_error(t_map *map, char *message);
void	read_map_lines(int fd, t_map *map);
int		parse_map(t_map *map, int fd);
int		is_allowed_char(char c, char *allowed);
int		custom_strlen(char *str);
char	*resize_line(char *str, int size);
char	*join_lines(char *s1, char *s2);
int		check_vertical_column(char **column, int y, int x, int height);
int		validate_vertical(t_map *map, int y, int x);
int		check_horizontal_line(t_map *map, char *line, int x);
int		validate_horizontal(t_map *map, int y, int x);
int		validate_map_walls(t_map *map);
int		validate_map_structure(t_map *map);
void	set_player_position(t_map *map, char direction, int i, int j);
void	set_map_dimensions(t_map *map, char **array, int i, int j);
int		analyse_map_line(t_map *map, char *line);
void	assign_texture_path(t_map *map, char **path, char **split_line);
int		parse_rgb_line(char *line);
int		parse_rgb_values(int *rgb, char *line);
void	parse_rgb_map(t_map *map, int *rgb, char **split_line);

/* ============================ */
/*        INITIALISATION       */
/* ============================ */

void	handle_game_error(t_map *map, char *message);
void	init_game_stats(t_map *map);
void	init_textures(t_map *map);
int		start_game(t_map *map);

/* ============================ */
/*       INPUT HANDLING        */
/* ============================ */

int		handle_key_input(int keycode, t_map *map);
int		handle_mouse_movement(int x, int y, t_map *map);
int		handle_mouse_click(int keycode, int x, int y, t_map *map);

/* ============================ */
/*   MOVEMENT & ROTATION       */
/* ============================ */

void	move_player(t_map *map, double next_x, double next_y, char sign);
void	rotate_player(t_map *map, double rotation_speed);
void	rotate_horizontally(t_map *map, double rotation_speed);

/* ============================ */
/*          RAYCASTING         */
/* ============================ */

void	calculate_delta(t_map *map);
void	calculate_ray_step(t_map *map);
void	run_dda(t_map *map);
void	init_raycast(t_map *map, int x);
void	execute_raycasting(t_map *map);
int		get_pixel_color(t_map *map, int x, int y, int texture_index);
void	place_pixel(t_map *map, int x, int y, int color);
void	draw_column_texture(t_map *map, int x);
void	define_texture_coords(t_map *map, int start, int line_height);
int		render_frame(t_map *map);
int		compose_color(int t, int r, int g, int b);
void	render_background(t_map *map);

/* ============================ */
/*            MINIMAP          */
/* ============================ */

void	draw_minimap(t_map *map);
void	update_minimap(t_map *map, int old_x, int old_y);
void	minimap_place_pixel(t_map *map, int x, int y, int color);
void	draw_minimap_tile(t_map *map, int x, int y, int color);

#endif