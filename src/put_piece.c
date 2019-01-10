/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_piece.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:31:49 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/24 15:31:50 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		distance_sum(t_game *game, int *stacking_sum, int i, int j, t_piece *piece)
{
	int dist_sum = 0;
	int n = -1;
	int m;

	while (++n < piece->x)
	{
		m = -1;
		while (++m < piece->y)
		{
			if (piece->array[n][m] == '*')
			{
				if (ft_tolower(game->map.array[i + n][j + m]) == game->me)
					*stacking_sum+=1;
				else if (ft_tolower(game->map.array[i + n][j + m]) == game->opponent)
					*stacking_sum += 2;
				dist_sum += game->map.int_array[i + n][j + m];
			} 
		}
	}
	return (dist_sum);
}

void		put_piece(t_game *game, t_map *map, t_piece *piece, int *put_x, int *put_y)
{
	int i;
	int j;
	int stacking_sum;
	int dist_min = 10000;

	*put_x = 0;
	*put_y = 0;
	i = -1;
	while (++i < map->x)
	{
		j = -1;
		while (++j < map->y)
		{
			stacking_sum = 0;
			if (i + piece->x <= map->x && j + piece->y <= map->y &&
			distance_sum(game, &stacking_sum, i, j, piece) < dist_min &&
			stacking_sum == 1)
			{
				*put_x = i;
				*put_y = j;
				dist_min = distance_sum(game, &stacking_sum, i, j, piece);
			}
		}
	}
	
}