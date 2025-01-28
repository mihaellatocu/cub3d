#include "../cub3d.h"

int check_cardinal(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c== 'E')
		return (1);
	return (0);
}

void check_left_wall(t_map *file, char* row)
{
	int j;
	int len_line;//it could be passed as a variable if needed less lines

	j = 0;
	len_line = ft_strlen(row);
	while (j < len_line)
	{
		if (row[0] == '0' || check_cardinal(row[0]))
			ft_clean(file, RED "Error:\nThe left wall is not correct.\n" RST);
		else if(row[0] == ' ')
		{
			while (j < len_line)
			{
				if (row[j + 1] == ' ')
					j++;
				else if (row[j + 1] == '1')
					return ;
				else
					ft_clean(file, RED "Error:\nThe left wall is invalid.\n" RST);
			}
		}
		j++;
	}
}

void check_right_wall(t_map *file, char* row, int len_line)
{
	if (row[len_line - 1] != '1')
	{
		if(row[len_line - 1] == ' ')
		{
			while(len_line > 0)
			{
				if(row[len_line - 2] == ' ')
					len_line--;
				else if (row[len_line - 2] == '1')
					return;
				else
					ft_clean(file,RED "Error:\nThe right wall is invalid." RST);
			}
		}
		else
			ft_clean(file,RED "Error:\nThe right wall is invalid." RST);
	}
}

void	check_top_wall(t_map *file, int len_line) //to correct 1 len size wall and u shape not all 1
{
	int j;
	int i;

	j = 0;
	i = 0;
	while (j < len_line)
	{
		if (file->map[i][j] == '0' || check_cardinal(file->map[i][j]))
			ft_clean(file, RED "The top row is incorrect." RST);
		else if (file->map[i][j] == ' ')
		{ 	
			while (file->map[i + 1][j] == ' ')
				i++;
			// printf("i este       %d\n", i);
			// printf("j este       %d\n", j);
			// printf(G "[i][j]                 %c\n" RST,file->map[i+1][j]) ;
			if (file->map[i + 1][j] != '1') // here is the problem <<<<<
				ft_clean(file, "The top row is incorrect.");
			
		}
		j++;
		i = 0;
	}
}


int		check_map(t_map *file)
{
	int i;
	//int j;
	int len_line;

	i = 0;
	//j = 0;
	while (i < file->nr_rows_map ) //file->map[i][j])
	{
		len_line = ft_strlen(file->map[i]);
		printf("line is %d - and lenght line: %d\n", i, len_line);
		if (len_line == 0) // check if empty lines in map
		{
			printf("The map is invalid.\n");
			file->error = true;
			ft_clean(file, RED "Error:\nThe line is empty.\n" RST);
		}
		//printf("len line: %d\n", len_line);
		//j = 0;
		// while(j < len_line)
		// {
			check_top_wall(file, len_line); //bottom
			check_left_wall(file, file->map[i]); 
			check_right_wall(file, file->map[i], len_line);
			//check_cardinal(file);// and save positions

		// 	j++;
		// }
		i++;
	}
	return 0;
}