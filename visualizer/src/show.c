/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:08:55 by osamoile          #+#    #+#             */
/*   Updated: 2018/11/08 16:08:57 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void	print_line(char *line, int i, t_visual *v)
{
	int	j;

	j = 3;
	while (++j < v->m_width + 4)
	{
		if (line[j] == 'o')
			wattron(v->map, COLOR_PAIR(1));
		else if (line[j] == 'x')
			wattron(v->map, COLOR_PAIR(2));
		if (line[j] == 'O' || line[j] == 'o')
		{
			mvwaddstr(v->map, i + 1, 2 * j - 6, GREEN_LEAF);
			v->p1_points++;
		}
		else if (line[j] == 'X' || line[j] == 'x')
		{
			mvwaddstr(v->map, i + 1, 2 * j - 6, RED_LEAF);
			v->p2_points++;
		}
		else
			mvwaddch(v->map, i + 1, 2 * j - 6, line[j]);
		wattron(v->map, COLOR_PAIR(3));
	}
}

void	show_map(t_visual *v)
{
	int		i;
	char	*line;

	v->p1_points = 0;
	v->p2_points = 0;
	i = -1;
	while (++i < v->m_heigth)
	{
		get_next_line(0, &line);
		if ((int)ft_strlen(line) != v->m_width + 4)
			handle_resize(v, line);
		print_line(line, i, v);
		ft_strdel(&line);
	}
	wrefresh(v->map);
}

void	show_scale(WINDOW *scale, int p1, int p2)
{
	char	*n;
	int		i;
	int		percent;

	n = ft_itoa(p1);
	mvwaddstr(scale, 3, LBL_IND - ft_strlen(n) / 2, n);
	ft_strdel(&n);
	n = ft_itoa(p2);
	mvwaddstr(scale, 3, 2 * SCALE_LEN - LBL_IND - ft_strlen(n) / 2, n);
	ft_strdel(&n);
	percent = SCALE_LEN * p1 / (p1 + p2);
	i = 0;
	while (++i < percent)
		mvwaddstr(scale, 2, 2 * i, GREEN_LEAF);
	while (i++ < SCALE_LEN)
		mvwaddstr(scale, 2, 2 * i, RED_LEAF);
	wrefresh(scale);
}

void	show_winner(int p1, int p2, t_visual *v)
{
	char	*text;

	if (p1 > p2)
		text = ft_strjoin(v->p1_name, " WON!");
	else
		text = ft_strjoin(v->p2_name, " WON!");
	wattron(v->scale, A_BOLD | COLOR_PAIR(4));
	mvwaddstr(v->scale, 3, SCALE_LEN - ft_strlen(text) / 2, text);
	wrefresh(v->scale);
}
