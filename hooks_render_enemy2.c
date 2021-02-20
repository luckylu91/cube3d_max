/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_render_enemy2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:24:29 by lzins             #+#    #+#             */
/*   Updated: 2021/02/20 10:52:59 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	first_path_update(t_pack *p, t_sprite *enemy)
{
	t_list	*dead_ghost;

	if (update_shortest_path(&p->map, enemy, ipt2d(p->pos.x, p->pos.y)) == -1)
		return (-1);
	if (!enemy->path)
	{
		printf("A lonely ghost commited suicide... again.\n");
		dead_ghost = ft_lstremove(&p->enemies, enemy, sizeof(t_sprite));
		ft_lstremove(&p->enemies, enemy, sizeof(t_sprite));
		ft_lstdelone(dead_ghost, &free_sprite);
		dead_ghost = ft_lstremove(&p->sprites, enemy, sizeof(t_sprite));
		ft_lstremove(&p->sprites, enemy, sizeof(t_sprite));
		free(dead_ghost);
		return (0);
	}
	return (1);
}

int	update_path(t_pack *p, t_sprite *enemy)
{
	t_ipt2d	*dest;

	dest = path_destination(enemy->path);
	if (dest->x != (int)p->pos.x || dest->y != (int)p->pos.y)
	{
		// printf("Player has moved on (%d,%d)\n", (int)p->pos.x, (int)p->pos.y);
		if (update_shortest_path(
				&p->map, enemy,
				ipt2d(p->pos.x, p->pos.y)) == -1)
			return (-1);
	}
	return (1);
}

int	update_path_if_needed(t_pack *p, t_sprite *enemy)
{
	t_list	*path_patch;

	if ((int)p->pos.x == (int)enemy->pos.x
			&& (int)p->pos.y == (int)enemy->pos.y)
		return (0);
	if (!enemy->path)
		return (first_path_update(p, enemy));
	else
		return (update_path(p, enemy));
}
