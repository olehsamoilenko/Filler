/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:31:49 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/24 15:31:50 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		choose_player(char *line, char *me, char *opponent)
{
	if (ft_strstr(line, "p1"))
	{
		*me = 'o';
		*opponent = 'x';
	}
	else
	{
		*me = 'x';
		*opponent = 'o';
	}
}

int			main(void)
{
	char	*line;
	t_array	map;
	int		**dist_map;
	t_array	piece;
	char	me;
	char	opponent;
	int start_x = 0;
	int start_y = 0;
	int i;
	int j;
	int put_x = 0;
	int put_y = 0;
	piece.array = NULL;

	get_next_line(0, &line); // header $$$ exec p1 : [./osamoile.filler]
	choose_player(line, &me, &opponent);
	ft_strdel(&line);
	while (1)
	{
		get_next_line(0, &line);
		if (!ft_strstr(line, "Plateau"))
			return (0);
		if (map.array == NULL)
		{
			map = create_map(line, &dist_map);

		}
		ft_strdel(&line);
		get_next_line(0, &line); // skip 0123456789
		ft_strdel(&line);

		read_map(map);


		get_next_line(0, &line);
		if (piece.array != NULL)
			ft_arrclr(piece.array);
		piece = read_piece(line, &start_x, &start_y);


	
		analyze_map(map, dist_map, me, opponent);
		put_piece(map, dist_map, piece, me, opponent, &put_x, &put_y);
		ft_printf("%i %i\n", put_x - start_x, put_y - start_y);

	}
	return (0);
}
