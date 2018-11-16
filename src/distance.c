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

int		distance_to_cell(t_game *game, t_map *map, char player, int x, int y)
{
	int		i;
	int		j;
	int		min;

	min = 10000;
	i = -1;
	while (++i < map->x)
	{
		j = -1;
		while (++j < map->y)
		{
			map->int_array[i][j] = ft_abs(x - i) + ft_abs(y - j);
			if (ft_tolower(map->array[i][j]) == player && map->int_array[i][j] < min)
				min = map->int_array[i][j];
		}
	}
	
	return (min);
}

void		distance_to_opponent(t_game *game, t_map *map, char me, char opponent)
{
	int		i;
	int		j;
	int		n;
	int		m;

	i = -1;
	while (++i < map->x)
	{
		j = -1;
		while (++j < map->y)
		{
			map->int_array[i][j] = 10000;
			n = -1;
			while (++n < map->x)
			{
				m = -1;
				while (++m < map->y)
				{
					if (ft_tolower(map->array[n][m]) == opponent &&
						ft_abs(n - i) + ft_abs(m - j) < map->int_array[i][j])
						map->int_array[i][j] = ft_abs(n - i) + ft_abs(m - j);
				}
			}
			
		}
	}
}