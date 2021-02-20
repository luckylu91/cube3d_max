/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pack_init2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:01:52 by lzins             #+#    #+#             */
/*   Updated: 2021/02/16 15:43:21 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int		compute_minidims(t_pack *p)
{
	if (p->map.width > p->map.height)
	{
		p->mini.width = MINI_SIZE * p->width;
		p->mini.block_size = p->mini.width / p->map.width;
		p->mini.height = p->map.height * p->mini.block_size;
	}
	else
	{
		p->mini.height = MINI_SIZE * p->height;
		p->mini.block_size = p->mini.height / p->map.height;
		p->mini.width = p->map.width * p->mini.block_size;
	}
	p->mini.ox = MINI_OX * p->width;
	p->mini.oy = MINI_OY * p->height;
	p->mini.border_thickness = MINI_THICKNESS * p->mini.block_size;
	return (1);
}

static void		pack_init_constants(t_pack *p)
{
	reset_clock(p);
	p->time_total = 0.;
	p->time_loop = 0.;
	p->lives_max = 3;
	p->lives = 3;
	p->time_invul = 0.;
	p->touched_by_enemy = 0;
	p->mouse_on = 1;
	p->game_on = 1;
}

int				pack_init(t_pack *p, void *mlx, int scene_fd)
{
	t_list	*scene_lines;
	int		i;
	t_list	*map_begin;
	int		ret;

	ft_bzero(p, sizeof(t_pack));
	pack_init_constants(p);
	p->mlx = mlx;
	if (!(scene_lines = file_to_list(scene_fd))
			|| close(scene_fd) < 0)
		return (file_error_free_lines_pack(scene_lines, p));
	ret = 1;
	if (parse_all(scene_lines, p, &map_begin) == -1
			|| init_sprites(p) == -1
			|| new_map(map_begin, p) == -1
			|| compute_minidims(p) == -1
			|| !(p->dist_array =\
					(double**)ft_array(p->width, p->height, sizeof(double)))
			|| set_win_elements(p) == -1
			|| load_const_imgs(p) == -1)
		ret = free_pack(p);
	ft_lstclear(&scene_lines, &free);
	return (ret);
}
