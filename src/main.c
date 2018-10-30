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

void		put_piece(t_array map, int ***dist_map, t_array piece, char me, char opponent)
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
	ft_printf("%i %i\n", put_x, put_y);
}

void		fill_map(t_array map)
{
	int		i;
	char	*line;

	i = -1;
	while (++i < map.x)
	{
		get_next_line(0, &line);
		ft_strcpy(&map.array[i][0], &line[4]);
		ft_strdel(&line);
	}
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

void		create_map(char *plateau, t_array *map, int ***dist_map)
{
	char	**output;
	int		i;
	int		j;

		output = ft_strsplit(plateau, ' ');
		map->x = ft_atoi(output[1]);
		map->y = ft_atoi(output[2]);
		ft_arrclr(output);
		// map->array = ft_memalloc((map->x + 1) * sizeof(char*));
		// map->array[map->x] = NULL;
		map->array = ft_chartable(map->x, map->y);
		*dist_map = (int**)ft_memalloc(map->x * sizeof(int*));
		i = -1;
		while (++i < map->x)
		{
			// map->array[i] = ft_strnew(map->y);
			(*dist_map)[i] = (int*)ft_memalloc(map->y * sizeof(int));
			j = -1;
			while (++j < map->y)
				(*dist_map)[i][j] = -1;
		}
}


void			reshape(t_array *piece, int fd)
{
	int		i;
	int		j;
	int		x_found = 0;
	int		y_found = 0;
	int		start_x;
	int		end_x;
	int		start_y;
	int		end_y;

	i = -1;
	while (++i < piece->x)
	{
		if (ft_strchr(piece->array[i], '*'))
		{
			end_x = i;
			if (!x_found)
			{
				start_x = i;
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
					start_y = i;
					y_found = 1;
				}
			}
				
		}
	}
	if (end_x - start_x + 1 != piece->x || end_y - start_y + 1 != piece->y)
	{
		ft_putstr_fd("NEED TO RESHAPE\n", fd);
		char **buf = piece->array;
		piece->x = end_x - start_x + 1;
		piece->y = end_y - start_y + 1;
		piece->array = ft_chartable(piece->x, piece->y);
		i = -1;
		while (++i < piece->x)
		{
			j = -1;
			while (++j < piece->y)
			{
				piece->array[i][j] = buf[i + start_x][j + start_y];
			}
		}
	}
		
}


void		take_piece(char *params, t_array *piece)
{
	char	*line;
	char	**output;
	int		i;

		output = ft_strsplit(params, ' ');
		ft_strdel(&params);
		piece->x = ft_atoi(output[1]);
		piece->y = ft_atoi(output[2]);
		ft_arrclr(output);
		// piece->array = ft_memalloc((piece->x + 1) * sizeof(char*));
		// piece->array[piece->x] = NULL;
		piece->array = ft_chartable(piece->x, piece->y);
		i = -1;
		while (++i < piece->x)
		{
			get_next_line(0, &line);
			// piece->array[i] = ft_strnew(piece->y);
			ft_strcpy(&piece->array[i][0], &line[0]);
			ft_strdel(&line);
		}
		
	
}

int			ft_abs(int n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

void		calculate_distances(t_array map, int ***dist_map, char me, char opponent)
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

int			main(void)
{
	char	*line;
	t_array	map;
	int		**dist_map;
	t_array	piece;
	char	me;
	char	opponent;


	int fd = open("file.txt", O_RDWR);

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
			create_map(line, &map, &dist_map);

		ft_strdel(&line);
		get_next_line(0, &line); // skip 0123456789
		ft_strdel(&line);
		fill_map(map);

		calculate_distances(map, &dist_map, me, opponent);

		// check
		int i = -1;
		while (++i < map.x)
		{
			int j = -1;
			while (++j < map.y)
			{
				ft_putnbr_fd(dist_map[i][j], fd);
				ft_putchar_fd(' ', fd);
			}
			ft_putchar_fd('\n', fd);
		}
		// check


		get_next_line(0, &line);
		if (piece.array != NULL)
			ft_arrclr(piece.array);
		take_piece(line, &piece);

		// check
		i = -1;
		while (++i < piece.x)
		{
			ft_putstr_fd(piece.array[i], fd);
			ft_putchar_fd('\n', fd);
		}
		// check

		// reshape(&piece, fd);

		// check
		i = -1;
		while (++i < piece.x)
		{
			ft_putstr_fd(piece.array[i], fd);
			ft_putchar_fd('\n', fd);
		}
		// check

		put_piece(map, &dist_map, piece, me, opponent);

		// check
		i = -1;
		while (++i < map.x)
		{
			int j = -1;
			while (++j < map.y)
			{
				ft_putnbr_fd(dist_map[i][j], fd);
				ft_putchar_fd(' ', fd);
			}
			ft_putchar_fd('\n', fd);
		}
		ft_putchar_fd('\n', fd);
		// check
	}
	return (0);
}
