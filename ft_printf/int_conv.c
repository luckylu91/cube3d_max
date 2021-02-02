/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:11:40 by lzins             #+#    #+#             */
/*   Updated: 2020/12/08 14:11:42 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** For i or d conversion
*/

char		*d_conv(va_list va, t_options *opts)
{
	char			*res;
	char			*num_str;

	num_str = digits_s(va, "0123456789", opts);
	res = generic_conv(num_str, ft_strlen(num_str), opts);
	free(num_str);
	return (res);
}

char		*x_conv(va_list va, t_options *opts)
{
	char				*res;
	char				*num_str;
	char				*tmp;

	if (opts->conv_char == 'x')
		num_str = digits_u(va, "0123456789abcdef", opts);
	else
		num_str = digits_u(va, "0123456789ABCDEF", opts);
	if (opts->flags & FLAG_SHARP)
	{
		tmp = num_str;
		num_str = ft_strjoin("0?", num_str);
		num_str[1] = opts->conv_char;
		free(tmp);
	}
	res = generic_conv(num_str, ft_strlen(num_str), opts);
	free(num_str);
	return (res);
}

char		*u_conv(va_list va, t_options *opts)
{
	char				*res;
	char				*num_str;

	num_str = digits_u(va, "0123456789", opts);
	res = generic_conv(num_str, ft_strlen(num_str), opts);
	free(num_str);
	return (res);
}
