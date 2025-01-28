#include "../cub3d.h"

int check_cardinal(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c== 'E')
		return (1);
	return (0);
}

void	check_cardinal_points(t_map *file, int len_line, int i)
{
	int j;

	j = 0;
	while (j < len_line)
	{
		if (check_cardinal(file->map[i][j]) == 1)
		{
			file->poz_x = i;
			file->poz_y = j;
			file->nr_cardinals++;
			printf("x %d  y %d cardinals %d\n", 	file->poz_x, file->poz_y, file->nr_cardinals );
		}
		j++;
	}
}

void check_left_wall(t_map *file, char* row, int i)
{
	int j;
	int len_line;//it could be passed as a variable if needed less lines
	(void)i;
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

void	check_north_wall(t_map *file, int len_line) //to correct 1 len size wall and u shape not all 1
{
	int j; //coloana
	int i; //rand

	j = 0;
	i = 0;
	while (j < len_line)
	{
		if (file->map[i][j] == '0' || check_cardinal(file->map[i][j]))
			ft_clean(file, RED "Error:\nThe top row is incorrect." RST);
		else if (file->map[i][j] == ' ')
		{ 	
			while (file->map[i + 1][j] == ' ')
			{
				i++;
				if (j > 0 && (file->map[i - 1][j - 1] != ' ' && file->map[i][j-1] != '1'))
					ft_clean(file, RED "Error:\nThe top row is incorrect." RST);
				if (j + 1 < len_line && file->map[i - 1][j + 1] != ' ' && file->map[i][j + 1] != '1')
					ft_clean(file, RED "Error:\nThe top row is incorrect." RST);
			}
			// printf("i este       %d\n", i);
			// printf("j este       %d\n", j);
			// printf(G "[i][j]                 %c\n" RST,file->map[i+1][j]) ;
			if (file->map[i + 1][j] != '1')
				ft_clean(file, RED "Error:\nThe top row is incorrect." RST);
		}
		j++;
		i = 0;
	}
}

void	check_south_wall(t_map *file, int len_line) 
{
	int i;
	int j;
	int k;

	i = file->nr_rows_map - 1; // ultima linie din harta
	j = 0;
	while(j < len_line)
	{
		if (file->map[i][j] == '0' || check_cardinal(file->map[i][j]) == 1)
		if (file->map[i][j] != '1' && file->map[i][j] != ' ')
			ft_clean(file,RED "Error:\nThe south wall is incorrect.\n" RST);
		if (file->map[i][j] == ' ')
		{
			k = i;
			while(k > 0 && file->map[k][j] == ' ')
			{
				k--; // merg in sus pe coloana cat timp exista spatii
				if (j > 0 && j + 1 < len_line && file->map[k][j] == ' ' && ((file->map[k][j - 1] != '1' && file->map[k][j - 1] != ' ') ||
					(file->map[k][j + 1] != '1' && file->map[k][j + 1] != ' ')))
					ft_clean(file, RED "Error:\nThe south wall is incorrect.\n" RST);
			}
			//printf("The value is  %c si j %d si i %d\n", file->map[i][j], j, k);
			if (file->map[k][j] != '1' || k == 0)
				ft_clean(file, RED "Error:\nThe south wall is incorrect after spaces.\n" RST);
		}
		j++;
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
		//printf("line is %d - and lenght line: %d\n", i, len_line);
		if (len_line == 0) // check if empty lines in map
		{
			printf("The map is invalid.\n");
			file->error = true;
			ft_clean(file, RED "Error:\nThe line is empty.\n" RST);
		}
		check_cardinal_points(file, len_line, i);

		if (i == 0)
			check_north_wall(file, len_line); //DONE
		check_left_wall(file, file->map[i], i); //TODOo enclaves
		check_right_wall(file, file->map[i], len_line);


		i++;
	}
	len_line = ft_strlen(file->map[file->nr_rows_map -1]);
	check_south_wall(file, len_line); //DONE
	if (file->nr_cardinals != 1)
		ft_clean(file, "Error:\nThe number of cardinals are incorrect.\n");
	return 0;
}