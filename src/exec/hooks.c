/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:00:00 by mtocu             #+#    #+#             */
/*   Updated: 2025/03/27 16:00:00 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/**
 * Handles key press events for player movement and rotation.
 * 
 * @param keycode Key pressed.
 * @param map Pointer to the map structure.
 * @return Always returns 0.
 */
int	handle_key_input(int keycode, t_map *map)
{
	if (keycode == KEY_ESCAPE)
		exit_game(map);
	else if (keycode == KEY_FORWARD)
		move_player(map, map->dir_x * map->speed, map->dir_y * map->speed, '+');
	else if (keycode == KEY_BACKWARD)
		move_player(map, map->dir_x * map->speed, map->dir_y * map->speed, '-');
	else if (keycode == KEY_LEFTWARD)
		move_player(map, map->plane_x * map->speed, map->plane_y * map->speed, '-');
	else if (keycode == KEY_RIGHTWARD)
		move_player(map, map->plane_x * map->speed, map->plane_y * map->speed, '+');
	else if ((keycode == ARROW_LEFT && (map->p_dir == 'N' || map->p_dir == 'S'))
		|| (keycode == ARROW_RIGHT && (map->p_dir == 'E' || map->p_dir == 'W')))
		rotate_player(map, -map->rot_speed);
	else if ((keycode == ARROW_LEFT && (map->p_dir == 'E' || map->p_dir == 'W'))
		|| (keycode == ARROW_RIGHT && (map->p_dir == 'N' || map->p_dir == 'S')))
		rotate_player(map, map->rot_speed);
	return (0);
}

/**
 * Handles mouse movement for rotating the player view.
 * 
 * @param x Mouse x-coordinate.
 * @param y Mouse y-coordinate (unused).
 * @param map Pointer to the map structure.
 * @return Always returns 0.
 */
int	handle_mouse_movement(int x, int y, t_map *map)
{
	(void)y;
	if (map->p_dir == 'N' || map->p_dir == 'S')
	{
		if (x > (int)(map->display_width / 1.2))
			rotate_player(map, map->rot_speed / 3);
		else if (x < map->display_width / 6)
			rotate_player(map, -map->rot_speed / 3);
	}
	else
	{
		if (x > (int)(map->display_width / 1.2))
			rotate_player(map, -map->rot_speed / 3);
		else if (x < map->display_width / 6)
			rotate_player(map, map->rot_speed / 3);
	}
	return (0);
}
