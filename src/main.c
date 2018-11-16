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

void		choose_player(t_game *game)
{
	char *line;

	get_next_line(0, &line); // header $$$ exec p1 : [./osamoile.filler]
	if (ft_strstr(line, "p1"))
	{
		game->me = 'o';
		game->opponent = 'x';
	}
	else
	{
		game->me = 'x';
		game->opponent = 'o';
	}
	ft_strdel(&line);
}

int			main(void)
{
	char	*line;
	// t_array	map;

	int		put_x;
	int		put_y;
	

	t_game	game;
	t_piece	piece;

	piece.array = NULL;
	


	
	choose_player(&game);
	while (1)
	{
		get_next_line(0, &line);
		if (!ft_strstr(line, "Plateau"))
			return (0);
		if (game.map == NULL)
			create_map(&game, line, &game.dist_map);
		ft_strdel(&line);
		read_map(&game);
		get_next_line(0, &line);
		ft_arrclr(piece.array);

		piece = read_piece(line);
		analyze_map(&game, game.dist_map, game.me, game.opponent);
		put_piece(&game, game.dist_map, &piece, game.me, game.opponent, &put_x, &put_y);
		
		ft_printf("%i %i\n", put_x - piece.start_x, put_y - piece.start_y);
	}
	return (0);
}
