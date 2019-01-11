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
// #include <unistd.h>
#define ENTER 107
#define DELAY 50000
#define GREEN_LEAF "\xF0\x9F\x8D\x80"
#define RED_LEAF "\xF0\x9F\x8D\x81"

#include <stdio.h>
#include "libft.h"



	// attron(A_BOLD);

	// int offsetx = (COLS - width) / 2;
	// int offsety = (LINES - height) / 2;
	// WINDOW *win = newwin(0, 0, 0, 0);

int		draw()
{
	

	// char *hello = "Hello world";
	// mvaddstr(LINES / 2, (COLS - ft_strlen(hello)) / 2, hello);
	// WINDOW *win = newwin(10, 10, 10, 10);
	// box(win, '*', '&');
	// wprintw(win, GREEN_LEAF);
	// wrefresh(win);
	// delwin(win);

	return (0);
}

int		main(void)
{
	char *line;
	int fd = open("test.txt", O_RDWR | O_CREAT);
	setlocale(LC_ALL, "");

	int i = -1;
	while (++i < 9)
	{
		get_next_line(0, &line);
		ft_strdel(&line);
	}

	initscr();
	curs_set(0);



	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_WHITE, COLOR_GREEN);
	init_pair(2, COLOR_WHITE, COLOR_RED);


	int lines = 0;
	int width;

	while (1)
	{
		ft_strdel(&line);
		get_next_line(0, &line);

		if (lines == 0 && ft_strstr(line, "Plateau"))
		{
			char **nums = ft_strsplit(line, ' ');
			lines = ft_atoi(nums[1]);
			width = ft_atoi(nums[2]);
		}

		if (ft_strstr(line, "0123456789"))
		{
			i = -1;
			// clear();
			while (++i < lines)
			{
				ft_strdel(&line);
				get_next_line(0, &line);
				
				int j = 3;
				while (++j < width + 4)
				{
					if (line[j] == 'o')
						color_set(1, NULL);
					else if (line[j] == 'x')
						color_set(2, NULL);
					if (line[j] == 'O' || line[j] == 'o')
						mvaddstr(i, 2 * j - 8, GREEN_LEAF);
					else if (line[j] == 'X' || line[j] == 'x')
						mvaddstr(i, 2 * j - 8, RED_LEAF);
					else
						mvaddch(i, 2 * j - 8, line[j]);
					color_set(0, NULL);
				}
			}
			refresh();
		}
		if (ft_strstr(line, "== X"))
			break;
		usleep(DELAY);
	}



	
	freopen("/dev/tty", "r", stdin);
	int ch = getch();
	ft_putnbr_fd(ch, fd);

	// FILE *tty = fopen("/dev/tty", "r");
	// int c = getc(tty);
	// ft_putnbr_fd(c, fd);

	
	endwin();

	return (0);




} 
