/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_conv_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:08:58 by lzins             #+#    #+#             */
/*   Updated: 2020/12/08 14:09:17 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t			digits_len(unsigned long long n, size_t base_len)
{
	int	n_len;

	n_len = 0;
	while (n)
	{
		n /= base_len;
		n_len++;
	}
	return (n_len);
}

void			swrite_digits_u(unsigned long long n, char *base,
									int n_len, char *s)
{
	size_t	base_len;

	base_len = ft_strlen(base);
	s[n_len--] = '\0';
	while (n_len > -1)
	{
		s[n_len--] = base[(n % base_len)];
		n /= base_len;
	}
}

char			*digits_s(va_list va, char *base, t_options *opts)
{
	int			n_len;
	char		*res;
	long long	n;

	n = raw_val_s(va, opts);
	n_len = digits_len(n < 0 ? -n : n, ft_strlen(base));
	if (opts->precision_given)
		n_len = max(n_len, opts->precision);
	else
		n_len = max(n_len, 1);
	if (n < 0 || opts->flags & FLAG_PLUS)
		n_len++;
	if (!(opts->precision_given) && (opts->flags & FLAG_ZERO)
			&& !(opts->flags & FLAG_MINUS))
		n_len = max(n_len, opts->field_len);
	if (!(res = malloc(n_len + 1)))
		return (NULL);
	swrite_digits_u(n < 0 ? -n : n, base, n_len, res);
	if (n < 0)
		res[0] = '-';
	else if (opts->flags & FLAG_PLUS)
		res[0] = '+';
	return (res);
}

char			*digits_u(va_list va, char *base, t_options *opts)
{
	int					n_len;
	char				*res;
	unsigned long long	n;

	n = raw_val_u(va, opts);
	n_len = digits_len(n, ft_strlen(base));
	if (opts->precision_given)
		n_len = max(n_len, opts->precision);
	else
		n_len = max(n_len, 1);
	if (!opts->precision_given && (opts->flags & FLAG_ZERO)
			&& !(opts->flags & FLAG_MINUS))
		n_len = max(n_len, opts->field_len);
	if (!(res = malloc(n_len + 1)))
		return (NULL);
	swrite_digits_u(n, base, n_len, res);
	return (res);
}
