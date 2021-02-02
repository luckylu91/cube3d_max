/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_opts2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:09:47 by lzins             #+#    #+#             */
/*   Updated: 2020/12/08 14:09:49 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_modif(char const *format, t_options *opts)
{
	if (format[0] == 'h')
	{
		if (format[1] == 'h')
		{
			opts->modif = MODIF_HH;
			return (2);
		}
		opts->modif = MODIF_H;
		return (1);
	}
	else if (format[0] == 'l')
	{
		if (format[1] == 'l')
		{
			opts->modif = MODIF_LL;
			return (2);
		}
		opts->modif = MODIF_L;
		return (1);
	}
	return (0);
}
