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
	t_array	map;

	int		put_x;
	int		put_y;
	

	t_game	game;
	t_piece	figure;

	figure.piece.array = NULL;

	
	choose_player(&game);
	while (1)
	{
		get_next_line(0, &line);
		if (!ft_strstr(line, "Plateau"))
			return (0);
		if (map.array == NULL)
			map = create_map(line, &game.dist_map);
		ft_strdel(&line);
		read_map(&map);
		game.map = map;
		get_next_line(0, &line);
		ft_arrclr(figure.piece.array);
		figure.piece = read_piece(line, &figure.start_x, &figure.start_y);
		analyze_map(game.map, game.dist_map, game.me, game.opponent);
		put_piece(game.map, game.dist_map, figure.piece, game.me, game.opponent, &put_x, &put_y);
		ft_printf("%i %i\n", put_x - figure.start_x, put_y - figure.start_y);
	}
	return (0);
}
