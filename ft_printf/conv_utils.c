/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 19:25:04 by lzins             #+#    #+#             */
/*   Updated: 2020/12/08 14:05:44 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_strnlen(char *s, int len)
{
	int i;

	i = 0;
	while (s[i] && i < len)
		i++;
	return (i);
}

char		*generic_conv(char *s, int len, t_options *opts)
{
	char			*res;
	int				res_len;

	res_len = max(len, opts->field_len);
	if (!(res = malloc(res_len + 1)))
		return (NULL);
	res[res_len] = '\0';
	if (ft_strchr("%sc", opts->conv_char)
				&& (opts->flags & FLAG_ZERO)
				&& !(opts->flags & FLAG_MINUS))
		ft_memset(res, '0', res_len);
	else
		ft_memset(res, ' ', res_len);
	if (opts->flags & FLAG_MINUS)
		ft_memcpy(res, s, len);
	else
		ft_memcpy(res + res_len - len, s, len);
	opts->result_len = res_len;
	return (res);
}
