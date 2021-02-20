/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_new1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:02:46 by lzins             #+#    #+#             */
/*   Updated: 2021/02/20 10:25:42 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "map_new.h"

void	mapline_dimentions(char *line, int *i1, int *i2)
{
	int i;

	i = -1;
	*i1 = -1;
	while (line[++i])
	{
		if (line[i] != ' ' && *i1 == -1)
			*i1 = i;
	}
	if (*i1 == -1)
		*i1 = 0;
	i = ft_strlen(line) - 1;
	*i2 = -1;
	while (i >= 0 && line[i])
	{
		if (line[i] != ' ' && *i2 == -1)
			*i2 = i;
		i--;
	}
	if (*i2 == -1)
		*i2 = 0;
}

void	map_dimentions(t_list *map_lst, int *i1, int *i2)
{
	int line_offsets[2];
	int width;
	int height;

	mapline_dimentions(map_lst->content, i1, i2);
	while ((map_lst = map_lst->next))
	{
		mapline_dimentions(map_lst->content, &line_offsets[0],
			&line_offsets[1]);
		if (line_offsets[0] < *i1)
			*i1 = line_offsets[0];
		if (line_offsets[1] > *i2)
			*i2 = line_offsets[1];
	}
}

void	fill_map_grid(t_list *map_lst, t_map *map, int i1, int i2)
{
	char	*mapline;
	int		mapline_len;
	int		j;
	int		i;

	j = 0;
	while (map_lst)
	{
		mapline = map_lst->content;
		mapline_len = ft_strlen(mapline);
		i = i1 - 1;
		while (++i <= i2)
		{
			map->grid[i - i1][j] = i < mapline_len ? mapline[i] : ' ';
		}
		map_lst = map_lst->next;
		j++;
	}
}
