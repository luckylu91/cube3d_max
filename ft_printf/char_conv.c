/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_conv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 19:24:10 by lzins             #+#    #+#             */
/*   Updated: 2020/12/07 19:24:15 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*c_conv(va_list va, t_options *opts)
{
	char c;

	c = va_arg(va, int);
	return (generic_conv(&c, 1, opts));
}

char	*s_conv(va_list va, t_options *opts)
{
	char	*s;
	int		len;

	s = va_arg(va, char*);
	if (!s)
		s = "(null)";
	if (!opts->precision_given || opts->precision < 0)
		len = ft_strlen(s);
	else
		len = min(ft_strnlen(s, opts->precision), opts->precision);
	return (generic_conv(s, len, opts));
}

char	*pct_conv(t_options *opts)
{
	return (generic_conv("%", 1, opts));
}
