/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:47:48 by lzins             #+#    #+#             */
/*   Updated: 2021/02/20 10:28:20 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	map_error(void)
{
	return (message_error("Error during map parsing"));
}

int	free_map_error(t_map *map, char **grid, int i)
{
	free_map(map);
	return (map_error());
}

int	print_invalid_map_error(t_map *map, int i, int j, char *message)
{
	int di;
	int dj;

	message_error(message);
	ft_printf("At x=%d, y=%d of map :\n%5d\u2193\n   -----\n", i, j, i);
	dj = -3;
	while (++dj < 3)
	{
		if (dj != 0)
			ft_printf("  |");
		else
			ft_printf("%d\u2192|", j);
		di = -3;
		while (++di < 3)
		{
			if (in_bounds2D(i + di, j + dj, map)
					&& map->grid[i + di][j + dj] != OUTSIDE)
				ft_putchar_fd(map->grid[i + di][j + dj], STDERR_FILENO);
			else
				ft_putchar_fd('.', STDERR_FILENO);
		}
		ft_printf("|\n");
	}
	ft_printf("   -----\n");
	return (-1);
}
