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

#include <curses.h>
#include <locale.h> // smiles

#include "libft.h"

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
	// mvwaddstr(scale, 3, 15, p1);
	get_next_line(0, &line);
	ft_strdel(&line);
	get_next_line(0, &line);
	*pl2 = ft_strsub(line, ft_strrchr(line, '/') - line + 1, ft_strlen(line) - (ft_strrchr(line, '/') - line));
	ft_strdel(&line);
	// mvwaddstr(scale, 3, SCALE_LEN * 2 - 15, p2);
	refresh();
}


int		main(void)
{
	char *line;

	setlocale(LC_ALL, "");

	

	initscr();
	curs_set(0);

	int term_size = LINES * COLS;
	
	WINDOW *map;
	WINDOW *scale;


	char *pl1;
	char *pl2;
	int p1;
	int p2;
	get_players(&pl1, &pl2);
	
	

	int lines = 0;
	int width;

	while (1)
	{
		// ft_strdel(&line);
		get_next_line(0, &line);

		if (lines == 0 && ft_strstr(line, "Plateau"))
		{
			char **nums = ft_strsplit(line, ' ');
			lines = ft_atoi(nums[1]);
			width = ft_atoi(nums[2]);
			refresh();
			map = newwin(lines + 2, (width + 2) * 2, 0, 0);
			scale = newwin(5, 2 * SCALE_LEN + 4, lines / 2 - 1, (width + 2) * 2 + 10);
			mvwaddstr(scale, 1, LB_IND - ft_strlen(pl1) / 2, pl1);
			mvwaddstr(scale, 1, SCALE_LEN * 2 - LB_IND - ft_strlen(pl2) / 2, pl2);
			box(map, 0, 0);
			box(scale, 0, 0);
			wrefresh(scale);
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
			while (++i < lines)
			{
				ft_strdel(&line);
				get_next_line(0, &line);
				
				int j = 3;
				while (++j < width + 4)
				{
					if (line[j] == 'o')
						wattron(map, COLOR_PAIR(1));
					else if (line[j] == 'x')
					{
						wattron(map, COLOR_PAIR(2));
					}
					if (line[j] == 'O' || line[j] == 'o')
					{
						mvwaddstr(map, i + 1, 2 * j - 6, GREEN_LEAF);
						p1++;
					}
					else if (line[j] == 'X' || line[j] == 'x')
					{
						mvwaddstr(map, i + 1, 2 * j - 6, RED_LEAF);
						p2++;
					}
					else
					{
						mvwaddch(map, i + 1, 2 * j - 6, line[j]);
					}
					wattron(map, COLOR_PAIR(3));
				}
			}
			char *n1 = ft_itoa(p1);
			char *n2 = ft_itoa(p2);
			mvwaddstr(scale, 3, LB_IND - ft_strlen(n1) / 2, n1);
			mvwaddstr(scale, 3, 2 * SCALE_LEN - LB_IND - ft_strlen(n2) /2, n2);
			
			wrefresh(map);
			int p1_percent = SCALE_LEN * p1 / (p1 + p2);

			i = 0;
			while (++i < p1_percent)
				mvwaddstr(scale, 2, 2 * i, GREEN_LEAF);
			
			while (i++ < SCALE_LEN)
				mvwaddstr(scale, 2, 2 * i, RED_LEAF);
			wrefresh(scale);
			refresh();
		}
		if (ft_strstr(line, "== X"))
		{
			char *text;
			if (p1 > p2)
				text = ft_strjoin(pl1, " WON!");
			else
				text = ft_strjoin(pl2, " WON!");
			wattron(scale, A_BOLD | COLOR_PAIR(4));
			mvwaddstr(scale, 3, SCALE_LEN - ft_strlen(text)/ 2, text);
			wrefresh(scale);
			break;
		}
		if (LINES * COLS != term_size)
		{
			// exit(0);
			delwin(map);
			delwin(scale);
			endwin();
			
			while(get_next_line(0, &line))
			{
				ft_printf("%s\n", line);
				ft_strdel(&line);
			}
				
			ft_printf("%sError: please don't resize terminal during visualizer processing.\n%s", COLOR_PINK, COLOR_RESET);
			exit(0);

		}
		// printf("");

		usleep(DELAY);
	}

	freopen("/dev/tty", "r", stdin);
	getch();
	delwin(map);
	delwin(scale);
	endwin();

	return (0);




} 
