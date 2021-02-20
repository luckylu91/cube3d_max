/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_parse_funs1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:53:27 by lzins             #+#    #+#             */
/*   Updated: 2021/02/16 15:53:39 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "params_parse_utils.h"
#include "params_parse_funs.h"

int	parse_r(t_pack *p, char *line)
{
	return (parse_resolution(line, &p->width, &p->height));
}

int	parse_no(t_pack *p, char *line)
{
	return (parse_image_path(line, p, &p->cube_faces[NORTH]));
}

int	parse_so(t_pack *p, char *line)
{
	return (parse_image_path(line, p, &p->cube_faces[SOUTH]));
}

int	parse_ea(t_pack *p, char *line)
{
	return (parse_image_path(line, p, &p->cube_faces[EAST]));
}

int	parse_we(t_pack *p, char *line)
{
	return (parse_image_path(line, p, &p->cube_faces[WEST]));
}
