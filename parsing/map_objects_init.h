/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_objects_init.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:43:05 by lzins             #+#    #+#             */
/*   Updated: 2021/02/11 17:55:19 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_OBJECTS_INIT_H
# define MAP_OBJECTS_INIT_H

# include "parse.h"

void		set_theta_pos(t_pack *p, int i, int j);
int			addback_sprite(t_list **asprites, t_sprite *new_val);
t_sprite	*add_sprite(t_pack *p, int i, int j, char type);
void		add_tpblock(t_map *map, t_ipt2d coord, int tp_count);

#endif
