/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:31:49 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/24 15:31:50 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <filler.h>

t_array		get_figure()
{
	char	*line;
	t_array	figure;
	char	**output;
	int		i;

	get_next_line(0, &line); // Piece 1 3:
	output = ft_strsplit(line, ' ');
	ft_strdel(&line);
	figure.x = ft_atoi(output[1]);
	figure.y = ft_atoi(output[2]);
	ft_arrclr(output);
	figure.array = ft_memalloc(figure.x * sizeof(char*));
	// array[x] = 0;
	i = -1;
	while(++i < figure.x)
	{
		get_next_line(0, &line);
		figure.array[i] = ft_memalloc(figure.y * sizeof(char));
		ft_strcpy(figure.array[i], line);
		ft_strdel(&line);
	}
	return (figure);
}

t_array		get_map(char *plateau)
{
	char	*line;
	char	**output;
	t_array	map;
	int		i;

	// get_next_line(0, &line); // Plateau 15 17:
	output = ft_strsplit(plateau, ' ');
	// ft_strdel(&line);
	map.x = ft_atoi(output[1]);
	map.y = ft_atoi(output[2]);
	ft_arrclr(output);
	get_next_line(0, &line); // 01234567890123456
	ft_strdel(&line);
	map.array = ft_memalloc(map.x * sizeof(char*));
	// map.array[map.x] = 0;
	i = -1;
	while(++i < map.x)
	{
		get_next_line(0, &line);
		map.array[i] = ft_memalloc(map.y * sizeof(char));
		// map.array[i][map.y] = 0;
		ft_strcpy(map.array[i], &line[4]);
		ft_strdel(&line);
	}
	return (map);
}

void		put_figure(t_array map, t_array figure)
{
	int		i;
	int		j;

	int res_x = 0;
	int res_y = 0;
	
	i = -1;
	while (++i < map.x)
	{
		j = -1;
		while(++j < map.y)
		{
			int sum = 0;
			if (map.x < i + figure.x && map.y < j + figure.y)
			{
				int n = 0;
				int m = 0;
				// int n = -1;
				// while (++n < figure.x)
				// {
				// 	int m = -1;
				// 	while (++m < figure.y)
				// 	{
						if (map.array[i + n][j + m] == 'O' &&
							figure.array[n][m] == '*')
							sum++;
				// 	}
				// }
				if (sum == 1)
				{
					res_x = i;
					res_y = j;
				}
			}
			
		}
	}
	ft_printf("%d %d\n", res_x, res_y);
}


int			main(void)
{
	char	*line;
	
	get_next_line(0, &line);
	while (ft_strstr(line, "Plateau") == 0)
	{
		ft_strdel(&line);
		get_next_line(0, &line); // $$$exec, launched etc
	}
	

	t_array	map = get_map(line);
	t_array	figure = get_figure();

	put_figure(map, figure);
	
	
	return (0);
}
