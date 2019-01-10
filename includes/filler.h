/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 11:39:25 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/02 11:39:26 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"

typedef struct		s_map
{
	char	**array;
	int		x;
	int		y;
	int		**int_array;
}					t_map;

typedef struct		s_game
{
	t_map	map;
	char	me;
	char	opponent;

}					t_game;

typedef struct		s_piece
{
	char	**array;
	int		x;
	int		y;
	int		start_x;
	int		start_y;
}					t_piece;

void		create_map(char *plateau, t_game *game);
void		read_map(t_game *game);
t_piece		read_piece(char *params);
int			distance_to_cell(t_map map, char me, int x, int y);
void		distance_to_opponent(t_map map, char me, char opponent);
void		analyze_map(t_game *game);
void		put_piece(t_game *game, t_map *map, t_piece *piece, int *put_x, int *put_y);

#endif
