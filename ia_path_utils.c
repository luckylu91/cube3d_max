/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ia_path_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 16:00:30 by lzins             #+#    #+#             */
/*   Updated: 2021/02/18 16:01:11 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		*dist_at(t_path **pathgrid, t_ipt2d coord)
{
	return (&pathgrid[coord.x][coord.y].dist);
}

int		*visited_at(t_path **pathgrid, t_ipt2d coord)
{
	return (&pathgrid[coord.x][coord.y].visited);
}

t_list	**steps_at(t_path **pathgrid, t_ipt2d coord)
{
	return (&pathgrid[coord.x][coord.y].steps);
}

t_path	*path_at(t_path **pathgrid, t_ipt2d coord)
{
	return (&pathgrid[coord.x][coord.y]);
}
