/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:31:49 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/24 15:31:50 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <filler.h>
#include <fcntl.h> // trahs

void		put_piece(t_array map, int ***dist_map, t_array piece, char me, char opponent, int fd, int start_x, int start_y)
{
	int i;
	int j;
	int put_x = 0;
	int put_y = 0;

	int dist_min = 10000;
	float dist_avg = 10000;
	int count;
	i = -1;
	while (++i < map.x)
	{
		j = -1;
		while (++j < map.y)
		{
			int stacking_sum = 0;
			int dist_sum = 0;
			if (i + piece.x <= map.x && j + piece.y <= map.y)
			{
				int n = -1;
				while (++n < piece.x)
				{
					int m = -1;
					count = 0;
					while (++m < piece.y)
					{

						if (piece.array[n][m] == '*')
						{
							if (ft_tolower(map.array[i + n][j + m]) == me)
								stacking_sum++;
							else if (ft_tolower(map.array[i + n][j + m]) == opponent)
								stacking_sum += 2;

							dist_sum += (*dist_map)[i + n][j + m];
							count++;
						} 
					}
				}
			}
			if (stacking_sum == 1 && (float)dist_sum / count < dist_avg)
			{
				put_x = i;
				put_y = j;
				dist_min = dist_sum;
				dist_avg = (float)dist_sum / count;
				
			}

		}
	}
	ft_putnbr_fd(put_x, fd);
	ft_putstr_fd(" - put x\n", fd);
	ft_putnbr_fd(put_y, fd);
	ft_putstr_fd(" - put y\n", fd);

	
	ft_printf("%i %i\n", put_x - start_x, put_y - start_y);


}

void		fill_map(t_array map, int fd, char opponent, int *op_x, int *op_y)
{
	int		i;
	char	*line;

	i = -1;
	while (++i < map.x)
	{
		// *op_x = 0;
		// *op_y = 0;
		get_next_line(0, &line);

		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		int j = -1;
		while (++j < map.y)
		{
			if (ft_tolower(line[j + 4]) == opponent &&
			ft_tolower(map.array[i][j]) != opponent)
			{
				*op_x = i;
				*op_y = j;
			}
		}


		ft_strcpy(&map.array[i][0], &line[4]);
		ft_strdel(&line);
	}
	// ft_putchar_fd('\n', fd);
}

char	**ft_chartable(int x, int y)
{
	char	**table;
	int		i;

	table = (char**)ft_memalloc((x + 1) * sizeof(char*));
	table[x] = NULL;
	i = -1;
	while (++i < x)
	{
		table[i] = ft_strnew(y);
	}
	return (table);
}

t_array		create_map(char *plateau, int ***dist_map)
{
	char	**output;
	int		i;
	int		j;
	t_array	map;

		output = ft_strsplit(plateau, ' ');
		map.x = ft_atoi(output[1]);
		map.y = ft_atoi(output[2]);
		ft_arrclr(output);
		// map.array = ft_memalloc((map.x + 1) * sizeof(char*));
		// map.array[map.x] = NULL;
		map.array = ft_chartable(map.x, map.y);
		*dist_map = (int**)ft_memalloc(map.x * sizeof(int*));
		i = -1;
		while (++i < map.x)
		{
			// map.array[i] = ft_strnew(map.y);
			(*dist_map)[i] = (int*)ft_memalloc(map.y * sizeof(int));
			j = -1;
			while (++j < map.y)
				(*dist_map)[i][j] = -1;
		}
		return (map);
}


void			reshape(t_array *piece, int fd, int *start_x, int *start_y)
{
	int		i;
	int		j;
	int		x_found = 0;
	int		y_found = 0;
	int		end_x;
	int		end_y;

	i = -1;
	while (++i < piece->x)
	{
		if (ft_strchr(piece->array[i], '*'))
		{
			end_x = i;
			if (!x_found)
			{
				*start_x = i;
				x_found = 1;
			}
		}
	}

	i = -1;
	while (++i < piece->y)
	{
		j = -1;
		while (++j < piece->x)
		{
			if (piece->array[j][i] == '*')
			{
				end_y = i;
				if (!y_found)
				{
					*start_y = i;
					y_found = 1;
				}
			}
				
		}
	}
	if (end_x - *start_x + 1 != piece->x || end_y - *start_y + 1 != piece->y)
	{
		// ft_putstr_fd("NEED TO RESHAPE\n", fd);
		char **buf = piece->array;
		
		piece->x = end_x - *start_x + 1;
		piece->y = end_y - *start_y + 1;
		piece->array = ft_chartable(piece->x, piece->y);
		i = -1;
		while (++i < piece->x)
		{
			j = -1;
			while (++j < piece->y)
			{
				piece->array[i][j] = buf[i + *start_x][j + *start_y];
			}
		}
		ft_arrclr(buf);
	}

		
}


t_array		take_piece(char *params)
{
	char	*line;
	char	**output;
	int		i;
	t_array	piece;

		output = ft_strsplit(params, ' ');
		ft_strdel(&params);
		piece.x = ft_atoi(output[1]);
		piece.y = ft_atoi(output[2]);
		ft_arrclr(output);
		// piece->array = ft_memalloc((piece->x + 1) * sizeof(char*));
		// piece->array[piece->x] = NULL;
		piece.array = ft_chartable(piece.x, piece.y);
		i = -1;
		while (++i < piece.x)
		{
			get_next_line(0, &line);
			// piece->array[i] = ft_strnew(piece->y);
			ft_strcpy(piece.array[i], &line[0]);
			ft_strdel(&line);
		}
		return (piece);
		
	
}

