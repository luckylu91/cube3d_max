/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:17:55 by lzins             #+#    #+#             */
/*   Updated: 2021/02/20 10:54:22 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "get_next_line.h"

// static int	illegal_map_line(char *line)
// {
// 	message_error("Map has empty/commented lines");
// 	ft_printf("Line : %s", line);
// 	return (-1);
// }

static int	line_status(char *line, int *map_begun)
{
	char	*line_trimmed;
	int		size_trimmed;
	char	first_char;
	int		ret;

	ret = 0;
	if (!(line_trimmed = ft_strtrim(line, " ")))
		return (-1);
	size_trimmed = ft_strlen(line_trimmed);
	first_char = line_trimmed[0];
	if (size_trimmed == 0 || first_char == '#')
	{
		if (*map_begun)
			ret = 2;
		else
			ret = 1;
	}
	else if (line_trimmed[0] && ft_all_in(line_trimmed, MAP_CHARS))
		*map_begun = 1;
	free(line_trimmed);
	return (ret);
}

int			addback_line(t_list **lst, char *line)
{
	t_list	*new_elem;

	if (!(new_elem = ft_lstnew(line)))
		return (-1);
	ft_lstadd_back(lst, new_elem);
	return (1);
}

void		lst_prune(t_list **alst, t_list *lst_end)
{
	t_list *lst;

	if (!lst_end)
		return ;
	while (*alst && *alst != lst_end)
		alst = &(*alst)->next;
	if (*alst == lst_end)
		ft_lstclear(alst, &free);
}

static int	filter_line(char *line, t_lst_parse_map *lines_parse)
{
	int		ret_emptyline;

	if ((ret_emptyline = line_status(line, &lines_parse->map_begun)) == -1)
		return (free_clear_and_error(&lines_parse->lst, line));
	if (ret_emptyline == 1)
		free(line);
	else if (addback_line(&lines_parse->lst, line) == -1)
		return (free_clear_and_error(&lines_parse->lst, line));
	else if (ret_emptyline == 2)
	{
		if (lines_parse->found_nonempty)
		{
			lines_parse->found_nonempty = 0;
			lines_parse->first_empty = ft_lstlast(lines_parse->lst);
		}
		else
		{
			lines_parse->found_nonempty = 1;
			lines_parse->first_empty = NULL;
		}
	}
	return (1);
}

t_list		*file_to_list(int fd)
{
	int				ret_gnl;
	char			*line;
	t_lst_parse_map	lines_parse;

	lines_parse.lst = NULL;
	lines_parse.map_begun = 0;
	lines_parse.found_nonempty = 1;
	lines_parse.first_empty = NULL;
	line = NULL;
	while ((ret_gnl = get_next_line(fd, &line)) != -1)
	{
		if (filter_line(line, &lines_parse) == -1)
			return (NULL);
		if (ret_gnl == 0)
		{
			lst_prune(&lines_parse.lst, lines_parse.first_empty);
			return (lines_parse.lst);
		}
	}
	free_clear_and_error(&lines_parse.lst, line);
	return (NULL);
}
