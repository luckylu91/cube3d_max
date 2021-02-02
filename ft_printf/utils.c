/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:10:18 by lzins             #+#    #+#             */
/*   Updated: 2020/12/08 14:16:00 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int					max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

long long			raw_val_s(va_list va, t_options *opts)
{
	if (opts->modif == MODIF_HH)
		return (va_arg(va, int) & UCHAR_MAX);
	else if (opts->modif == MODIF_H)
		return (va_arg(va, int) & USHRT_MAX);
	else if (opts->modif == MODIF_L)
		return (va_arg(va, long));
	else if (opts->modif == MODIF_LL)
		return (va_arg(va, long long int));
	else
		return (va_arg(va, int));
}

unsigned long long	raw_val_u(va_list va, t_options *opts)
{
	if (opts->modif == MODIF_HH)
		return (va_arg(va, unsigned int) & UCHAR_MAX);
	else if (opts->modif == MODIF_H)
		return (va_arg(va, unsigned int) & USHRT_MAX);
	else if (opts->modif == MODIF_L)
		return (va_arg(va, unsigned long));
	else if (opts->modif == MODIF_LL)
		return (va_arg(va, unsigned long long));
	else
		return (va_arg(va, unsigned int));
}
