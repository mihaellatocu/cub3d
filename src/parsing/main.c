/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:04:46 by mtocu             #+#    #+#             */
/*   Updated: 2025/02/05 13:33:02 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"
/*
-check extension file DONE
TODO
-check path for file -no
- check path for geographic textures ??
-DONE  check if the RGB are only between 0-255 and 
not negatives and nothing else apart numbers like letters
- need to exit on errors
- save map DONE
-check walls DONE

*/

void	init_textures_variables(t_map *file)
{
	file->nr_rows_map = 0;
	file->north = NULL;
	file->south = NULL;
	file->west = NULL;
	file->east = NULL;
	file->error = false;
	file->ceiling[0] = -1;
	file->ceiling[1] = -1;
	file->ceiling[2] = -1;
	file->floor[0] = -1;
	file->floor[1] = -1;
	file->floor[2] = -1;
	file->temp_map = NULL;
	file->map = NULL;
	file->ceiling_str = NULL;
	file->floor_str = NULL;
	file->poz_x = -1;
	file->poz_y = -1;
	file->nr_cardinals = 0;
	file->mlx = NULL;
	file->win = NULL;
}

int	validate_args(int argc, char **argv)
{
	int	len;
	int	fd;

	if (argc < 2)
		return (printf(RED "Error:\nThe Map was not provided.\n" RST), 1);
	else if (argc != 2)
		return (printf(RED "Error\nMultiple arguments provided.\n" RST), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (printf(RED "Error:\nError opening the file.\n" RST), 1);
	close(fd);
	len = ft_strlen(argv[1]);
	if (!ft_strnstr(argv[1] + len - 4, ".cub", len))
		return (printf(RED "Error:\nWrong'.cub' format\n"RST), 1);
	return (0);
}

void	read_line(char *line, t_map *file)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		file->north = ft_strtrim(line + 2, " ");
	else if (ft_strncmp(line, "SO ", 3) == 0)
		file->south = ft_strtrim(line + 2, " ");
	else if (ft_strncmp(line, "WE ", 3) == 0)
		file->west = ft_strtrim(line + 2, " ");
	else if (ft_strncmp(line, "EA ", 3) == 0)
		file->east = ft_strtrim(line + 2, " ");
	else if (ft_strncmp(line, "F ", 2) == 0)
		file->floor_str = ft_strdup(line);
	else if (ft_strncmp(line, "C ", 2) == 0)
		file->ceiling_str = ft_strdup(line);
	else if ((line && line[0] == '\n') || (ft_strlen(line) == 0
			&& file->nr_rows_map == 0))
		return ;
	else if (valid_elements(line) == 1)
		create_map(line, file);
	else
		file->error = true; //unexpected value
	if (file->error == true)
	{
		free(line);
		ft_clean(file, "Error:\nUnexpected value in file.\n");
	}
}

void	check_parsing(t_map *file)
{
	check_texture_paths(file, file->north);
	check_texture_paths(file, file->south);
	check_texture_paths(file, file->east);
	check_texture_paths(file, file->west);
	if (valid_colours(file->ceiling_str, file) == 1)
		pick_color(file->ceiling_str, file);
	if (valid_colours(file->floor_str, file) == 1)
		pick_color(file->floor_str, file);
	check_map(file);
	if (file->error == true)
		ft_clean(file, "Error:\n");
}

void	read_file(char *argv, t_map *file)
{
	int		fd;
	char	*line;

	fd = open(argv, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		read_line(line, file);
		free(line);
		if (!file->error)
			line = get_next_line(fd);
	}
	close(fd);
}

// int	close_window(t_map *file)
// {
// 	mlx_destroy_window(file->mlx, file->win);
// 	mlx_destroy_display(file->mlx);

// 	free(file->mlx);
// 	free_variables(file);
// 	exit(0);
// 	// return (0);
// }

int	main(int argc, char *argv[])
{
	t_map	file;

	if (validate_args(argc, argv) == 1)
		exit(1);
	init_textures_variables(&file);
	read_file(argv[1], &file);
	check_parsing(&file);
	// file.mlx = mlx_init();
	// if(file.mlx == NULL)
	// 	return 1; // do I need to return -1?

	// file.win = mlx_new_window(file.mlx, 800, 600, "Cub3d");
	// if (file.win == NULL)
	// 	return (free(file.mlx), 1);
	// mlx_hook(file.win, 17, 1L << 0, close_window, &file);
	// mlx_loop(file.mlx);
	execution(&file);

	// print_map(&file);
	// free_variables(&file);
	printf("**********end of main function\n");
	return (0);
}
