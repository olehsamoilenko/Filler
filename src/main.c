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

void		put_piece(t_array map, t_array piece)
{
	int i;
	int j;

	i = -1;
	while (++i < map.x)
	{
		j = -1;
		while (++j < map.y)
		{
			int sum = 0;
			if (i + piece.x <= map.x && j + piece.y <= map.y)
			{
				int n = -1;
				while (++n < piece.x)
				{
					int m = -1;
					while (++m < piece.y)
					{
						if (piece.array[n][m] == '*' &&
						(map.array[i + n][j + m] == 'O' || map.array[i + n][j + m] == 'o'))
							sum++;
						if (piece.array[n][m] == '*' &&
						(map.array[i + n][j + m] == 'x' || map.array[i + n][j + m] == 'X'))
							sum+=2;
					}
				}
			}
			if (sum == 1)
			{
				ft_printf("%i %i\n", i, j);
				return;
			}
		}
		
	}
	ft_printf("0 0\n");
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

void		create_map(t_array *map)
{
	char	*line;
	char	**output;
	int		i;

	get_next_line(0, &line); //Plateau 15 17:
	output = ft_strsplit(line, ' ');
	map->x = ft_atoi(output[1]);
	map->y = ft_atoi(output[2]);
	ft_arrclr(output);
	map->array = ft_memalloc(map->x * sizeof(char*));
	i = -1;
	while (++i < map->x)
		map->array[i] = ft_memalloc(map->y * sizeof(char));
}

void		take_piece(t_array *piece)
{
	char	*line;
	char	**output;
	int		i;

	get_next_line(0, &line);
	output = ft_strsplit(line, ' ');
	ft_strdel(&line);
	piece->x = ft_atoi(output[1]);
	piece->y = ft_atoi(output[2]);
	ft_arrclr(output);
	piece->array = ft_memalloc(piece->x * sizeof(char*));
	i = -1;
	while (++i < piece->x)
	{
		get_next_line(0, &line);
		piece->array[i] = ft_memalloc(piece->y * sizeof(char));
		ft_strcpy(&piece->array[i][0], &line[0]);
		ft_strdel(&line);
	}
}

int			main(void)
{
	int fd = open("file.txt", O_RDWR);

	char	*line;
	int i;

	t_array map;
	map.array = NULL;
	

	t_array piece;
	piece.array = NULL;

	// header $$$ exec p1 : [./osamoile.filler]
	get_next_line(0, &line);
	ft_strdel(&line);
	// ft_putstr_fd(ft_strjoin(line, "\n"), fd);
	// header

	while (1)
	{
		if (map.array == NULL)
			create_map(&map);
		else
		{
			
			get_next_line(0, &line); // skip plateau
			ft_strdel(&line);

		}
		
		get_next_line(0, &line);
		ft_strdel(&line);
		fill_map(map);
		if (piece.array != NULL)
			ft_arrclr(piece.array); // HERE IS THE PROBLEM
		take_piece(&piece);
		// ft_arrclr(piece.array);
		put_piece(map, piece);

	}

	return (0);
}
