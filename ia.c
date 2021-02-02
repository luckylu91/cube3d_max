#include "cub3d.h"

//
void print_ipt2d2(void *content)
{
	t_ipt2d *apt = content;
	printf("(%d,%d) -> ", apt->x, apt->y);
}

void print_ilist(t_list *l)
{
	ft_lstiter(l, &print_ipt2d2);
	printf("END\n");
}
//

int		add_back_ipt2d_ifnotpresent(t_list **alst, t_ipt2d val)
{
	t_list *lst_match;
	t_list *new_elem;
	t_ipt2d *new_val;

	lst_match = ft_lstfind(*alst, &val, sizeof(t_ipt2d));
	if (lst_match)
		return (1);
	if (!(new_val = malloc(sizeof(t_ipt2d))))
		return (0);
	*new_val = val;
	if (!(new_elem = ft_lstnew(new_val)))
	{
		free(new_val);
		return (0);
	}
	ft_lstadd_back(alst, new_elem);
	return (1);
}

int		path_copy(t_path *src, t_path *res)
{
	// res->dist = src->dist;
	// res->visited = src->visited;
	if (!(res->steps = ft_lstcpy(src->steps, sizeof(t_ipt2d))))
	{
		// //
		// printf("copy failed of list:\n");
		// print_ilist(src->steps);
		// printf("------\n");
		// //
		return (0);
	}
	return (1);
}

void	clear_path(t_path *path)
{
	ft_lstclear(&path->steps, free);
	path->steps = NULL;
}

void	clear_path_grid(t_map *map, t_path **pathgrid)
{
	int x;
	int y;

	x = -1;
	while (++x < map->width)
	{
		y = -1;
		while (++y < map->height)
			clear_path(&pathgrid[x][y]);
		free(pathgrid[x]);
	}
	free(pathgrid);
}

int		select_shortest_visited_neighbor(t_ipt2d curr, t_map *map, t_path **pathgrid)
{
	int axis;
	int offset;
	t_ipt2d neighbor;
	t_ipt2d neighbor_min;
	int min;

	min = -1;
	axis = -1;
	while (++axis < 2)
	{
		offset = -1;
		while (offset < 2)
		{
			neighbor.x = curr.x + (axis == 0 ? offset : 0);
			neighbor.y = curr.y + (axis == 1 ? offset : 0);
			// //
			// if (in_bounds2D(neighbor.x, neighbor.y, map))
			// {
			// 	printf("curr (%d,%d) | neighbor (%d,%d)\n", curr.x, curr.y, neighbor.x, neighbor.y);
			// 	printf("visited = %d\n", pathgrid[neighbor.x][neighbor.y].visited);
			// 	print_ilist(pathgrid[neighbor.x][neighbor.y].steps);
			// }
			// //
			if (in_bounds2D(neighbor.x, neighbor.y, map)
					&& map->grid[neighbor.x][neighbor.y] != WALL
					&& pathgrid[neighbor.x][neighbor.y].visited
					&& (min == -1 || pathgrid[neighbor.x][neighbor.y].dist < min))
			{
				neighbor_min = neighbor;
				min = pathgrid[neighbor.x][neighbor.y].dist;
			}
			offset += 2;
		}
	}
	if (min == -1)
		return (1);
	if (!path_copy(&pathgrid[neighbor_min.x][neighbor_min.y], &pathgrid[curr.x][curr.y])
		|| !add_back_ipt2d_ifnotpresent(&pathgrid[curr.x][curr.y].steps, curr))
	{
		// //
		// printf("Quitting select_shortest_...\n");
		// printf("\n");
		clear_path(&pathgrid[neighbor_min.x][neighbor_min.y]); // unnecessary ?
		return (0);
	}
	pathgrid[curr.x][curr.y].dist = pathgrid[neighbor_min.x][neighbor_min.y].dist + 1;
	return (1);
}

