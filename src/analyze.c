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

int		top(t_array map, char player)
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

int		left(t_array map, char player)
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

int		way_closed(t_array map, int me_top, char opponent)
{
	int i = -1;
	while (++i < me_top)
	{
		if (ft_tolower(map.array[i][map.y - 1]) == opponent)
			return (1);
	}
	return (0);
}

void	analyze_map(t_array map, int **dist_map, char me, char opponent)
{
	int		me_top = top(map, me);
	int		op_top = top(map, opponent);
	int		me_left = left(map, me);

	if (me_top > op_top)
	{
		if (!way_closed(map, me_top, opponent))
			distance_to_cell(map, &dist_map, me, 0, map.y - 1);
		else
			distance_to_cell(map, &dist_map, me, map.x - 1, 0);
	}
	else
		distance_to_cell(map, &dist_map, me, op_top - 1, 0);
	if (me_left <= 2 || map.x > 20)
		distance_to_opponent(map, &dist_map, me, opponent);
}



