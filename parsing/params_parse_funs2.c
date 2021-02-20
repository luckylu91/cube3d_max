/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_parse_funs2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:53:56 by lzins             #+#    #+#             */
/*   Updated: 2021/02/16 15:54:18 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "params_parse_utils.h"
#include "params_parse_funs.h"

int	parse_s(t_pack *p, char *line)
{
	char	*fname;
	int		ret;

	ret = 1;
	if (parse_text_param(line, &fname) == -1)
		ret = -1;
	else
		p->sprite_fname = fname;
	return (ret);
}

int	parse_f(t_pack *p, char *line)
{
	return (parse_fc(p, line, &p->cube_faces[FLOOR]));
}

int	parse_c(t_pack *p, char *line)
{
	return (parse_fc(p, line, &p->cube_faces[CEIL]));
}

int	parse_game(t_pack *p, char *line)
{
	char	*value_str;
	int		i;
	int		ret;

	value_str = NULL;
	if (parse_text_param(line, &value_str) == -1)
	{
		free(value_str);
		return (-1);
	}
	i = -1;
	while (value_str[++i])
		value_str[i] = ft_tolower(value_str[i]);
	if (!ft_strcmp(value_str, "on"))
		p->game_on = 1;
	else
		p->game_on = 0;
	free(value_str);
	return (1);
}

int	parse_mouse(t_pack *p, char *line)
{
	char	*value_str;
	int		i;

	value_str = NULL;
	if (parse_text_param(line, &value_str) == -1)
	{
		free(value_str);
		return (-1);
	}
	i = -1;
	while (value_str[++i])
		value_str[i] = ft_tolower(value_str[i]);
	if (!ft_strcmp(value_str, "on"))
		p->mouse_on = 1;
	else
		p->mouse_on = 0;
	free(value_str);
	return (1);
}
