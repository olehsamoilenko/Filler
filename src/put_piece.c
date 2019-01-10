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

int		distance_sum(t_game *game, int *sum, int i, int j)
{
	int dist_sum;
	int n;
	int m;

	dist_sum = 0;
	n = -1;
	while (++n < game->piece.x)
	{
		m = -1;
		while (++m < game->piece.y)
		{
			if (game->piece.array[n][m] == '*')
			{
				if (ft_tolower(game->map.array[i + n][j + m]) == game->me)
					*sum += 1;
				else if (ft_tolower(game->map.array[i + n][j + m]) ==
					game->opponent)
					*sum += 2;
				dist_sum += game->map.int_array[i + n][j + m];
			}
		}
	}
	return (dist_sum);
}

void	put_piece(t_game *game, int *put_x, int *put_y)
{
	int i;
	int j;
	int sum;
	int dist_min;

	dist_min = 10000;
	*put_x = 0;
	*put_y = 0;
	i = -1;
	while (++i < game->map.x)
	{
		j = -1;
		while (++j < game->map.y)
		{
			sum = 0;
			if (i + game->piece.x <= game->map.x &&
			j + game->piece.y <= game->map.y &&
			distance_sum(game, &sum, i, j) < dist_min && sum == 1)
			{
				*put_x = i;
				*put_y = j;
				dist_min = distance_sum(game, &sum, i, j);
			}
		}
	}
}
