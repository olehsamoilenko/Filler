/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:08:55 by osamoile          #+#    #+#             */
/*   Updated: 2018/11/08 16:08:57 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void	get_players(t_visual *v)
{
	int		i;
	char	*line;

	i = -1;
	while (++i < 5)
	{
		get_next_line(0, &line);
		ft_strdel(&line);
	}
	get_next_line(0, &line);
	v->p1_name = ft_strsub(line, ft_strrchr(line, '/') - line + 1,
		ft_strlen(line) - (ft_strrchr(line, '/') - line));
	ft_strdel(&line);
	get_next_line(0, &line);
	ft_strdel(&line);
	get_next_line(0, &line);
	v->p2_name = ft_strsub(line, ft_strrchr(line, '/') - line + 1,
		ft_strlen(line) - (ft_strrchr(line, '/') - line));
	ft_strdel(&line);
}

void	handle_resize(t_visual *v, char *line)
{
	delwin(v->map);
	delwin(v->scale);
	endwin();
	ft_strdel(&line);
	while (get_next_line(0, &line))
	{
		ft_printf("%s\n", line);
		ft_strdel(&line);
	}
	while (get_next_line(0, &line))
	{
		ft_printf("%s\n", line);
		ft_strdel(&line);
	}
	freopen("/dev/tty", "r", stdin);
	ft_printf("%s%s\n%s",
		COLOR_PINK,
		"Error: please don't resize terminal during visualizer processing.",
		COLOR_RESET);
	exit(0);
}

void	over(t_visual *v)
{
	freopen("/dev/tty", "r", stdin);
	getch();
	delwin(v->map);
	delwin(v->scale);
	endwin();
}

int		main(void)
{
	char		*line;
	t_visual	*v;

	v = ft_memalloc(sizeof(t_visual));
	get_players(v);
	while (1)
	{
		if (LINES * COLS != v->term_size)
			handle_resize(v, line);
		get_next_line(0, &line);
		if (v->m_heigth == 0 && ft_strstr(line, "Plateau"))
			init_wins(line, v);
		if (ft_strstr(line, "0123456789"))
		{
			show_map(v);
			show_scale(v->scale, v->p1_points, v->p2_points);
		}
		if (ft_strstr(line, "== X"))
			break ;
		ft_strdel(&line);
		usleep(-100 * (v->m_heigth - 100));
	}
	show_winner(v->p1_points, v->p2_points, v);
	over(v);
	return (0);
}
