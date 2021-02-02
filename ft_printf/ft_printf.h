/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:10:44 by lzins             #+#    #+#             */
/*   Updated: 2021/01/11 18:42:48 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "libft.h"
# include <stdio.h>

# define FD STDERR_FILENO
# define FLAG_ZERO 1
# define FLAG_MINUS 2
# define FLAG_PLUS 4
# define FLAG_SHARP 8
# define MODIF_HH 1
# define MODIF_H 2
# define MODIF_L 3
# define MODIF_LL 4

/*
** If field_len or precision are -1 : field_len_arg and precision_arg are
** either -1 if 'look at next argument' or arg's index
*/

typedef struct		s_options
{
	int				flags;
	int				field_len;
	int				field_len_arg;
	int				precision;
	int				precision_given;
	int				precision_arg;
	int				modif;
	int				result_len;
	int				char_is_null;
	char			conv_char;
}					t_options;

/*
** conv_char can be any supported char,
** or '*' if format was invalid
*/

typedef struct		s_match
{
	size_t			i_start;
	int				len;
	t_options		opts;
}					t_match;

int					ft_printf(char const *format, ...);
char				*c_conv(va_list va, t_options *opts);
char				*s_conv(va_list va, t_options *opts);
char				*pct_conv(t_options *opts);
size_t				digits_len(unsigned long long n, size_t base_len);
void				swrite_digits_u(unsigned long long n, char *base, int n_len,
									char *s);
char				*digits_s(va_list va, char *base, t_options *opts);
char				*digits_u(va_list va, char *base, t_options *opts);
char				*d_conv(va_list va, t_options *opts);
char				*x_conv(va_list va, t_options *opts);
char				*u_conv(va_list va, t_options *opts);
int					ft_strnlen(char *s, int len);
char				*generic_conv(char *raw_str, int len, t_options *opts);
int					min(int a, int b);
int					max(int a, int b);
unsigned long long	raw_val_u(va_list va, t_options *opts);
long long			raw_val_s(va_list va, t_options *opts);
int					get_flags(char const *format, t_options *opts);
int					get_field_len(char const *format, t_options *opts);
int					get_precision(char const *format, t_options *opts);
int					get_modif(char const *format, t_options *opts);
t_match				*parser_one(char const *format, char const *supported);
int					parser_all(char const *format, char const *supported,
								t_list **matches);

#endif
