/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:29:45 by mtocu             #+#    #+#             */
/*   Updated: 2025/02/05 11:33:08 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	free_variables(t_map *file)
{
	free(file->north);
	free(file->south);
	free(file->west);
	free(file->east);
	free(file->ceiling_str);
	free(file->floor_str);
	free_matrix(file);
}
