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

#include "visual.h"

void	get_players(t_visual *v)
{
	int		i = -1;
	char	*line;

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

void	show_scale(WINDOW *scale, int p1, int p2)
{
	char	*n;
	int		i;
	int		percent;
	
	n = ft_itoa(p1);
	mvwaddstr(scale, 3, LBL_IND - ft_strlen(n) / 2, n);
	ft_strdel(&n);
	n = ft_itoa(p2);
	mvwaddstr(scale, 3, 2 * SCALE_LEN - LBL_IND - ft_strlen(n) /2, n);
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
	v->p1_points = 0;
	v->p2_points = 0;
	int i = -1;
	char	*line;
	while (++i < v->m_heigth)
	{
		get_next_line(0, &line);
		print_line(line, i, v);
		ft_strdel(&line);
	}
	wrefresh(v->map);
}

void	over(t_visual *v)
{
	freopen("/dev/tty", "r", stdin);
	getch();
	delwin(v->map);
	delwin(v->scale);
	endwin();
}

void	handle_resize(t_visual *v, char *line)
{
	delwin(v->map);
	delwin(v->scale);
	endwin();
	// ft_strdel(&line);
	// while (get_next_line(0, &line))
	// {
	// 	ft_printf("%s\n", line);
	// 	ft_strdel(&line);
	// }
	freopen("/dev/tty", "r", stdin);
	ft_printf("%s%s\n%s",
		COLOR_PINK,
		"Error: please don't resize terminal during visualizer processing.",
		COLOR_RESET);
	exit(0);
}

int		main(void)
{
	char		*line;
	t_visual	*v;
	
	v = ft_memalloc(sizeof(t_visual));
	get_players(v);
	while (1)
	{
		get_next_line(0, &line);
		if (v->m_heigth == 0 && ft_strstr(line, "Plateau"))
			init_wins(line, v);
		if (ft_strstr(line, "0123456789"))
		{
			show_map(v);
			show_scale(v->scale, v->p1_points, v->p2_points);
		}
		if (ft_strstr(line, "== X"))
			break;
		if (LINES * COLS != v->term_size) // HERE
			handle_resize(v, line);
		ft_strdel(&line);
		usleep(-100 * (v->m_heigth - 100));
	}
	show_winner(v->p1_points, v->p2_points, v);
	over(v);
	return (0);
} 
