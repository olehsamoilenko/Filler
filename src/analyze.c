/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:31:49 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/24 15:31:50 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		top(t_game *game, char player, t_map *map)
{
	int		i;
	int		j;

	i = -1;
	while (++i < map->x)
	{
		j = -1;
		while (++j < map->y)
		{
			if (ft_tolower(map->array[i][j]) == player)
				return (i);
		}
	}
	return (0);
}

int		left(t_game *game, char player, t_map *map)
{
	int		i;
	int		j;

	j = -1;
	while (++j < map->y)
	{
		i = -1;
		while (++i < map->x)
		{
			if (ft_tolower(map->array[i][j]) == player)
				return (j);
		}
	}
	return (0);
}

int		way_closed(t_game *game, int me_top, char opponent, t_map *map)
{
	int i = -1;
	while (++i < me_top)
	{
		if (ft_tolower(map->array[i][map->y - 1]) == opponent)
			return (1);
	}
	return (0);
}

void	analyze_map(t_game *game, t_map *map, char me, char opponent)
{
	int		me_top = top(game, me, map);
	int		op_top = top(game, opponent, map);
	int		me_left = left(game, me, map);


	if (me_top > op_top)
	{
		if (!way_closed(game, me_top, opponent, map))
			distance_to_cell(game, map, me, 0, map->y - 1);
		else
			distance_to_cell(game, map, me, map->x - 1, 0);
	}
	else
		distance_to_cell(game, map, me, op_top - 1, 0);
	if (me_left <= 2 || map->x > 20)
		distance_to_opponent(game, map, me, opponent);
}



