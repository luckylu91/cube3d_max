/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_parse2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:20:29 by lzins             #+#    #+#             */
/*   Updated: 2021/02/17 09:19:23 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "params_parse_funs.h"

static char			*ith_prefix(int i)
{
	static char	*prefixes[11] = {"R ", "NO ", "SO ", "WE ", "EA ", "S ",
		"F ", "C ", "GAME ", "MOUSE ", NULL};

	return (prefixes[i]);
}

static t_parse_fun	ith_parser(int i)
{
	static t_parse_fun	parsers[11] = { &parse_r, &parse_no, &parse_so,
		&parse_we, &parse_ea, &parse_s, &parse_f, &parse_c, &parse_game,
		&parse_mouse, NULL};

	return (parsers[i]);
}

static int			ith_mandatory_val(int i)
{
	static int			mandatory_vals[11] = {
		1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0};

	return (mandatory_vals[i]);
}

t_list				*create_po_list(void)
{
	t_list				*po_lst;
	int					i;

	po_lst = NULL;
	i = -1;
	while (++i < 11)
	{
		if (addback_parse_option(&po_lst, ith_prefix(i),
				ith_mandatory_val(i), ith_parser(i)) == -1)
		{
			ft_lstclear(&po_lst, &free_parse_option);
			malloc_error();
			return (NULL);
		}
	}
	return (po_lst);
}

int					parse_line(t_list *po_lst, t_pack *p, char *line)
{
	t_list			*po_mov;
	t_parse_option	*po;
	int				ret_parser;

	po_mov = po_lst;
	while (po_mov)
	{
		po = (t_parse_option*)(po_mov->content);
		if (!po->prefix
				&& addback_parsed_line(&po->parsed_lines, -1, line) == -1)
			return (malloc_error());
		if (po->prefix && !ft_strncmp(po->prefix, line, ft_strlen(po->prefix)))
		{
			ret_parser = (*po->parser)(p, line);
			if (addback_parsed_line(&po->parsed_lines, ret_parser, line) == -1)
				return (malloc_error());
			return (1);
		}
		po_mov = po_mov->next;
	}
	return (-1);
}
