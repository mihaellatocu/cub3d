/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:45:00 by mtocu             #+#    #+#             */
/*   Updated: 2025/04/01 18:26:19 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*
** Moves the player on the map in a specified direction.
** `next_x` and `next_y` define the movement vector (usually derived from 
**dir or plane).
** `sign` determines whether the movement is forward ('+') or backward ('-').
**
** - Before moving, the function checks for walls ('1') to prevent walking
** through them.
** - Updates player position only if the next tile is not a wall.
** - If the player moves to a new tile, the minimap is updated.
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

/*
** Rotates the player's direction and camera plane using standard 2D rotation.
** Rotation is done using the rotation matrix:
**   x' = x * cos(θ) - y * sin(θ)
**   y' = x * sin(θ) + y * cos(θ)
**
** - `rot_spd` defines the rotation angle (positive = right, negative = left).
** - This affects both the viewing direction and the FOV plane.
*/
void	rotate_player(t_map *map, double rot_spd)
{
	double	tmp_dir_x;
	double	tmp_plane_x;

	tmp_dir_x = map->dir_x;
	tmp_plane_x = map->plane_x;
	map->dir_x = map->dir_x * cos(rot_spd) - map->dir_y * sin(rot_spd);
	map->dir_y = tmp_dir_x * sin(rot_spd) + map->dir_y * cos(rot_spd);
	map->plane_x = map->plane_x * cos(rot_spd) - map->plane_y * sin(rot_spd);
	map->plane_y = tmp_plane_x * sin(rot_spd) + map->plane_y * cos(rot_spd);
}
