/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chartable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 18:00:27 by osamoile          #+#    #+#             */
/*   Updated: 2018/03/21 18:00:28 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_chartable(int x, int y)
{
	char	**table;
	int		i;

	table = (char**)ft_memalloc((x + 1) * sizeof(char*));
	table[x] = 0;
	i = -1;
	while (++i < x)
		table[i] = ft_strnew(y);
	return (table);
}
