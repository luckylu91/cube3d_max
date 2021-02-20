/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_render_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:32:24 by lzins             #+#    #+#             */
/*   Updated: 2021/02/18 15:33:01 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	collect_pea(t_pack *p)
{
	int		x;
	int		y;
	t_list	*lst_elem;

	x = (int)p->pos.x;
	y = (int)p->pos.y;
	if (p->map.pea_sprites_grid[x][y])
	{
		lst_elem = ft_lstremove(&p->sprites, p->map.pea_sprites_grid[x][y],
			sizeof(t_sprite));
		free_sprite(p->map.pea_sprites_grid[x][y]);
		free(lst_elem);
		p->map.pea_sprites_grid[x][y] = NULL;
		p->map.peas_count--;
	}
}

void	assess_victory(t_pack *p)
{
	if (p->map.peas_count == 0)
	{
		p->you_won = 1;
		end_game(p);
	}
}

void	assess_life(t_pack *p)
{
	int touched;
	int i;

	touched = p->touched_by_enemy;
	p->touched_by_enemy = 0;
	if (p->time_invul > 0. || !touched)
		return ;
	p->lives--;
	p->time_invul = TIME_INVUL;
	if (p->lives <= 0)
	{
		p->you_won = 0;
		end_game(p);
	}
}

void	draw(t_pack *p)
{
	render(p);
	render_minimap(p);
	swap(p);
}
