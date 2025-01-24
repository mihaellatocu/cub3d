#include "../cub3d.h"

void	free_matrix(t_map *file)
{
	int k = 0;
	while(k < file->nr_rows_map && file->map[k])
	{
		free(file->map[k]);
		k++;
	}
	free(file->map);
}

void	free_temp_matrix(t_map *file)
{
	int k = 0;
	while(k < file->nr_rows_map && file->temp_map[k])
	{
		free(file->temp_map[k]);
		k++;
	}
	free(file->temp_map);
}

void	create_map(char* line, t_map *file)
{
	int i;

	i = -1;
	file->temp_map = malloc(sizeof(char*) * (file->nr_rows_map + 2)); // 1 pt linia noua si 1 pt NULL
	if (!file->temp_map)
	{
		printf("Error: Memory allocation failed for the temp map.\n");
		exit(1);
	}
	while(++i < file->nr_rows_map)// && file->map[i]) //copy existent lines in matrix
		file->temp_map[i] = ft_strdup(file->map[i]);
	file->temp_map[i] = ft_strdup(line); //copy last line
	file->temp_map[i + 1] = NULL;//terminator for matrix
	free_matrix(file); //destroy temp mat and copy all matrix from map and then destroy all map
	file->nr_rows_map++;
	file->map = malloc(sizeof(char*) * (file->nr_rows_map + 1));
	if (!file->map)
	{
		printf("Error: Memory allocation failed for the map.\n");
		exit(1);
	}
	i = 0;
	while(file->temp_map[i]) //copy existent lines in matrix
	{
		file->map[i] = ft_strdup(file->temp_map[i]);
		i++;
	}
	free_temp_matrix(file);
}

void	print_map(t_map *file)
{
	int i;
	int j = 0;
	for (i = 0; i < file->nr_rows_map; i++)
	{
		printf("my map is:  ");
		for (j = 0; j < ft_strlen(file->map[i]); j++)
		{
			printf("%c ", file->map[i][j]);
		}
		printf("\n");
	}

}

int	valid_elements(char* line)
{
	int i;

	i = 0;
	while(line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != 'S' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

