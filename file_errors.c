/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 12:55:04 by lzins             #+#    #+#             */
/*   Updated: 2021/02/20 10:54:46 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		file_error(char *fname)
{
	ft_printf("Error\nWhile opening/reading/closing %s\n", fname);
	perror(NULL);
	return (-1);
}

int		file_error_free_lines_pack(t_list *scene_lines, t_pack *p)
{
	ft_lstclear(&scene_lines, &free);
	free_pack(p);
	perror(NULL);
	return (-1);
}

int	free_clear_and_error(t_list **alst, char *line)
{
	message_error("During scene file reading");
	free(line);
	ft_lstclear(alst, &free);
	return (-1);
}
