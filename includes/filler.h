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

// typedef struct		s_array
// {

// }					t_array;

typedef struct		s_game
{
	char	**map;
	int		x_map;
	int		y_map;
	int		**dist_map;
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

void		create_map(t_game *game, char *plateau, int ***dist_map);
void		read_map(t_game *game);
char		**read_piece(char *params, int *piece_start_x, int *piece_start_y, int *x, int *y);
int		distance_to_cell(t_game *game, int ***dist_map, char player, int x, int y);
void		distance_to_opponent(t_game *game, int ***dist_map, char me, char opponent);
void	analyze_map(t_game *game, int **dist_map, char me, char opponent);
void		put_piece(t_game *game, int **dist_map, t_piece piece, char me, char opponent, int *put_x, int *put_y);

#endif
