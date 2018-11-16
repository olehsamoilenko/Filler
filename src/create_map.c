/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:31:49 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/24 15:31:50 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		create_map(t_game *game, char *plateau, t_map *map)
{
	char	**output;
	int		i;
	int		j;


	output = ft_strsplit(plateau, ' ');
	map->x = ft_atoi(output[1]);
	map->y = ft_atoi(output[2]);
	ft_arrclr(output);
	map->array = ft_chartable(map->x, map->y);
	map->int_array = (int**)ft_memalloc(map->x * sizeof(int*));
	i = -1;
	while (++i < map->x)
	{
		map->int_array[i] = (int*)ft_memalloc(map->y * sizeof(int));
		j = -1;
		while (++j < map->y)
			map->int_array[i][j] = -1;
	}
}