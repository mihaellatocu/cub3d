/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:45:00 by mtocu             #+#    #+#             */
/*   Updated: 2025/03/27 17:00:00 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/**
 * Moves the player based on direction vector and collision detection.
 * The `sign` parameter decides whether the movement is forward ('+')
 * or backward ('-'). If the move is valid (not into a wall), updates
 * the position and minimap accordingly.
 */
void	move_player(t_map *map, double next_x, double next_y, char sign)
{
	int	old_x;
	int	old_y;

	old_x = (int)map->pos_x;
	old_y = (int)map->pos_y;
	if (sign == '+')
	{
		if (map->map_tab[(int)map->pos_y][(int)(map->pos_x + next_x)] != '1')
			map->pos_x += next_x;
		if (map->map_tab[(int)(map->pos_y + next_y)][(int)map->pos_x] != '1')
			map->pos_y += next_y;
	}
	else if (sign == '-')
	{
		if (map->map_tab[(int)map->pos_y][(int)(map->pos_x - next_x)] != '1')
			map->pos_x -= next_x;
		if (map->map_tab[(int)(map->pos_y - next_y)][(int)map->pos_x] != '1')
			map->pos_y -= next_y;
	}
	if (old_x != map->map_x || old_y != map->map_y)
		update_minimap(map, old_x, old_y);
}

/**
 * Rotates the player's direction and camera plane by the given speed.
 * Uses basic 2D rotation matrix to rotate both the direction vector
 * and the camera plane.
 */
void	rotate_player(t_map *map, double rotation_speed)
{
	double	tmp_dir_x;
	double	tmp_plane_x;

	tmp_dir_x = map->dir_x;
	tmp_plane_x = map->plane_x;
	map->dir_x = map->dir_x * cos(rotation_speed) - map->dir_y * sin(rotation_speed);
	map->dir_y = tmp_dir_x * sin(rotation_speed) + map->dir_y * cos(rotation_speed);
	map->plane_x = map->plane_x * cos(rotation_speed) - map->plane_y * sin(rotation_speed);
	map->plane_y = tmp_plane_x * sin(rotation_speed) + map->plane_y * cos(rotation_speed);
}
