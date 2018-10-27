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


int			main(void)
{
	// char	*line;
	
	// get_next_line(0, &line);
	// while (ft_strstr(line, "Plateau") == 0)
	// {
	// 	ft_strdel(&line);
	// 	get_next_line(0, &line); // $$$exec, launched etc
	// }
	// t_array	map = get_map(line);
	// t_array	figure = get_figure();
	int i;
	int j;

	t_array map;
	map.x = 15;
	map.y = 17;
	map.array = ft_memalloc(map.x * sizeof(char*));
	i = 0;
	map.array[i++] = "................."; //000
	map.array[i++] = "................."; //001
	map.array[i++] = "................."; //002
	map.array[i++] = "................."; //003
	map.array[i++] = "................."; //004
	map.array[i++] = "................."; //005
	map.array[i++] = "................."; //006
	map.array[i++] = "................."; //007
	map.array[i++] = "..O.............."; //008
	map.array[i++] = "................."; //009
	map.array[i++] = "................."; //010
	map.array[i++] = "................."; //011
	map.array[i++] = "..............X.."; //012
	map.array[i++] = "................."; //013
	map.array[i++] = "................."; //014

	t_array figure;
	figure.x = 2;
	figure.y = 2;
	figure.array = ft_memalloc(figure.x * sizeof(char*));
	figure.array[0] = "*.";
	figure.array[1] = "*.";
	
	i = -1;
	while (++i < map.x)
		ft_printf("%s\n", map.array[i]);
	i = -1;
	while (++i < figure.x)
		ft_printf("%s\n", figure.array[i]);

	i = -1;
	while (++i < map.x)
	{
		j = -1;
		while (++j < map.y)
		{
			if (map.array[i][j] == 'O' || map.array[i][j] == 'o')
				ft_printf("%c", '1');
			else
				ft_printf("%c", map.array[i][j]);
		}
		ft_printf("\n");
	}


	// put_figure(map, figure);
	
	return (0);
}
