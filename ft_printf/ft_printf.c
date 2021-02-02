/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:08:39 by lzins             #+#    #+#             */
/*   Updated: 2021/01/11 18:43:15 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_arg(va_list va, int argno)
{
	static va_list	va_beg;
	static int		first_call = 1;
	va_list			va_mov;
	int				i;
	int				val;

	val = 0;
	if (first_call)
	{
		first_call = 0;
		va_copy(va_beg, va);
	}
	if (argno < 0)
		return (va_arg(va, int));
	else
	{
		i = -1;
		while (i < argno)
		{
			va_copy(va_mov, va_beg);
			val = va_arg(va_mov, int);
			i++;
		}
		return (val);
	}
}

static void	complete_match_options(va_list va, t_options *opts)
{
	if (opts->field_len == -1)
		opts->field_len = get_arg(va, opts->field_len_arg);
	if (opts->field_len < 0)
	{
		opts->flags |= FLAG_MINUS;
		opts->field_len *= -1;
	}
	if (opts->precision == -1)
		opts->precision = get_arg(va, opts->precision_arg);
	if (opts->precision < 0 && ft_strchr("dixXup", opts->conv_char))
		opts->precision_given = 0;
}

static char	*converted_str(va_list va, t_options *opts)
{
	char	conv_char;

	conv_char = opts->conv_char;
	if (conv_char == 'd' || conv_char == 'i')
		return (d_conv(va, opts));
	if (conv_char == 'x' || conv_char == 'X')
		return (x_conv(va, opts));
	if (conv_char == 'u')
		return (u_conv(va, opts));
	if (conv_char == 'c')
		return (c_conv(va, opts));
	if (conv_char == 's')
		return (s_conv(va, opts));
	if (conv_char == '%')
		return (pct_conv(opts));
	return (ft_strdup(""));
}

int			ft_print_matches(char const *format, t_list *matches,
							va_list va, size_t *i)
{
	t_match			*match;
	size_t			len;
	char			*conv_str;

	len = 0;
	while (matches)
	{
		match = matches->content;
		if (match->i_start > *i)
		{
			write(FD, format + *i, match->i_start - *i);
			len += match->i_start - *i;
		}
		complete_match_options(va, &match->opts);
		if (!(conv_str = converted_str(va, &match->opts)))
			return (-1);
		write(FD, conv_str, match->opts.result_len);
		*i = match->i_start + match->len;
		len += match->opts.result_len;
		free(conv_str);
		matches = matches->next;
	}
	return (len);
}

int			ft_printf(char const *format, ...)
{
	va_list			va;
	t_list			*matches;
	size_t			i;
	size_t			len;

	if (parser_all(format, "dixXcsup%*", &matches) == -1)
		return (-1);
	va_start(va, format);
	i = 0;
	len = ft_print_matches(format, matches, va, &i) + ft_strlen(format + i);
	write(FD, format + i, ft_strlen(format + i));
	ft_lstclear(&matches, &free);
	va_end(va);
	return (len);
}
