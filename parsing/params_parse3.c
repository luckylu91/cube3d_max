/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_parse3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 17:22:17 by lzins             #+#    #+#             */
/*   Updated: 2021/02/16 17:23:07 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "params_parse_funs.h"

int			missing_mandatory_error(t_parse_option *po)
{
	ft_printf("Error\n");
	ft_printf("Missing mandatory parameter %s\n", po->prefix);
	return (-1);
}

int			too_many_instances_error(t_parse_option *po)
{
	t_list			*pl_lst;
	t_parsed_line	*pl;

	ft_printf("Error\n");
	ft_printf("Several occurences of parameter %s:\n", po->prefix);
	pl_lst = po->parsed_lines;
	while (pl_lst)
	{
		pl = (t_parsed_line*)(pl_lst->content);
		ft_printf("Line : %s\n", pl->line);
		pl_lst = pl_lst->next;
	}
	return (-1);
}

static int	unknown_parameters(t_parse_option *po)
{
	t_list			*pl_lst;
	t_parsed_line	*pl;

	ft_printf("Error\n");
	ft_printf("Unknown parameter(s) for the following line(s) :\n");
	pl_lst = po->parsed_lines;
	while (pl_lst)
	{
		pl = (t_parsed_line*)(pl_lst->content);
		ft_printf("Line : %s\n", pl->line);
		pl_lst = pl_lst->next;
	}
	return (-1);
}

static int	recap_po_one(t_parse_option *po, int n_lines)
{
	t_parsed_line	*pl;
	int				ret;

	ret = 1;
	if (po->mandatory && n_lines == 0)
		ret = missing_mandatory_error(po);
	else if (n_lines > 1)
		ret = too_many_instances_error(po);
	if (n_lines == 1)
	{
		pl = (t_parsed_line*)(po->parsed_lines->content);
		if (pl->valid == -1)
			ret = -1;
	}
	return (ret);
}

int			recap_po_errors(t_list *po_lst)
{
	t_list			*po_mov;
	int				ret;
	t_parse_option	*po;
	int				n_lines;

	ret = 1;
	po_mov = po_lst;
	while (po_mov)
	{
		po = (t_parse_option*)(po_mov->content);
		n_lines = ft_lstsize(po->parsed_lines);
		if (!po->prefix && n_lines > 0)
			ret = unknown_parameters(po);
		else if (recap_po_one(po, n_lines) == -1)
			ret = -1;
		po_mov = po_mov->next;
	}
	return (ret);
}
