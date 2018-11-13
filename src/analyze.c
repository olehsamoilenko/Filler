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

int		top(t_game *game, char player)
{
	int		i;
	int		j;

	i = -1;
	while (++i < game->x)
	{
		j = -1;
		while (++j < game->y)
		{
			if (ft_tolower(game->map[i][j]) == player)
				return (i);
		}
	}
	return (0);
}

int		left(t_game *game, char player)
{
	int		i;
	int		j;

	j = -1;
	while (++j < game->y)
	{
		i = -1;
		while (++i < game->x)
		{
			if (ft_tolower(game->map[i][j]) == player)
				return (j);
		}
	}
	return (0);
}

int		way_closed(t_game *game, int me_top, char opponent)
{
	int i = -1;
	while (++i < me_top)
	{
		if (ft_tolower(game->map[i][game->y - 1]) == opponent)
			return (1);
	}
	return (0);
}

void	analyze_map(t_game *game, int **dist_map, char me, char opponent)
{
	int		me_top = top(game, me);
	int		op_top = top(game, opponent);
	int		me_left = left(game, me);


	if (me_top > op_top)
	{
		if (!way_closed(game, me_top, opponent))
			distance_to_cell(game, &dist_map, me, 0, game->y - 1);
		else
			distance_to_cell(game, &dist_map, me, game->x - 1, 0);
	}
	else
		distance_to_cell(game, &dist_map, me, op_top - 1, 0);
	if (me_left <= 2 || game->x > 20)
		distance_to_opponent(game, &dist_map, me, opponent);
}



