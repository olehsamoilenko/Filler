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
#include <locale.h>
// #include <unistd.h>
#define DELAY 20000
#define GREEN_LEAF "\x20\xF0\x9F\x8D\x80"
#define RED_LEAF "\xF0\x9F\x8D\x81"

#include <stdio.h>
#include "libft.h"

int		draw()
{
	// setlocale(LC_ALL, "");
	initscr();
	curs_set(0);
	refresh();

	int width = 50;
	int height = 20;
	int offsetx = (COLS - width) / 2;
	int offsety = (LINES - height) / 2;
	WINDOW *win = newwin(height, width, offsety, offsetx);
	char *hello = "Hello world\uE030";
	attron(A_BOLD);
	// mvaddstr(LINES / 2, (COLS - ft_strlen(hello)) /2, hello);
	mvaddch(10, 10, 'a');
	mvaddstr(1, 0, "\xe2\x9c\x93");
	mvaddstr(10, 0, GREEN_LEAF);
	mvaddstr(10, 2, RED_LEAF);
	box(win, 0, 0);

	wrefresh(win);
	
	
	getch();
	delwin(win);
	endwin();

	return (0);
}

int		main(void)
{
	char *line;
	get_next_line(0, &line);
	ft_printf("test: %s\n", line);


} 
