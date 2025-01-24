#include "../cub3d.h"

int		check_map(t_map *file)
{
	int i;
	int j;
	int len_line;

	i = 0;
	j = 0;
	while (i < file->nr_rows_map ) //file->map[i][j])
	{
		len_line = ft_strlen(file->map[i]);
		printf("len line: %d\n", len_line);
		if (len_line == 0)
		{
			printf("The map is invalid.\n");
			file->error = true;
		}
		//printf("len line: %d\n", len_line);
		j = 0;
		while(j < len_line)
		{
			if (len_line == 0)
			{
				printf("len line: %d\n", len_line);
					//file->error = true;
			}
			j++;
		}
		i++;
	}
	return 0;
}