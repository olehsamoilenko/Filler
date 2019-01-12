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
#include <fcntl.h> // files
#include "libft.h"

#define ESC 27
#define DELAY 10
#define GREEN_LEAF "\xF0\x9F\x8D\x80"
#define RED_LEAF "\xF0\x9F\x8D\x81"

void	get_players()
{
	int i = -1;
	char *line;
	while (++i < 5)
	{
		get_next_line(0, &line);
		ft_strdel(&line);
	}
	get_next_line(0, &line);
	char *p1 = ft_strsub(line, ft_strrchr(line, '/') - line + 1, ft_strlen(line) - (ft_strrchr(line, '/') - line));
	ft_strdel(&line);
	mvaddstr(20, 0, p1);
	get_next_line(0, &line);
	ft_strdel(&line);
	get_next_line(0, &line);
	char *p2 = ft_strsub(line, ft_strrchr(line, '/') - line + 1, ft_strlen(line) - (ft_strrchr(line, '/') - line));
	ft_strdel(&line);
	mvaddstr(21, 0, p2);
	refresh();
}

void	scale()
{
	

	

}

int		main(void)
{
	char *line;
	
	int fd = open("test.txt", O_RDWR | O_CREAT);
	setlocale(LC_ALL, "");

	

	initscr();
	curs_set(0);
	
	WINDOW *map;
	get_players();

	

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
			// refresh();
			map = newwin(lines + 2, (width + 2) * 2, 0, 0);
			box(map, 0, 0);
			start_color();
			
			init_pair(1, COLOR_WHITE, COLOR_GREEN);
			init_pair(2, COLOR_WHITE, COLOR_RED);
			init_pair(3, COLOR_WHITE, COLOR_BLACK);
			init_pair(4, COLOR_BLACK, COLOR_BLACK);
		}

		if (ft_strstr(line, "0123456789"))
		{
			int i = -1;
			// clear();
			int p1 = 0;
			int p2 = 0;
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
			mvaddstr(20, 20, ft_itoa(p1));
			mvaddstr(21, 20, ft_itoa(p2));
			wrefresh(map);
			refresh();
		}
		if (ft_strstr(line, "== X"))
			break;
		usleep(DELAY);
	}

	color_set(4, NULL);
	freopen("/dev/tty", "r", stdin);
	int ch;
	while (ch != ESC)
		ch = getch();
	ft_putnbr_fd(ch, fd);

	
	delwin(map);
	endwin();

	return (0);




} 