int			ft_abs(int n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

void		distance_to_opponent(t_array map, int ***dist_map, char me, char opponent)
{
	int		i;
	int		j;
	int		n;
	int		m;
	int		res;

	i = -1;
	while (++i < map.x)
	{
		j = -1;
		while (++j < map.y)
		{
			(*dist_map)[i][j] = 10000;
			n = -1;
			while (++n < map.x)
			{
				m = -1;
				while (++m < map.y)
				{
					if (ft_tolower(map.array[n][m]) == opponent &&
						ft_abs(n - i) + ft_abs(m - j) < (*dist_map)[i][j])
						(*dist_map)[i][j] = ft_abs(n - i) + ft_abs(m - j);
				}
			}
			
		}
	}
	
}

int		distance_to_cell(t_array map, int ***dist_map, char player, int x, int y)
{
	int		i;
	int		j;
	int		min;

	min = 10000;
	i = -1;
	while (++i < map.x)
	{
		j = -1;
		while (++j < map.y)
		{
			(*dist_map)[i][j] = ft_abs(x - i) + ft_abs(y - j);
			if (ft_tolower(map.array[i][j]) == player && (*dist_map)[i][j] < min)
				min = (*dist_map)[i][j];
		}
	}
	
	return (min);
}

void	analyze_map(t_array map, int *me_top, int *op_top, int *me_left, int *op_left, char me, char opponent)
{
	int i;
	int j;

	i = map.x;
	while (--i >= 0)
	{
		j = -1;
		while (++j < map.y)
		{
			if (ft_tolower(map.array[i][j]) == me)
				*me_top = i;
			if (ft_tolower(map.array[i][j]) == opponent)
				*op_top = i;
		}
	}
	j = map.y;
	while (--j >= 0)
	{
		i = -1;
		while (++i < map.x)
		{
			if (ft_tolower(map.array[i][j]) == me)
				*me_left = j;
			if (ft_tolower(map.array[i][j]) == opponent)
				*op_left = j;
		}
	}
}

int			main(void)
{
	char	*line;
	t_array	map;
	int		**dist_map;
	t_array	piece;
	char	me;
	char	opponent;
	int start_x;
	int start_y;
	int i;
	int j;



	

	int order = 0;

	piece.array = NULL;


	int debug = open("file.txt", O_RDWR);
	int karta = open("map.txt", O_RDWR);

	get_next_line(0, &line); // header $$$ exec p1 : [./osamoile.filler]
	if (ft_strstr(line, "p1"))
	{
		me = 'o';
		opponent = 'x';
	}
	else
	{
		me = 'x';
		opponent = 'o';
	}
	ft_strdel(&line);
	while (1)
	{
		get_next_line(0, &line);
		if (!ft_strstr(line, "Plateau"))
			return (0);
		if (map.array == NULL)
		{
			map = create_map(line, &dist_map);

		}
		ft_strdel(&line);
		get_next_line(0, &line); // skip 0123456789
		ft_strdel(&line);
		int op_x = 0;
		int op_y = 0;
		fill_map(map, debug, opponent, &op_x, &op_y);
		// where is opponent moving ?
		// ft_putnbr_fd(op_x, debug);
		// ft_putstr_fd(" - op x\n", debug);
		// ft_putnbr_fd(op_y, debug);
		// ft_putstr_fd(" - op y\n", debug);
		// where is opponent moving ?

		get_next_line(0, &line);
		if (piece.array != NULL)
			ft_arrclr(piece.array);
		piece = take_piece(line);

		start_x = 0;
		start_y = 0;
		reshape(&piece, debug, &start_x, &start_y);

		i = -1;
		while (++i < piece.x)
		{
			ft_putstr_fd(piece.array[i], debug);
			ft_putchar_fd('\n', debug);
		}

			int me_top = 0;
			int op_top = 0;
			int me_left = 0;
			int op_left = 0;
			analyze_map(map, &me_top, &op_top, &me_left, &op_left, me, opponent);
			ft_putnbr_fd(me_top, debug);
			ft_putstr_fd(" - me top\n", debug);
			ft_putnbr_fd(op_top, debug);
			ft_putstr_fd(" - op top\n", debug);
			ft_putnbr_fd(me_left, debug);
			ft_putstr_fd(" - me left\n", debug);
			ft_putnbr_fd(op_left, debug);
			ft_putstr_fd(" - op left\n", debug);


			distance_to_cell(map, &dist_map, me, 0, map.x - 1);
			if (me_top < op_top)
			{
				distance_to_cell(map, &dist_map, me, op_top - 1, 0);
				ft_putstr_fd("attacking\n", debug);
			}
			if (me_left <= 2)
			{
				distance_to_opponent(map, &dist_map, me, opponent);
			}


			

		put_piece(map, &dist_map, piece, me, opponent, debug, start_x, start_y);

	}
	return (0);
}
