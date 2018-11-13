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

void		create_map(t_game *game, char *plateau, int ***dist_map)
{
	char	**output;
	int		i;
	int		j;


	output = ft_strsplit(plateau, ' ');
	game->x_map = ft_atoi(output[1]);
	game->y_map = ft_atoi(output[2]);
	ft_arrclr(output);
	game->map = ft_chartable(game->x_map, game->y_map);
	*dist_map = (int**)ft_memalloc(game->x_map * sizeof(int*));
	i = -1;
	while (++i < game->x_map)
	{
		(*dist_map)[i] = (int*)ft_memalloc(game->y_map * sizeof(int));
		j = -1;
		while (++j < game->y_map)
			(*dist_map)[i][j] = -1;
	}
}