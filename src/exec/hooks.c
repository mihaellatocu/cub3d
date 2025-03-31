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

/*
** Handles keyboard input for player movement and rotation.
** - KEY_W / KEY_S: move forward/backward in the direction the player is facing.
** - KEY_A / KEY_D: strafe left/right based on camera plane (perpendicular to direction).
** - KEY_L / KEY_R: rotate the player left/right, with direction depending on initial orientation.
** - KEY_ESC: cleanly exits the game.
*/
int	handle_key_input(int keycode, t_map *map)
{
	if (keycode == KEY_ESC)
		exit_game(map);
	else if (keycode == KEY_W)
		move_player(map, map->dir_x * map->speed, map->dir_y * map->speed, '+');
	else if (keycode == KEY_S)
		move_player(map, map->dir_x * map->speed, map->dir_y * map->speed, '-');
	else if (keycode == KEY_A)
		move_player(map, map->plane_x * map->speed, map->plane_y * map->speed, '-');
	else if (keycode == KEY_D)
		move_player(map, map->plane_x * map->speed, map->plane_y * map->speed, '+');
	else if ((keycode == KEY_L && (map->p_dir == 'N' || map->p_dir == 'S'))
		|| (keycode == KEY_R && (map->p_dir == 'E' || map->p_dir == 'W')))
		rotate_player(map, -map->rot_speed);
	else if ((keycode == KEY_L && (map->p_dir == 'E' || map->p_dir == 'W'))
		|| (keycode == KEY_R && (map->p_dir == 'N' || map->p_dir == 'S')))
		rotate_player(map, map->rot_speed);
	return (0);
}

/*
** Handles player rotation based on horizontal mouse position.
** - If mouse is near right edge of screen: rotate right.
** - If mouse is near left edge of screen: rotate left.
** - Direction depends on player's orientation (N/S vs. E/W).
** - Y is unused, as only horizontal movement affects rotation.
*/
int	mouse_movement(int x, int y, t_map *map)
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
