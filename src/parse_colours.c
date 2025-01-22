#include "../cub3d.h"

void	check_value(int value, char first_letter, int k, t_map *file)
{
	if (value < 0 || value > 255 || k >= 3)
	{
		printf("%s", "Error the value for the colours is not in range or there are too many colours");
		///return 1;
	}
	if (first_letter == 'F')
	{
		if (k == 0)
			file->f_red = value;
		else if (k == 1)
			file->f_green = value;
		else if (k == 2)
			file->f_blue = value;
	}
	else if (first_letter == 'C')
	{
		if (k == 0)
			file->c_red = value;
		else if (k == 1)
			file->c_green = value;
		else if (k == 2)
			file->c_blue = value;
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
		check_value(value, line[0], k, file); // should I stop here if a value is incorrect?
		k++;
		j = 0;
		if (line[i] != ' ' && line[i] != ',' && line[i] <'0' && line[i] > '9')
			printf("The RGB values are incorrect!\n"); // this line will never get into
	}
}