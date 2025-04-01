/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:39:36 by mtocu             #+#    #+#             */
/*   Updated: 2025/04/01 18:39:57 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** Calculates the distance the ray must travel to cross 
** from one x-side to the next (delta_dist_x),
** and from one y-side to the next (delta_dist_y).
** Uses `INT_MAX` to avoid division by 0 when the direction component is 0.
** This value is used in DDA to incrementally calculate the distance to walls.
*/
void	calc_delta(t_map *map)
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
** Calculates the distance the ray must travel to cross 
** from one x-side to the next (delta_dist_x),
** and from one y-side to the next (delta_dist_y).
** Uses `INT_MAX` to avoid division by 0 when the direction component is 0.
** This value is used in DDA to incrementally calculate the distance to walls.
*/
void	calc_ray_step(t_map *map)
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
** Performs the DDA (Digital Differential Analysis) algorithm.
** This algorithm steps through the map grid cell by cell,
** using the precomputed distances until a wall ('1') is hit.
** Sets `wall_side` to 0 if a vertical wall was hit, or 1 for a horizontal wall.
*/
void	run_dda(t_map *map)
{
	int	wall;

	wall = 0;
	while (wall == 0)
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
			wall = 1;
	}
}

/*
** Sets up the raycasting calculations for a single vertical screen 
slice (column x).
** Calculates camera space x-coordinate, ray direction,
** and starting grid cell (map_x, map_y) based on player position.
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
** Executes the full raycasting loop over all screen columns.
** For each column:
**  - Initializes the ray.
**  - Computes step and side distances.
**  - Runs DDA to detect walls.
**  - Calculates perpendicular wall distance to avoid fish-eye effect.
**  - Triggers drawing for the current column.
*/
void	exec_raycasting(t_map *map)
{
	int	x;

	x = 0;
	while (x < map->display_width)
	{
		init_raycast(map, x);
		calc_delta(map);
		calc_ray_step(map);
		run_dda(map);
		if (map->wall_side == 0)
			map->perpwalldist = (map->side_dist_x - map->delta_dist_x);
		else
			map->perpwalldist = (map->side_dist_y - map->delta_dist_y);
		if (map->perpwalldist < 0.1)
			map->perpwalldist = 0.1;
		draw_col_texture(map, x);
		x++;
	}
}
