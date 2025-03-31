/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:25:00 by mtocu             #+#    #+#             */
/*   Updated: 2025/03/31 00:00:00 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

/* ============================ */
/*        IMAGE STRUCTURE      */
/* ============================ */

/*
	t_img:
	Holds image-related information for MiniLibX rendering.
	Includes pointer to image, address of pixel data,
	and metadata like width, height, and endian info.
*/
typedef struct s_img
{
	void	*image;		// Pointer to MLX image
	char	*path;		// Path to texture file
	char	*pixels;		// Pixel data address
	int		bits_per_pixel;			// Bits per pixel
	int		line_size;		// Line size in bytes
	int		endian;			// Endian setting
	int		width;				// Width of image
	int		height;				// Height of image
}	t_img;

/* ============================ */
/*         MAIN STRUCT         */
/* ============================ */

/*
	t_map:
	The central structure storing the game state,
	raycasting parameters, map, textures, and player movement data.
*/
typedef struct s_map
{
	/* MLX and image handling */
	void	*mlx;
	void	*mlx_win;
	t_img	img[5];			// Texture images: NO, SO, WE, EA + main
	t_img	minimap;		// Minimap image

	int		display_width;	// Window width
	int		display_height;	// Window height

	/* Map information */
	char	**map_tab;		// 2D map layout
	int		width_map;
	int		height_map;

	/* Player settings */
	char	p_dir;			// Initial direction: N/S/E/W
	double	pos_x;			// Player X position
	double	pos_y;			// Player Y position
	double	dir_x;			// Player X direction vector
	double	dir_y;			// Player Y direction vector
	double	plane_x;		// Camera X plane
	double	plane_y;		// Camera Y plane

	/* Colours */
	int		rgb_floor[3];	// RGB floor colour
	int		rgb_sky[3];		// RGB ceiling colour

	/* Map parsing helpers */
	char	*line;			// Temporary line buffer
	char	*map_line;		// Accumulated map lines

	/* Texture sampling */
	double	wall_x;			// Exact X position where wall was hit
	int		tex_x;			// X coordinate in texture
	int		tex_y;			// Y coordinate in texture
	double	step;			// Step for texture
	double	tex_pos;		// Starting texture position

	/* Raycasting values */
	double	ray_dir_x;
	double	ray_dir_y;
	double	cam_x;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perpwalldist;

	/* DDA and grid position */
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		wall_side;		// 0 for vertical, 1 for horizontal
	int		wall_dist;

	/* Drawing wall slice */
	int		size_line;
	int		start_line;
	int		end_line;
	int		start;
	int		end;

	/* Player movement speed */
	double	speed;
	double	rot_speed;
}	t_map;

#endif
