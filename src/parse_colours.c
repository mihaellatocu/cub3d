#include "../cub3d.h"

void	check_value(int value, char first_letter, int k, t_map *file)
{
	if (k >= 3 || value < 0 || value > 255)
	{
		printf("Eroare la nr de culori sau marimea lor\n");
		file->error = true;
	}	
	else if (value >= 0 && value <= 255)
	{
		if (first_letter == 'F')
			file->floor[k] = value;
		else if (first_letter == 'C')
			file->ceiling[k] = value;
	}
	// printf(" F red green blue %d %d %d\n", file->floor[0], file->floor[1], file->floor[2]);
	// printf(" C red green blue %d %d %d\n", file->ceiling[0], file->ceiling[1], file->ceiling[2]);
}

void pick_color(char *line, t_map *file)
{
	int i;
	char temp_nr[4];
	int j;
	int k; // nr of colours
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
	if (k != 3)
		ft_clean(file, "Error:\nColur missconfiguration.\n");
}

int valid_colours(char *line, t_map *file)
{
	int i;

	i = 1;
	if (line == NULL)
		return(0); 
	//printf("valid_colours function\n");
	while(line[i])
	{
		if ((line[i] != ' ' && line[i] != ',' && line[i] <'0') || (line[i] > '9'))
			ft_clean(file,"Error:\nThe coulour configuration is incorrect.\n");	
		i++;
	}
	return (1);
}

void ft_clean(t_map *file, char* str)
{
	// if (file->error == true)
	// {
		free_variables(file);
		// if()
		// 	free(line);
		printf("ft_clean called %s\n" , str);
		
	//}
	exit(1);
}


