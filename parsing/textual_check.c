/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textual_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:59:35 by lzins             #+#    #+#             */
/*   Updated: 2021/02/20 09:28:36 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int			is_map_line(char *line)
{
	char	*trimmed;
	int		ret;

	ret = 0;
	if (!(trimmed = ft_strtrim(line, " ")))
		ret = message_error("malloc error during string trim");
	if (trimmed[0] && ft_all_in(trimmed, MAP_CHARS))
		ret = 1;
	free(trimmed);
	return (ret);
}

static int	mapline_check(char *line)
{
	int begining;
	int i;
	int player_start_found;

	player_start_found = 0;
	begining = 1;
	i = -1;
	while (line[++i])
	{
		if (!ft_strchr(MAP_CHARS, line[i]))
		{
			ft_printf("Error\n");
			ft_printf("Forbidden character in map line \"%s\" -> %c\n",
				line, line[i]);
			return (-1);
		}
	}
	return (1);
}

int			textual_check(t_list *lst, t_list **map_begin)
{
	int ret;

	while (lst)
	{
		if ((ret = is_map_line(lst->content)) == -1)
			return (-1);
		if (ret == 1)
		{
			*map_begin = lst;
			break ;
		}
		lst = lst->next;
	}
	if (!lst)
		return (message_error("no map in scene"));
	while (lst)
	{
		if (mapline_check(lst->content) == -1)
			return (-1);
		lst = lst->next;
	}
	return (1);
}
