/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:58:05 by mtocu             #+#    #+#             */
/*   Updated: 2025/02/04 14:11:46 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_texture_paths(t_map *file, char *paths)
{
	int		fd;
	int		bytes;
	char	buffer[4];

	fd = open(paths, O_RDONLY);
	if (fd == -1)
		ft_clean(file, "Error:\nThe texture file cannot be open.");
	bytes = read(fd, buffer, sizeof(buffer));
	close(fd);
	if (bytes == -1)
		ft_clean(file, "Error:\nThe texture file cannot be read.");
}
