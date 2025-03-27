#ifndef CONFIG_H
# define CONFIG_H

/*
** Structure for handling texture information including image pointer,
** pixel data, size, and format properties.
*/
typedef struct s_texture
{
	void	*image;
	char	*path;
	char	*pixels;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
	int		width;
	int		height;
}	t_texture;

/*
** Structure for holding the main game map and rendering state.
*/
typedef struct s_map
{
	/* MLX & image rendering */
	void		*mlx;
	void		*mlx_win;
	t_texture	img[5];
	t_texture	minimap;

	/* Display */
	int		display_width;
	int		display_height;

	/* Map info */
	char		**map_tab;
	int		width_map;
	int		height_map;

	/* Player position & direction */
	char		p_dir;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;

	/* Floor and ceiling colours */
	int		rgb_floor[3];
	int		rgb_sky[3];

	/* Map parsing helpers */
	char		*line;
	char		*map_line;

	/* Wall intersection */
	double		wall_x;
	int		tex_x;
	int		tex_y;
	double		step;
	double		tex_pos;

	/* Raycasting calculations */
	double		ray_dir_x;
	double		ray_dir_y;
	double		cam_x;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perpwalldist;

	/* DDA */
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;

	/* Wall info */
	int		wall_side;
	int		wall_dist;

	/* Drawing info */
	int		size_line;
	int		start_line;
	int		end_line;
	int		start;
	int		end;

	/* Movement */
	double		speed;
	double		rot_speed;

}	t_map;

#endif