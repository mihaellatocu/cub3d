#include "../cub3d.h"

void	check_value(int value, char first_letter, int k, t_map *file)
{
	if (k >= 3 || value < 0 || value > 255)
	{
		printf("Eroare la nr de culori sau marimea lor\n");
		printf("value %d\n", value);
		file->error = true;
	}	
	else if (value >= 0 && value <= 255)
	{
		if (first_letter == 'F')
		{
			file->floor[k] = value;
		}
		else if (first_letter == 'C')
		{
			file->floor[k] = value;
		}
	}
	
	// printf(" F red green blue %d %d %d\n", file->f_red, file->f_green, file->f_blue);
	// printf(" C red green blue %d %d %d\n", file->c_red, file->c_green, file->c_blue);
}

void pick_color(char *line, t_map *file)
{
	int i;
	char temp_nr[4];
	int j;
	int k;
	int value;

	i = 1;
	j = 0;
	k = 0;
	value = 0;
	while(line[i])
	{
		while (line[i] == ' ' || line[i] == ',')
			i++;
		while (line[i] >='0' && line[i] <= '9')
			temp_nr[j++] = line[i++];
		temp_nr[j] = '\0';
		value = ft_atoi(temp_nr);
		check_value(value, line[0], k, file);
		k++;
		j = 0;
	}
	printf("%d\n", file->error);
}

int valid_colours(char *line, t_map *file)
{
	int i;
	(void)file;

	i = 1;
	printf("valid_colours function\n");
	
	while(line[i])
	{
		if ((line[i] != ' ' && line[i] != ',' && line[i] <'0') || (line[i] > '9'))
		{
			printf("i este %d si line[i] %c The RGB values are incorrect!\n", i, line[i]);
			file->error = true;
			return 0;
		}	
		i++;
	}
	//printf("%d\n", file->error);
	return (1);
}

void ft_clean(char *line, t_map *file)
{
	if (file->error == true)
	{
		free_variables(file);
		if(line)
			free(line);
		printf("ft_clean called\n");
		exit(1);
	}
}