#include "../cub3d.h"

void	check_texture_paths(t_map *file, char* paths)
{
	int	fd;
	int bytes;
	char buffer[4];
	
	
	fd = open(paths, O_RDONLY);
	if (fd == -1)
	{
		//printf("Error:\nThe file cannot be open.\n");
		ft_clean(file, "Error:\nThe file cannot be open.\n");
	}
	bytes = read(fd, buffer, sizeof(buffer));
	close(fd);
	if (bytes == -1)
	{
		//printf("Error:\nThe file cannot be read.\n");
		ft_clean(file, "Error:\nThe file cannot be read.\n");
	}
}
