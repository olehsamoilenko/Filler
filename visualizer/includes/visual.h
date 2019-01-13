/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:08:55 by osamoile          #+#    #+#             */
/*   Updated: 2018/11/08 16:08:57 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include <curses.h>
# include <locale.h>
# include "libft.h"

# define COLOR_PINK "\033[1;35m"
# define COLOR_RESET "\033[0m"
# define DELAY 10000
# define SCALE_LEN 40
# define LBL_IND 15
# define GREEN_LEAF "\xF0\x9F\x8D\x80"
# define RED_LEAF "\xF0\x9F\x8D\x81"

typedef struct	s_visual
{
	WINDOW	*map;
	int		m_heigth;
	int		m_width;
	int		term_size;
	WINDOW	*scale;
	char	*p1_name;
	char	*p2_name;
	int		p1_points;
	int		p2_points;
}				t_visual;

void			show_map(t_visual *v);
void			handle_resize(t_visual *v, char *line);
void			show_scale(WINDOW *scale, int p1, int p2);
void			show_winner(int p1, int p2, t_visual *v);
void			init_wins(char *line, t_visual *v);

#endif
