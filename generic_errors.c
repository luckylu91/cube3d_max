/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <lzins@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 16:02:25 by lzins             #+#    #+#             */
/*   Updated: 2021/02/20 10:56:26 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	malloc_error(void)
{
	ft_printf("Malloc error\n");
	return (-1);
}

int	parse_error(void)
{
	ft_printf("Error while parsing\n");
	return (-1);
}

int	message_error(char *message)
{
	ft_printf("Error\n");
	if (message)
		ft_printf("%s\n", message);
	return (-1);
}

int	file_not_found_error(char *fname)
{
	ft_printf("Error\n");
	ft_printf("File not found : %s\n", fname);
	return (-1);
}
