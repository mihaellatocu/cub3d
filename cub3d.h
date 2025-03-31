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

# include <mlx.h>
# include "lib/libft.h"
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
# define PINK "\033[1;95m"
# define SALMON "\033[38;5;210m"
# define LIGHT_CORAL "\033[1;31m"

/* ============================ */
/*        KEY CODES            */
/* ============================ */

# define KEY_ESC		65307
# define KEY_W			119
# define KEY_A			97
# define KEY_S			115
# define KEY_D			100
# define SPACE			32

# define KEY_UP			65362
# define KEY_DOWN		65364
# define KEY_L			65361
# define KEY_R			65363

/* ============================ */
/*          ENUMS              */
/* ============================ */

enum	e_direction
{
	DIR_NORTH = 0,
	DIR_SOUTH = 1,
	DIR_EAST = 2,
	DIR_WEST = 3
};

/* =============================================================================
**                          INITIALISATION / ENTRY
** =============================================================================
** Functions for setting up the map and validating input arguments.
*/

void	init_map_data(t_map *map);
int		validate_args(char *argv);

/* =============================================================================
**                             MEMORY MANAGEMENT
** =============================================================================
** Functions for safely freeing or destroying dynamically allocated memory.
*/

void	destroy_img(t_map *map);
void	free_texture_data(t_map *map);
void	free_str_array(char **str);
int		exit_game(t_map *map);

/* =============================================================================
**                             MAP PARSING
** =============================================================================
** Functions related to reading, validating, and parsing the .cub configuration.
*/

void	parse_err(t_map *map, char *message);
void	read_map_lines(int fd, t_map *map);
int		parse_map(t_map *map, int fd);

/* =============================================================================
**                             STRING UTILITIES
** =============================================================================
** Custom string utilities to support parsing and validation.
*/

int		is_allowed_char(char c, char *char_ok);
int		cub3d_strlen(char *str);
char	*resize_line(char *str, int size);
char	*strjoin_line(char *s1, char *s2);

/* =============================================================================
**                             MAP STRUCTURE CHECKING
** =============================================================================
** Functions that check if the map is surrounded by valid wall boundaries.
*/

int		check_vertical_column(char **column, int y, int x, int height);
int		validate_vertical(t_map *map, int y, int x);
int		check_horizontal_line(t_map *map, char *line, int x);
int		validate_horizontal(t_map *map, int y, int x);
int		validate_map_walls(t_map *map);

/* =============================================================================
**                             MAP SETUP HELPERS
** =============================================================================
** Functions for assigning player spawn and calculating map dimensions.
*/

void	set_player_position(t_map *map, char direction, int i, int j);
void	set_map_dimensions(t_map *map, char **array, int i, int j);
int		analyze_map_line(t_map *map, char *line);

/* =============================================================================
**                             TEXTURE / RGB PARSING
** =============================================================================
** Parses texture paths and RGB colour values from the config file.
*/

void	assign_texture_path(t_map *map, char **path, char **split_line);
int		parse_rgb(char *line);
int		parse_rgb_value(int *rgb, char *line);
void	parse_rgb_map(t_map *map, int *rgb, char **split_line);

/* =============================================================================
**                             INPUT EVENTS
** =============================================================================
** Key and mouse event handlers used by the game loop.
*/

int		handle_key_input(int keycode, t_map *map);
int		mouse_movement(int x, int y, t_map *map);

/* =============================================================================
**                             GAME INIT / START
** =============================================================================
** Main game start and error-handling routines.
*/

void	handle_game_err(t_map *map, char *message);
void	check_game_init(t_map *map);
void	init_textures(t_map *map);
int		start_game(t_map *map);

/* =============================================================================
**                             PLAYER MOVEMENT
** =============================================================================
** Controls player position updates and rotation logic.
*/

void	move_player(t_map *map, double next_x, double next_y, char sign);
void	rotate_player(t_map *map, double rot_spd);

/* =============================================================================
**                             RAYCASTING
** =============================================================================
** Core raycasting loop and helpers for wall detection and rendering.
*/

void	calc_delta(t_map *map);
void	calc_ray_step(t_map *map);
void	run_dda(t_map *map);
void	init_raycast(t_map *map, int x);
void	exec_raycasting(t_map *map);

/* =============================================================================
**                             RENDERING
** =============================================================================
** Pixel manipulation and rendering logic for frame output.
*/

int		get_pixel_color(t_map *map, int x, int y, int i);
void	place_pixel(t_map *map, int x, int y, int color);
void	draw_col_texture(t_map *map, int x);
void	define_texture_coords(t_map *map, int start, int line_height);
int		render_frame(t_map *map);
int		compose_color(int t, int r, int g, int b);
void	render_background(t_map *map);

/* =============================================================================
**                             MINIMAP
** =============================================================================
** Drawing and updating the player's minimap view.
*/

void	draw_minimap(t_map *map);
void	update_minimap(t_map *map, int old_x, int old_y);
void	minimap_place_pixel(t_map *map, int x, int y, int color);
void	draw_minimap_tile(t_map *map, int x, int y, int color);

#endif