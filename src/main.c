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
					while (++m < piece.y)
					{

						if (piece.array[n][m] == '*')
						{
							if (ft_tolower(map.array[i + n][j + m]) == me)
								stacking_sum++;
							else if (ft_tolower(map.array[i + n][j + m]) == opponent)
								stacking_sum += 2;
							else
							{
								dist_sum += (*dist_map)[i + n][j + m];
							}
						} 
					}
				}
			}
			if (stacking_sum == 1 && dist_sum < dist_min)
			{
				put_x = i;
				put_y = j;
				dist_min = dist_sum;
			}

		}
	}
	// ft_putnbr_fd(put_x, fd);
	// ft_putstr_fd(" - figure x\n", fd);
	// ft_putnbr_fd(put_y, fd);
	// ft_putstr_fd(" - figure y\n", fd);
	ft_printf("%i %i\n", put_x - start_x, put_y - start_y);

	// ft_putstr_fd("FROM PUT_PIECE:\n", fd);
	// int i = -1;
	// while (++i < map.x)
	// {
	// 	int j = -1;
	// 	while (++j < map.y)
	// 	{
	// 		ft_putnbr_fd((*dist_map)[i][j], fd);
	// 		ft_putchar_fd(' ', fd);
	// 	}
	// 	ft_putchar_fd('\n', fd);
	// }
	// ft_putchar_fd('\n', fd);
	// ft_printf("%i %i\n", 0, 0);
}

void		fill_map(t_array map, int fd)
{
	int		i;
	char	*line;

	i = -1;
	while (++i < map.x)
	{
		get_next_line(0, &line);
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
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


	t_dot	*dots;
	int n_dots;
	



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
			n_dots = 25;
			dots = ft_memalloc(n_dots * sizeof(t_dot));
			
			i = -1;
			while (++i < 5)
			{
				j = -1;
				while (++j < 5)
				{
					dots[5 * i + j].x = i * 1 * map.x / 5;
					dots[5 * i + j].y = j * 1 * map.y / 5;
				}
			}
			// dots[0].x = 3 * map.x / 4 ;
			// dots[0].y = 3 * map.y / 4 ;

			// dots[1].x = 1 * map.x / 2 ;
			// dots[1].y = 3 * map.y / 4 ;

			// dots[2].x = 3 * map.x / 4 ;
			// dots[2].y = 1 * map.y / 2 ;

			// dots[3].x = 1 * map.x / 2 ;
			// dots[3].y = 1 * map.y / 2 ;

			// dots[4].x = 1 * map.x / 4 ;
			// dots[4].y = 3 * map.y / 4 ;

			// dots[5].x = 3 * map.x / 4 ;
			// dots[5].y = 1 * map.y / 4 ;

			// dots[6].x = 1 * map.x / 4 ;
			// dots[6].y = 1 * map.y / 2 ;

			// dots[7].x = 1 * map.x / 2 ;
			// dots[7].y = 1 * map.y / 4 ;

			// dots[8].x = 1 * map.x / 4 ;
			// dots[8].y = 1 * map.y / 4 ;

		}
			

		ft_strdel(&line);
		get_next_line(0, &line); // skip 0123456789
		ft_strdel(&line);
		fill_map(map, debug);

		

		// check
		// int i = -1;
		// while (++i < map.x)
		// {
		// 	int j = -1;
		// 	while (++j < map.y)
		// 	{
		// 		ft_putnbr_fd(dist_map[i][j], debug);
		// 		ft_putchar_fd(' ', debug);
		// 	}
		// 	ft_putchar_fd('\n', debug);
		// }
		// check


		get_next_line(0, &line);
		if (piece.array != NULL)
			ft_arrclr(piece.array);
		piece = take_piece(line);

		// check
		// i = -1;
		// while (++i < piece.x)
		// {
		// 	ft_putstr_fd(piece.array[i], debug);
		// 	ft_putchar_fd('\n', debug);
		// }
		// check

		start_x = 0;
		start_y = 0;
		reshape(&piece, debug, &start_x, &start_y);

		// check start
		// ft_putnbr_fd(start_x, fd);
		// ft_putstr_fd(" - start x\n", fd);
		// ft_putnbr_fd(start_y, fd);
		// ft_putstr_fd(" - start y\n", fd);
		// check start

		// check
		// ft_putstr_fd("AFTER RESHAPING\n", debug);
		i = -1;
		while (++i < piece.x)
		{
			ft_putstr_fd(piece.array[i], debug);
			ft_putchar_fd('\n', debug);
		}
		// check

		// int k = -1;
		// int min;
		// while (++k < n_dots)
		// {
		// 	min = distance_to_cell(map, &dist_map, me, dots[k].x, dots[k].y);
		// 	ft_putnbr_fd(min, debug);
		// 	ft_putstr_fd(" - min, ", debug);
		// 	ft_putnbr_fd(k, debug);
		// 	ft_putstr_fd(" - k\n", debug);
		// 	if (min > 5)
		// 		break;
		// }
		// if (k == n_dots)
		// {
		// 	ft_putstr_fd("attack!\n", debug);
		// 	distance_to_opponent(map, &dist_map, me, opponent);
		// }

		i = -1;
		int max_dist = 0;
		int best = -1;
		while (++i < n_dots)
		{
			dots[i].my_dist = distance_to_cell(map, &dist_map, me, dots[i].x, dots[i].y);
			dots[i].op_dist = distance_to_cell(map, &dist_map, opponent, dots[i].x, dots[i].y);
			if (dots[i].my_dist <= 1 || dots[i].op_dist <= 1)
				dots[i].reached = 1;
			ft_putnbr_fd(dots[i].reached, debug);
			ft_putstr_fd(" Dot ", debug);
			ft_putnbr_fd(i, debug);
			ft_putstr_fd(" (", debug);
			ft_putnbr_fd(dots[i].x, debug);
			ft_putstr_fd(", ", debug);
			ft_putnbr_fd(dots[i].y, debug);
			ft_putstr_fd(") ", debug);
			ft_putnbr_fd(dots[i].my_dist, debug);
			ft_putstr_fd(" - my, ", debug);
			ft_putnbr_fd(dots[i].op_dist, debug);
			ft_putstr_fd(" - op, ", debug);
			ft_putnbr_fd(dots[i].op_dist - dots[i].my_dist, debug);
			ft_putstr_fd(" - diff\n", debug);
			if (dots[i].reached == 0 && dots[i].op_dist > max_dist)
			{
				max_dist = dots[i].op_dist;
				best = i;
			}
			
			
		}
		ft_putnbr_fd(best, debug);
		ft_putstr_fd(" - best, ", debug);
		ft_putnbr_fd(max_dist, debug);
		ft_putstr_fd(" - min diff\n", debug);
		if (best != -1)
		{
			distance_to_cell(map, &dist_map, me, dots[best].x, dots[best].y);
		}
		else
		{
			distance_to_opponent(map, &dist_map, me, opponent);
		}
			

		// i = -1;
		// while (++i < map.x)
		// {
		// 	j = -1;
		// 	while (++j < map.y)
		// 	{
		// 		ft_putnbr_fd(dist_map[i][j], debug);
		// 		ft_putchar_fd(' ', debug);
		// 	}
		// 	ft_putchar_fd('\n', debug);
		// }
		// ft_putchar_fd('\n', debug);


		put_piece(map, &dist_map, piece, me, opponent, debug, start_x, start_y);



	}
	return (0);
}
