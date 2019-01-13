/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:08:55 by osamoile          #+#    #+#             */
/*   Updated: 2018/11/08 16:08:57 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void	read_sizes(char *line, t_visual *v)
{
	char	**nums;

	nums = ft_strsplit(line, ' ');
	v->m_heigth = ft_atoi(nums[1]);
	v->m_width = ft_atoi(nums[2]);
	ft_arrclr(nums);
}

void	init_wins(char *line, t_visual *v)
{
	setlocale(LC_ALL, "");
	initscr();
	curs_set(0);
	v->term_size = LINES * COLS;
	read_sizes(line, v);
	refresh();
	v->map = newwin(v->m_heigth + 2, (v->m_width + 2) * 2, 0, 0);
	v->scale = newwin(5, 2 * SCALE_LEN + 4,
		v->m_heigth / 2 - 1, (v->m_width + 2) * 2 + 10);
	mvwaddstr(v->scale, 1, LBL_IND - ft_strlen(v->p1_name) / 2, v->p1_name);
	mvwaddstr(v->scale, 1,
		SCALE_LEN * 2 - LBL_IND - ft_strlen(v->p2_name) / 2, v->p2_name);
	box(v->map, 0, 0);
	box(v->scale, 0, 0);
	wrefresh(v->scale);
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_GREEN);
	init_pair(2, COLOR_WHITE, COLOR_RED);
	init_pair(3, COLOR_WHITE, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
}