int		add_unvisited_neighbors(t_ipt2d curr, t_map *map, t_path **pathgrid, t_list **visit_fifo)
{
	int axis;
	int offset;
	t_ipt2d neighbor;
	
	axis = -1;
	while (++axis < 2)
	{
		offset = -1;
		while (offset < 2)
		{
			neighbor.x = curr.x + (axis == 0 ? offset : 0);
			neighbor.y = curr.y + (axis == 1 ? offset : 0);
			// //
			// if (in_bounds2D(neighbor.x, neighbor.y, map))
			// {
			// 	printf("neighbor (%d,%d)\n", neighbor.x, neighbor.y);
			// 	printf("visited = %d\n", pathgrid[neighbor.x][neighbor.y].visited);
			// 	print_ilist(pathgrid[neighbor.x][neighbor.y].steps);
			// }
			// //
			if (in_bounds2D(neighbor.x, neighbor.y, map)
					&& map->grid[neighbor.x][neighbor.y] != WALL
					&& !pathgrid[neighbor.x][neighbor.y].visited)
			{
				// //
				// printf("valid neighbor (%d,%d)\n", neighbor.x, neighbor.y);
				// //
				if (!add_back_ipt2d_ifnotpresent(visit_fifo, neighbor))
					return (0);
			}
			offset += 2;
		}
	}
	// //
	// printf("visit list :\n");
	// print_ilist(*visit_fifo);
	// printf("\tend visit list\n");
	// //
	return (1);
}

int		free_all(t_map *map, t_path **pathgrid, t_list **visit_fifo)
{
	clear_path_grid(map, pathgrid);
	ft_lstclear(visit_fifo, free);
	return (0);
}

/*
** adding nodes in a way that all strictly closer nodes are already added
** 
*/
// TODO TODO TODOOOOOOOOOO dont include start...
int		update_shortest_path(t_map *map, t_sprite *sprite, t_ipt2d goal)
{
	t_list *visit_fifo; // ipt2d
	t_ipt2d curr;
	t_path **pathgrid;
	t_list *shortest_path;
	t_ipt2d start;

	if (sprite->path)
		start = *ipt2d_at(sprite->path);
	else
		start = ipt2d((int)sprite->pos.x, (int)sprite->pos.y);
	visit_fifo = NULL;
	if (!(pathgrid = (t_path**)ft_array(map->width, map->height, sizeof(t_path)))
			|| !add_back_ipt2d_ifnotpresent(&visit_fifo, start)
			|| !add_back_ipt2d_ifnotpresent(&pathgrid[start.x][start.y].steps, start))
		return (free_all(map, pathgrid, &visit_fifo));
	pathgrid[start.x][start.y].visited = 1;
	// //
	// printf("visited = %d\n", pathgrid[start.x][start.y].visited);
	// print_ilist(pathgrid[start.x][start.y].steps);
	// //
	while (visit_fifo)
	{
		pop_first(&visit_fifo, &curr);
		// //
		// printf("curr (%d,%d)\n", curr.x, curr.y);
		if (!select_shortest_visited_neighbor(curr, map, pathgrid)
			|| !add_unvisited_neighbors(curr, map, pathgrid, &visit_fifo))
				return (free_all(map, pathgrid, &visit_fifo));
		// //
		// printf("step visit list :\n");
		// print_ilist(visit_fifo);
		// printf("\tend step visit list\n");
		// //
		pathgrid[curr.x][curr.y].visited = 1;
		if (curr.x == goal.x && curr.y == goal.y)
			break;
	}
	// //
	// printf("Optimal path :\n");
	// print_ilist(pathgrid[goal.x][goal.y].steps);
	// //
	if (!pathgrid[goal.x][goal.y].steps)
		ft_lstclear(&sprite->path, free);
	else
	{
		if (sprite->path)
		{
			ft_lstclear(&sprite->path->next, free);
			sprite->path->next = ft_lstcpy(pathgrid[goal.x][goal.y].steps->next, sizeof(t_ipt2d));
		}
		else
			sprite->path = ft_lstcpy(pathgrid[goal.x][goal.y].steps->next, sizeof(t_ipt2d));
	}
	free_all(map, pathgrid, &visit_fifo);
	return (1);
}