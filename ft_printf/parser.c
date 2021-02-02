/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:12:01 by lzins             #+#    #+#             */
/*   Updated: 2021/01/11 17:35:47 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	parser_one_main(char const *format, char const *supported,
								t_match *match)
{
	size_t			len;

	len = 1;
	len += get_flags(format + len, &match->opts);
	len += get_field_len(format + len, &match->opts);
	len += get_precision(format + len, &match->opts);
	len += get_modif(format + len, &match->opts);
	if (!format[len] || !ft_strchr(supported, format[len]))
	{
		match->opts.conv_char = '*';
		len = 1;
	}
	else
		match->opts.conv_char = format[len++];
	match->len = len;
}

t_match		*parser_one(char const *format, char const *supported)
{
	t_match	*match;

	if (!(match = ft_calloc(1, sizeof(t_match))))
		return (NULL);
	parser_one_main(format, supported, match);
	if (match->opts.conv_char == 'p')
	{
		match->opts.conv_char = 'x';
		match->opts.modif = MODIF_L;
		match->opts.flags |= FLAG_SHARP;
	}
	return (match);
}

int			parser_all(char const *format, char const *supported,
						t_list **matches)
{
	t_match			*match;
	size_t			i;
	t_list			*match_elem;

	*matches = NULL;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (!(match = parser_one(format + i, supported))
					|| !(match_elem = ft_lstnew(match)))
			{
				ft_lstclear(matches, &free);
				return (-1);
			}
			match->i_start = i;
			ft_lstadd_back(matches, match_elem);
			i += match->len;
		}
		else
			i++;
	}
	return (0);
}
