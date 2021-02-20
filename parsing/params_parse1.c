/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_parse1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:17:02 by lzins             #+#    #+#             */
/*   Updated: 2021/02/16 17:55:02 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "params_parse_funs.h"

void			free_parsed_line(void *pl_ptr)
{
	t_parsed_line *pl;

	pl = (t_parsed_line*)pl_ptr;
	free(pl->line);
	free(pl);
}

void			free_parse_option(void *po_ptr)
{
	t_parse_option *po;

	po = (t_parse_option*)po_ptr;
	free(po->prefix);
	ft_lstclear(&po->parsed_lines, &free_parsed_line);
	free(po);
}

int				addback_parse_option(t_list **alst, char *prefix,
		int mandatory, t_parse_fun parser)
{
	t_parse_option	*new_po;
	t_list			*new_elem;

	if (!(new_po = ft_calloc(1, sizeof(t_parse_option))))
		return (-1);
	if ((prefix && !(new_po->prefix = ft_strdup(prefix)))
			|| !(new_elem = ft_lstnew(new_po)))
	{
		free_parse_option(new_po);
		return (-1);
	}
	new_po->mandatory = mandatory;
	new_po->parser = parser;
	ft_lstadd_back(alst, new_elem);
	return (1);
}

int				addback_parsed_line(t_list **alst, int valid, char *line)
{
	t_parsed_line	*new_pl;
	t_list			*new_elem;

	if (!(new_pl = ft_calloc(1, sizeof(t_parsed_line))))
		return (-1);
	new_pl->line = ft_strdup(line);
	new_elem = ft_lstnew(new_pl);
	if (!new_pl->line || !new_elem)
	{
		free_parsed_line(new_pl);
		return (-1);
	}
	new_pl->valid = valid;
	ft_lstadd_back(alst, new_elem);
	return (1);
}
