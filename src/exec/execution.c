/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:41:09 by mtocu             #+#    #+#             */
/*   Updated: 2025/02/05 13:41:52 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	close_window(t_map *file)
{
	mlx_destroy_window(file->mlx, file->win);
	mlx_destroy_display(file->mlx);
	free(file->mlx);
	free_variables(file);
	exit (1);
}

int	deal_key(int key, t_map *file)
{
	if (key == XK_Escape)
		close_window(file);
	return (0);
}

void	execution(t_map *file)
{
	file->mlx = mlx_init();
	if (file->mlx == NULL)
		return ;
	file->win = mlx_new_window(file->mlx, 800, 600, "Cub3d");
	if (file->win == NULL)
		return (free(file->mlx));
	mlx_hook(file->win, 17, 1L << 0, close_window, file);
	mlx_key_hook(file->win, deal_key, file);
	mlx_loop(file->mlx);
}
