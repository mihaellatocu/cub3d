#include "../cub3d.h"

void free_variables(t_map *file)
{
	printf(" file north %s\n", file->north);
	free(file->north);
	printf(" file south %s\n", file->south);
	free(file->south);
	printf(" file west %s\n", file->west);
	free(file->west);
	printf(" file east %s\n", file->east);
	free(file->east);
	

}