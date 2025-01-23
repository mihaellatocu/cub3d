/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtocu <mtocu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:04:46 by mtocu             #+#    #+#             */
/*   Updated: 2025/01/21 15:53:33 by mtocu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
/*
-check extension file DONE
TODO
-check path for file -no
- check path for geographic textures
- check if the RGB are only between 0-255 and not negatives and nothing else apart numbers like letters
- need to exit on errors
- save map
-check walls

*/

void init_textures_variables(t_map *file)
{
	file->c_blue = 0;
	file->c_green = 0;
	file->c_blue = 0;
	file->f_blue = 0;
	file->f_green = 0;
	file->f_red = 0;
	file->north = NULL;
	file->south = NULL;
	file->west = NULL;
	file->east = NULL;
	file->error = false;
	
}

void validate_args(int argc, char **argv)
{
	int	len;
	int fd;
	
	if (argc < 2)
	{
		printf("The Map was not provided.\n");
		exit(1);
	}
	else if (argc != 2)
	{
		printf("Multiple arguments provided.\n");
		exit(1);
	}
	fd = open(argv[1], O_RDONLY); // which one should be first?
	if (fd == -1)
	{
		printf("File does not exist or cannot be accessed.\n");
		exit(1);
	}
	close(fd);
	len = ft_strlen(argv[1]);
	if (!ft_strnstr(argv[1] + len - 4, ".cub", len))	
	{
		printf("The map should be in '.cub' format\n"); // or this one?
		exit(EXIT_FAILURE);
	}
	
}



void read_line(char* line, t_map *file)
{
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		file->north = ft_strtrim(line + 2, " ");  
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		file->south = ft_strtrim(line + 2, " ");  
	}
	else if (ft_strncmp(line, "WE", 2) == 0)
	{
		file->west = ft_strtrim(line + 2, " ");  
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		file->east = ft_strtrim(line + 2, " ");  
	}
	else if ((ft_strncmp(line, "F", 1) == 0) || (ft_strncmp(line, "C", 1) == 0))
	{
		if (valid_colours(line, file) == 1)
			pick_color(line, file);
	}
	if (file->error == true)
		ft_clean(line, file);

	
}


void	read_file(char *argv, t_map *file)
{
	int fd;
	char *line;
	
	fd = open(argv, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s\n", line);
		read_line(line, file); //save path to textures and colours for floor and ceiling
								//check if the paths to textures are valid

	
		free(line);
		if (!file->error)
			line = get_next_line(fd);
	}
	close(fd);
}


int	main(int argc, char *argv[])
{
	t_map	file;
	
	validate_args(argc, argv);
	init_textures_variables(&file);
	read_file(argv[1], &file);

	free_variables(&file);
	printf("**********end of main function\n");
	return (0);
}