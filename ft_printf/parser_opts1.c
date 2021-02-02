/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_opts1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:10:01 by lzins             #+#    #+#             */
/*   Updated: 2020/12/08 14:10:03 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_atoi_n(char const *str, size_t len)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	while (i < len && ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

int				get_flags(char const *format, t_options *opts)
{
	size_t	len;

	len = 0;
	while (ft_strchr("0-#", format[len]))
	{
		if (format[len] == '0')
			opts->flags |= FLAG_ZERO;
		else if (format[len] == '-')
			opts->flags |= FLAG_MINUS;
		else
			opts->flags |= FLAG_SHARP;
		len++;
	}
	return (len);
}

/*
** In case of * or '*xxx$', return len after the *
*/

static int		get_argno_star(char const *format, int *opts_param)
{
	size_t	len;

	len = 0;
	while (ft_isdigit(format[len]))
		len++;
	if (len == 0 || format[len] != '$')
	{
		*opts_param = -1;
		return (0);
	}
	else
	{
		*opts_param = ft_atoi_n(format, len);
		len++;
	}
	return (len);
}

int				get_field_len(char const *format, t_options *opts)
{
	size_t	len;

	len = 0;
	if (format[0] == '*')
	{
		opts->field_len = -1;
		return (1 + get_argno_star(format + 1, &(opts->field_len_arg)));
	}
	while (ft_isdigit(format[len]))
		len++;
	if (len > 0)
		opts->field_len = ft_atoi_n(format, len);
	return (len);
}

int				get_precision(char const *format, t_options *opts)
{
	size_t	len;

	len = 0;
	if (format[0] == '.')
	{
		opts->precision = 0;
		opts->precision_given = 1;
		if (format[1] == '*')
		{
			opts->precision = -1;
			return (2 + get_argno_star(format + 2, &(opts->precision_arg)));
		}
		len = 1;
		while (ft_isdigit(format[len]))
			len++;
		if (len > 1)
			opts->precision = ft_atoi_n(format + 1, len - 1);
	}
	else
	{
		opts->precision = 1;
		opts->precision_given = 0;
	}
	return (len);
}
