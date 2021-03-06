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

int		top(t_map map, char player)
{
	int		i;
	int		j;

	i = -1;
	while (++i < map.x)
	{
		j = -1;
		while (++j < map.y)
		{
			if (ft_tolower(map.array[i][j]) == player)
				return (i);
		}
	}
	return (0);
}

int		left(t_map map, char player)
{
	int		i;
	int		j;

	j = -1;
	while (++j < map.y)
	{
		i = -1;
		while (++i < map.x)
		{
			if (ft_tolower(map.array[i][j]) == player)
				return (j);
		}
	}
	return (0);
}

int		way_closed(t_game *game, int me_top)
{
	int		i;

	i = -1;
	while (++i < me_top)
	{
		if (ft_tolower(game->map.array[i][game->map.y - 1]) == game->opponent)
			return (1);
	}
	return (0);
}

void	analyze_map(t_game *game)
{
	int		me_top;
	int		op_top;
	int		me_left;

	me_top = top(game->map, game->me);
	op_top = top(game->map, game->opponent);
	me_left = left(game->map, game->me);
	if (me_top > op_top)
	{
		if (!way_closed(game, me_top))
			distance_to_cell(game->map, game->me, 0, game->map.y - 1);
		else
			distance_to_cell(game->map, game->me, game->map.x - 1, 0);
	}
	else
		distance_to_cell(game->map, game->me, op_top - 1, 0);
	if (me_left <= 2 || game->map.x > 20)
		distance_to_opponent(game->map, game->opponent);
}
