/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:31:49 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/24 15:31:50 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		distance_to_cell(t_game *game, int ***dist_map, char player, int x, int y)
{
	int		i;
	int		j;
	int		min;

	min = 10000;
	i = -1;
	while (++i < game->x_map)
	{
		j = -1;
		while (++j < game->y_map)
		{
			(*dist_map)[i][j] = ft_abs(x - i) + ft_abs(y - j);
			if (ft_tolower(game->map[i][j]) == player && (*dist_map)[i][j] < min)
				min = (*dist_map)[i][j];
		}
	}
	
	return (min);
}

void		distance_to_opponent(t_game *game, int ***dist_map, char me, char opponent)
{
	int		i;
	int		j;
	int		n;
	int		m;

	i = -1;
	while (++i < game->x_map)
	{
		j = -1;
		while (++j < game->y_map)
		{
			(*dist_map)[i][j] = 10000;
			n = -1;
			while (++n < game->x_map)
			{
				m = -1;
				while (++m < game->y_map)
				{
					if (ft_tolower(game->map[n][m]) == opponent &&
						ft_abs(n - i) + ft_abs(m - j) < (*dist_map)[i][j])
						(*dist_map)[i][j] = ft_abs(n - i) + ft_abs(m - j);
				}
			}
			
		}
	}
}