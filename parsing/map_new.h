/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_new.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:03:35 by lzins             #+#    #+#             */
/*   Updated: 2021/02/11 16:42:07 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_NEW_H
# define MAP_NEW_H

# include "parse.h"

void	mapline_dimentions(char *line, int *i1, int *i2);
void	map_dimentions(t_list *map_lst, int *i1, int *i2);
void	fill_map_grid(t_list *map_lst, t_map *map, int i1, int i2);

#endif
