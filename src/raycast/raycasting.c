#include "../../cub3d.h"

/*
** Calculates delta distances for raycasting.
** Delta distance is the distance the ray has to travel to go from one x or y-side to the next.
** Avoids division by zero by using INT_MAX for zero direction values.
*/
void	calculate_delta(t_map *map)
{
	if (map->ray_dir_x == 0)
		map->delta_dist_x = INT_MAX;
	else
		map->delta_dist_x = fabs(1 / map->ray_dir_x);
	if (map->ray_dir_y == 0)
		map->delta_dist_y = INT_MAX;
	else
		map->delta_dist_y = fabs(1 / map->ray_dir_y);
}

/*
** Determines step direction and initial side distances based on ray direction.
** This is used to prepare for DDA (Digital Differential Analysis) step-by-step checking.
*/
void	calculate_ray_step(t_map *map)
{
	if (map->ray_dir_x < 0)
	{
		map->step_x = -1;
		map->side_dist_x = (map->pos_x - map->map_x) * map->delta_dist_x;
	}
	else
	{
		map->step_x = 1;
		map->side_dist_x = (map->map_x + 1.0 - map->pos_x) * map->delta_dist_x;
	}
	if (map->ray_dir_y < 0)
	{
		map->step_y = -1;
		map->side_dist_y = (map->pos_y - map->map_y) * map->delta_dist_y;
	}
	else
	{
		map->step_y = 1;
		map->side_dist_y = (map->map_y + 1.0 - map->pos_y) * map->delta_dist_y;
	}
}

/*
** Performs the Digital Differential Analysis (DDA) to detect wall collisions.
** Continues stepping through the map grid until a wall cell ('1') is hit.
*/
void	run_dda(t_map *map)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (map->side_dist_x < map->side_dist_y)
		{
			map->side_dist_x += map->delta_dist_x;
			map->map_x += map->step_x;
			map->wall_side = 0;
		}
		else
		{
			map->side_dist_y += map->delta_dist_y;
			map->map_y += map->step_y;
			map->wall_side = 1;
		}
		if (map->map_tab[map->map_y][map->map_x] == '1')
			hit = 1;
	}
}

/*
** Initializes ray direction and camera position for a specific screen column.
*/
void	init_raycast(t_map *map, int x)
{
	map->map_x = map->pos_x;
	map->map_y = map->pos_y;
	map->cam_x = 2 * x / (double)map->display_width - 1;
	map->ray_dir_x = map->dir_x + map->plane_x * map->cam_x;
	map->ray_dir_y = map->dir_y + map->plane_y * map->cam_x;
}

/*
** Executes the full raycasting loop for each vertical screen column.
** Calculates ray, steps through map with DDA, and draws textured column.
*/
void	execute_raycasting(t_map *map)
{
	int	x;

	x = 0;
	while (x < map->display_width)
	{
		init_raycast(map, x);
		calculate_delta(map);
		calculate_ray_step(map);
		run_dda(map);
		if (map->wall_side == 0)
			map->perpwalldist = map->side_dist_x - map->delta_dist_x;
		else
			map->perpwalldist = map->side_dist_y - map->delta_dist_y;
		draw_column_texture(map, x);
		x++;
	}
}
