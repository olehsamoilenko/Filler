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

void		create_map(char *plateau, t_game *game)
{
	char	**output;
	int		i;
	int		j;


	output = ft_strsplit(plateau, ' ');
	game->map.x = ft_atoi(output[1]);
	game->map.y = ft_atoi(output[2]);
	ft_arrclr(output);
	game->map.array = ft_chartable(game->map.x, game->map.y);
	game->map.int_array = (int**)ft_memalloc(game->map.x * sizeof(int*));
	i = -1;
	while (++i < game->map.x)
	{
		game->map.int_array[i] = (int*)ft_memalloc(game->map.y * sizeof(int));
		j = -1;
		while (++j < game->map.y)
			game->map.int_array[i][j] = -1;
	}
}