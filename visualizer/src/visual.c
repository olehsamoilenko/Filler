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

#include <locale.h> // smiles

#define COLOR_PINK "\033[1;35m"
#define COLOR_RESET "\033[0m"
#define DELAY 10000
#define SCALE_LEN 40
#define LB_IND 15
#define GREEN_LEAF "\xF0\x9F\x8D\x80"
#define RED_LEAF "\xF0\x9F\x8D\x81"

void	get_players(char **pl1, char **pl2)
{
	int i = -1;
	char *line;
	while (++i < 5)
	{
		get_next_line(0, &line);
		ft_strdel(&line);
	}
	get_next_line(0, &line);
	*pl1 = ft_strsub(line, ft_strrchr(line, '/') - line + 1, ft_strlen(line) - (ft_strrchr(line, '/') - line));
	ft_strdel(&line);
	get_next_line(0, &line);
	ft_strdel(&line);
	get_next_line(0, &line);
	*pl2 = ft_strsub(line, ft_strrchr(line, '/') - line + 1, ft_strlen(line) - (ft_strrchr(line, '/') - line));
	ft_strdel(&line);
}

void	read_sizes(char *line, t_visual *v)
{
	char	**nums;
	
	nums = ft_strsplit(line, ' ');
	v->m_heigth = ft_atoi(nums[1]);
	v->m_width = ft_atoi(nums[2]);
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
	v->scale = newwin(5, 2 * SCALE_LEN + 4, v->m_heigth / 2 - 1, (v->m_width + 2) * 2 + 10);
	mvwaddstr(v->scale, 1, LB_IND - ft_strlen(v->p1_name) / 2, v->p1_name);
	mvwaddstr(v->scale, 1, SCALE_LEN * 2 - LB_IND - ft_strlen(v->p2_name) / 2, v->p2_name);
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
	mvwaddstr(scale, 3, LB_IND - ft_strlen(n) / 2, n);
	ft_strdel(&n);
	n = ft_itoa(p2);
	mvwaddstr(scale, 3, 2 * SCALE_LEN - LB_IND - ft_strlen(n) /2, n);
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

void	show_map(t_visual *v)
{
	v->p1_points = 0;
	v->p2_points = 0;
	int i = -1;
	char	*line;
	while (++i < v->m_heigth)
	{
		get_next_line(0, &line);
		int j = 3;
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
		ft_strdel(&line);
	}
	wrefresh(v->map);
}

void	close_wins(t_visual *v)
{
	delwin(v->map);
	delwin(v->scale);
	endwin();
}

void	handle_resize(t_visual *v, char *line)
{
	close_wins(v);
	ft_strdel(&line);
	while (get_next_line(0, &line))
	{
		ft_printf("%s\n", line);
		ft_strdel(&line);
	}
	ft_printf("%sError: please don't resize terminal during visualizer processing.\n%s", COLOR_PINK, COLOR_RESET);
	system("leaks visualizer"); // !
	exit(0);
}


int		main(void)
{
	char		*line;
	t_visual	*v;
	
	v = ft_memalloc(sizeof(t_visual));
	get_players(&v->p1_name, &v->p2_name);
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
		if (LINES * COLS != v->term_size)
			handle_resize(v, line);
		ft_strdel(&line);
		usleep(DELAY);
	}
	show_winner(v->p1_points, v->p2_points, v);
	freopen("/dev/tty", "r", stdin);
	getch();
	close_wins(v);
	return (0);
} 
