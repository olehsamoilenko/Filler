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
	game->x = ft_atoi(output[1]);
	game->y = ft_atoi(output[2]);
	ft_arrclr(output);
	game->map = ft_chartable(game->x, game->y);
	*dist_map = (int**)ft_memalloc(game->x * sizeof(int*));
	i = -1;
	while (++i < game->x)
	{
		(*dist_map)[i] = (int*)ft_memalloc(game->y * sizeof(int));
		j = -1;
		while (++j < game->y)
			(*dist_map)[i][j] = -1;
	}
}