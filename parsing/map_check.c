/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 17:45:34 by lzins             #+#    #+#             */
/*   Updated: 2021/02/16 15:44:47 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	is_not_telep_exit(t_map *map, int i, int j)
{
	if (!in_bounds2D(i, j, map)
			|| map->grid[i][j] == OUTSIDE
			|| map->grid[i][j] == WALL)
		return (1);
	return (0);
}

static int	map_telep_condition(t_map *map, int i, int j)
{
	int	di;
	int	dj;
	int	axis;
	int	delta;
	int	n_exits;

	n_exits = 4;
	axis = -1;
	while (++axis <= 1)
	{
		delta = -1;
		while (delta < 2)
		{
			di = (axis == 0) ? delta : 0;
			dj = (axis == 1) ? delta : 0;
			n_exits -= is_not_telep_exit(map, i + di, j + dj);
			delta += 2;
		}
	}
	if (n_exits == 0)
		return (message_error("Wrong placement of teleportation block "
		"(needs at least one connection to the inside)"));
	return (1);
}

static int	map_check_surround(t_map *map, int i, int j)
{
	int di;
	int dj;

	di = -2;
	while (++di < 2)
	{
		dj = -2;
		while (++dj < 2)
		{
			if (di == 0 && dj == 0)
				continue ;
			if (in_bounds2D(i + di, j + dj, map)
					&& map->grid[i][j] == OUTSIDE
					&& map->grid[i + di][j + dj] != WALL
					&& map->grid[i + di][j + dj] != OUTSIDE
					&& map->grid[i + di][j + dj] != TELEP)
				return (-1);
			if (!in_bounds2D(i + di, j + dj, map)
					&& map->grid[i][j] != OUTSIDE
					&& map->grid[i][j] != WALL
					&& map->grid[i][j] != TELEP)
				return (-1);
		}
	}
	return (1);
}

static int	map_check_one(t_map *map, int i, int j, t_special_blocks_counter *c)
{
	if (map->grid[i][j] == TELEP)
	{
		if (map_telep_condition(map, i, j) == -1)
			return (-1);
		c->n_telep++;
	}
	if (map_check_surround(map, i, j) == -1)
		return (print_invalid_map_error(map, i, j, "Map not surounded by 1s"));
	if (ft_strchr("NSWE", map->grid[i][j]))
		c->n_player_start++;
	if (c->n_player_start > 1)
		return (print_invalid_map_error(map, i, j, "At least two player-start"
		"given. Second one here :"));
	return (1);
}

int			map_check(t_map *map)
{
	int							i;
	int							j;
	t_special_blocks_counter	c;

	c.n_player_start = 0;
	c.n_telep = 0;
	i = -1;
	while (++i < map->width)
	{
		j = -1;
		while (++j < map->height)
			if (map_check_one(map, i, j, &c) == -1)
				return (-1);
	}
	if (c.n_player_start == 0)
		return (message_error("No player-start found (N/S/W/E character)"));
	if (c.n_telep == 1)
		return (message_error("Only one teleporter found."
		" Make a choice for christ sake !"));
	return (1);
}
