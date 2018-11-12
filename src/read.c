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

void			reshape(t_array *piece, int *start_x, int *start_y)
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


void		read_map(t_array map)
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

t_array		read_piece(char *params, int *piece_start_x, int *piece_start_y)
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
		piece.array = ft_chartable(piece.x, piece.y);
		i = -1;
		while (++i < piece.x)
		{
			get_next_line(0, &line);
			ft_strcpy(piece.array[i], &line[0]);
			ft_strdel(&line);
		}
		reshape(&piece, piece_start_x, piece_start_y);
		return (piece);
}
