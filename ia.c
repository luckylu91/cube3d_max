/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:57:45 by lzins             #+#    #+#             */
/*   Updated: 2021/02/20 10:31:18 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// ///
// void print_ipt2d(void *val_ptr)
// {
// 	t_ipt2d val;

// 	val = *(t_ipt2d*)val_ptr;
// 	printf("(%d, %d) -> ", val.x, val.y);
// }

// void print_ilist(t_list *lst)
// {
// 	ft_lstiter(lst, &print_ipt2d);
// 	printf("END\n");
// }
// ///


int		select_closest_visited_neighbor(t_ipt2d curr, t_map *map,
	t_path **pathgrid)
{
	t_list	*neighbor_lst;
	t_ipt2d	neighbor;
	t_ipt2d	neighbor_min;
	int		min;

	min = -1;
	neighbor_lst = map->neighbors[curr.x][curr.y];
	while (neighbor_lst)
	{
		neighbor = *(t_ipt2d*)(neighbor_lst->content);
		if (*visited_at(pathgrid, neighbor)
				&& (min == -1 || *dist_at(pathgrid, neighbor) < min))
		{
			neighbor_min = neighbor;
			min = *dist_at(pathgrid, neighbor);
		}
		neighbor_lst = neighbor_lst->next;
	}
	if (min == -1)
		return (1);
	if (!path_copy(path_at(pathgrid, neighbor_min), path_at(pathgrid, curr))
			|| !add_back_ipt2d_once(steps_at(pathgrid, curr), curr))
		return (0);
	*dist_at(pathgrid, curr) = *dist_at(pathgrid, neighbor_min) + 1;
	return (1);
}


int		add_unvisited_neighbors(t_ipt2d curr, t_map *map, t_path **pathgrid,
	t_list **visit_fifo)
{
	t_list	*neighbor_lst;
	t_ipt2d neighbor;
	int min;

	min = -1;
	neighbor_lst = map->neighbors[curr.x][curr.y];
	while (neighbor_lst)
	{
		neighbor = *(t_ipt2d*)(neighbor_lst->content);
		if (!*visited_at(pathgrid, neighbor)
				&& !add_back_ipt2d_once(visit_fifo, neighbor))
			return (0);
		neighbor_lst = neighbor_lst->next;
	}
	return (1);
}

static int init_paths(t_map *map, t_sprite *sprite, t_path ***pathgrid_addr, t_list **visit_fifo_addr)
{
	t_ipt2d start;

	if (sprite->path)
		start = *ipt2d_at(sprite->path);
	else
		start = ipt2d((int)sprite->pos.x, (int)sprite->pos.y);
	if (!(*pathgrid_addr = (t_path**)ft_array(map->width, map->height, sizeof(t_path)))
			|| !add_back_ipt2d_once(visit_fifo_addr, start)
			|| !add_back_ipt2d_once(steps_at(*pathgrid_addr, start), start))
		return (-1);
	*visited_at(*pathgrid_addr, start) = 1;
	return (1);
}

static int	explore_paths(t_map *map, t_path **pathgrid, t_list **visit_fifo_addr,
	t_ipt2d goal)
{
	t_ipt2d	curr;

	while (*visit_fifo_addr)
	{
		pop_first(visit_fifo_addr, &curr);
		if (!select_closest_visited_neighbor(curr, map, pathgrid)
				|| !add_unvisited_neighbors(curr, map, pathgrid, visit_fifo_addr))
			return (-1);
		*visited_at(pathgrid, curr) = 1;
		if (curr.x == goal.x && curr.y == goal.y)
			break ;
	}
	return (1);
}

static int copy_shortest_path(t_sprite *sprite, t_path **pathgrid, t_ipt2d goal)
{
	t_list *copy;

	if (!*steps_at(pathgrid, goal))
		ft_lstclear(&sprite->path, free);
	else
	{
		if (!ft_lstcpy((*steps_at(pathgrid, goal))->next, &copy, sizeof(t_ipt2d)))
			return (-1);
		if (sprite->path)
		{
			ft_lstclear(&sprite->path->next, free);
			sprite->path->next = copy;
		}
		else
			sprite->path = copy;
	}
	return (1);
}

int		update_shortest_path(t_map *map, t_sprite *sprite, t_ipt2d goal)
{
	t_list	*visit_fifo;
	t_path	**pathgrid;

	if (sprite->path && ipt2d_equal(*ipt2d_at(sprite->path), goal))
		return (1);
	visit_fifo = NULL;
	if (init_paths(map, sprite, &pathgrid, &visit_fifo) == -1
			|| explore_paths(map, pathgrid, &visit_fifo, goal) == -1
			|| copy_shortest_path(sprite, pathgrid, goal) == -1)
	{
		// printf("ERROR\n");
		return (free_all_error(map, pathgrid, &visit_fifo));
	}
	clear_path_grid(map, pathgrid);
	ft_lstclear(&visit_fifo, free);
	// printf("New path : ");
	// print_ilist(sprite->path);
	return (1);
}
