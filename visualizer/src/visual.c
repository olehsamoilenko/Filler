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
	refresh(); // ?
}



int		main(void)
{
	char *line;

	setlocale(LC_ALL, "");

	t_visual *v = ft_memalloc(sizeof(t_visual));

	initscr();
	curs_set(0);

	int term_size = LINES * COLS;
	
	// WINDOW *map;
	// WINDOW *scale;


	// char *pl1;
	// char *pl2;
	int p1;
	int p2;
	char *n1 = NULL;
	char *n2 = NULL;
	get_players(&v->p1_name, &v->p2_name);
	
	
	while (1)
	{
		// ft_strdel(&line);
		get_next_line(0, &line);

		if (v->m_heigth == 0 && ft_strstr(line, "Plateau"))
		{
			char **nums = ft_strsplit(line, ' ');
			v->m_heigth = ft_atoi(nums[1]);
			v->m_width = ft_atoi(nums[2]);
			refresh();
			v->map = newwin(v->m_heigth + 2, (v->m_width + 2) * 2, 0, 0);
			v->scale = newwin(5, 2 * SCALE_LEN + 4, v->m_heigth / 2 - 1, (v->m_width + 2) * 2 + 10);
			mvwaddstr(v->scale, 1, LB_IND - ft_strlen(v->p1_name) / 2, v->p1_name);
			mvwaddstr(v->scale, 1, SCALE_LEN * 2 - LB_IND - ft_strlen(v->p2_name) / 2, v->p2_name);
			box(v->map, 0, 0);
			box(v->scale, 0, 0);
			wrefresh(v->scale);
			// refresh();
			start_color();
			
			init_pair(1, COLOR_WHITE, COLOR_GREEN);
			init_pair(2, COLOR_WHITE, COLOR_RED);
			init_pair(3, COLOR_WHITE, COLOR_BLACK);
			init_pair(4, COLOR_CYAN, COLOR_BLACK);
			// init_pair(4, COLOR_BLACK, COLOR_BLACK);
		}

		if (ft_strstr(line, "0123456789"))
		{
			int i = -1;
			// clear();
			p1 = 0;
			p2 = 0;
			while (++i < v->m_heigth)
			{
				ft_strdel(&line);
				get_next_line(0, &line);
				
				int j = 3;
				while (++j < v->m_width + 4)
				{
					if (line[j] == 'o')
						wattron(v->map, COLOR_PAIR(1));
					else if (line[j] == 'x')
					{
						wattron(v->map, COLOR_PAIR(2));
					}
					if (line[j] == 'O' || line[j] == 'o')
					{
						mvwaddstr(v->map, i + 1, 2 * j - 6, GREEN_LEAF);
						p1++;
					}
					else if (line[j] == 'X' || line[j] == 'x')
					{
						mvwaddstr(v->map, i + 1, 2 * j - 6, RED_LEAF);
						p2++;
					}
					else
					{
						mvwaddch(v->map, i + 1, 2 * j - 6, line[j]);
					}
					wattron(v->map, COLOR_PAIR(3));
				}

			}
			wrefresh(v->map);

			ft_strdel(&n1);
			n1 = ft_itoa(p1);
			ft_strdel(&n2);
			n2 = ft_itoa(p2);
			mvwaddstr(v->scale, 3, LB_IND - ft_strlen(n1) / 2, n1);
			mvwaddstr(v->scale, 3, 2 * SCALE_LEN - LB_IND - ft_strlen(n2) /2, n2);
			int p1_percent = SCALE_LEN * p1 / (p1 + p2);
			i = 0;
			while (++i < p1_percent)
				mvwaddstr(v->scale, 2, 2 * i, GREEN_LEAF);
			
			while (i++ < SCALE_LEN)
				mvwaddstr(v->scale, 2, 2 * i, RED_LEAF);
			wrefresh(v->scale);



		}
		if (ft_strstr(line, "== X"))
		{
			char *text;
			if (p1 > p2)
				text = ft_strjoin(v->p1_name, " WON!");
			else
				text = ft_strjoin(v->p2_name, " WON!");
			wattron(v->scale, A_BOLD | COLOR_PAIR(4));
			mvwaddstr(v->scale, 3, SCALE_LEN - ft_strlen(text)/ 2, text);
			wrefresh(v->scale);
			break;
		}
		if (LINES * COLS != term_size)
		{
			delwin(v->map);
			delwin(v->scale);
			endwin();
			ft_strdel(&line);
			while(get_next_line(0, &line))
			{
				ft_printf("%s\n", line);
				ft_strdel(&line);
			}
			ft_printf("%sError: please don't resize terminal during visualizer processing.\n%s", COLOR_PINK, COLOR_RESET);
			system("leaks visualizer");
			exit(0);
		}
		ft_strdel(&line);
		usleep(DELAY);
	}



	freopen("/dev/tty", "r", stdin);
	getch();
	delwin(v->map);
	delwin(v->scale);
	endwin();



	return (0);




} 
