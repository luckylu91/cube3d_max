/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 00:53:12 by lzins             #+#    #+#             */
/*   Updated: 2021/01/12 15:51:38 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strccpy(char *dst, char *src, char c, size_t n)
{
	size_t i;

	i = 0;
	while (i < n && src[i] && src[i] != c)
	{
		dst[i] = src[i];
		i++;
	}
	return (i);
}

int		free_safe(char *line)
{
	if (line)
		free(line);
	return (-1);
}
