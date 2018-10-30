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
	ft_printf("8 2\n");
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

void		create_map(char *plateau, t_array *map)
{
	char	**output;
	int		i;

		output = ft_strsplit(plateau, ' ');
		map->x = ft_atoi(output[1]);
		map->y = ft_atoi(output[2]);
		ft_arrclr(output);
		map->array = ft_memalloc((map->x + 1) * sizeof(char*));
		map->array[map->x] = NULL;
		i = -1;
		while (++i < map->x)
			map->array[i] = ft_strnew(map->y);

	
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
		piece->array = ft_memalloc((piece->x + 1) * sizeof(char*));
		piece->array[piece->x] = NULL;
		i = -1;
		while (++i < piece->x)
		{
			get_next_line(0, &line);
			piece->array[i] = ft_strnew(piece->y);
			ft_strcpy(&piece->array[i][0], &line[0]);
			ft_strdel(&line);
		}
	
}

int			main(void)
{
	char	*line;
	t_array	map;
	t_array	piece;

	get_next_line(0, &line); // header $$$ exec p1 : [./osamoile.filler]
	ft_strdel(&line);
	while (1)
	{
		get_next_line(0, &line);
		if (!ft_strstr(line, "Plateau"))
			return (0);
		if (map.array == NULL)
			create_map(line, &map);
		ft_strdel(&line);
		get_next_line(0, &line); // skip 0123456789
		ft_strdel(&line);
		fill_map(map);
		get_next_line(0, &line);
		if (piece.array != NULL)
			ft_arrclr(piece.array);
		take_piece(line, &piece);
		put_piece(map, piece);
	}
	return (0);
}
