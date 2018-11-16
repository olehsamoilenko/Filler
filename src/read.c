/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:31:49 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/24 15:31:50 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"



void		read_map(t_game *game, t_map *map)
{
	int		i;
	char	*line;

	get_next_line(0, &line); // skip 0123456789
	ft_strdel(&line);
	i = -1;
	while (++i < map->x)
	{
		get_next_line(0, &line);
		ft_strcpy(&map->array[i][0], &line[4]);
		ft_strdel(&line);
	}
}

void	start_end_x(t_piece *piece, int *end_x)
{
	int i;
	int		x_found = 0;

	i = -1;
	while (++i < piece->x)
	{
		if (ft_strchr(piece->array[i], '*'))
		{
			*end_x = i;
			if (!x_found)
			{
				piece->start_x = i;
				x_found = 1;
			}
		}
	}
}

void	start_end_y(t_piece *piece, int *end_y)
{
	int	i;
	int j;
		int		y_found = 0;

	i = -1;
	while (++i < piece->y)
	{
		j = -1;
		while (++j < piece->x)
		{
			if (piece->array[j][i] == '*')
			{
				*end_y = i;
				if (!y_found)
				{
					piece->start_y = i;
					y_found = 1;
				}
			}
		}
	}
}

void			reshape(t_piece *piece)
{
	int	i;
	int	j;
	int	end_x;
	int	end_y;

	start_end_x(piece, &end_x);
	start_end_y(piece, &end_y);
	if (end_x - piece->start_x + 1 != piece->x || end_y - piece->start_y + 1 != piece->y)
	{
		char **buf = piece->array;
		
		piece->x = end_x - piece->start_x + 1;
		piece->y = end_y - piece->start_y + 1;
		piece->array = ft_chartable(piece->x, piece->y);
		i = -1;
		while (++i < piece->x)
		{
			j = -1;
			while (++j < piece->y)
				piece->array[i][j] = buf[i + piece->start_x][j + piece->start_y];
		}
		ft_arrclr(buf);
	}
}

t_piece		read_piece(char *params)
{
	char	*line;
	char	**output;
	int		i;
	t_piece	piece;

	output = ft_strsplit(params, ' ');
	ft_strdel(&params);
	piece.x = ft_atoi(output[1]);
	piece.y = ft_atoi(output[2]);
	ft_arrclr(output);
	piece.array = ft_chartable(piece.x, piece.y);
	i = -1;
	while (++i < piece.x)
	{
		get_next_line(0, &line);
		ft_strcpy(piece.array[i], &line[0]);
		ft_strdel(&line);
	}
	reshape(&piece);

	return (piece);
}
