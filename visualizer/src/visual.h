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
#include "libft.h"

typedef struct		s_visual
{
	
	WINDOW	*map;
	int		m_heigth;
	int		m_width;
	int		term_size;
	WINDOW	*scale;
	char	*p1_name;
	char	*p2_name;
	int		p1_points;
	int		p2_points;
}					t_visual;