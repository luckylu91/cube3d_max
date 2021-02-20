/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_parse_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:05:49 by lzins             #+#    #+#             */
/*   Updated: 2021/02/17 09:19:47 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "params_parse_utils.h"

static int	color_from_split(char *line, char **splitted_color, int *color)
{
	int		r;
	int		g;
	int		b;

	r = ft_atoi(splitted_color[0]);
	g = ft_atoi(splitted_color[1]);
	b = ft_atoi(splitted_color[2]);
	*color = (r << 16) + (g << 8) + b;
	if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
	{
		ft_printf("Error\n");
		ft_printf("One r/g/b value is not in 0-255 range in"
		"color_from_split\n");
		ft_printf("Line : %s\n", line);
		return (-1);
	}
	return (0);
}

int			parse_color(char *line, int *color)
{
	char	**splitted_line;
	char	**splitted_color;
	int		ret;

	if (!(splitted_line = split_and_check_len(line, " ", 2,
			"During color parsing (separating the line)\n")))
		return (-1);
	if (!(splitted_color = split_and_check_len(splitted_line[1], ",", 3,
			"During color parsing (separating the colors)\n")))
		return (free_split_error(splitted_line));
	ret = color_from_split(line, splitted_color, color);
	free_split(splitted_line);
	free_split(splitted_color);
	return (ret);
}

static int	wrong_color_arg_error(char *line)
{
	ft_printf("Error\n");
	ft_printf("Expected : path/to/texture OR r,g,b\n");
	ft_printf("Line : %s\n", line);
	return (-1);
}

int			color_or_text(char *line, int *color, char **text)
{
	char	**splitted_line;
	char	**splitted_arg;
	int		arg_splitlen;
	int		ret;

	*text = NULL;
	if (!(splitted_line = split_and_check_len(line, " ", 2,
			"Expected : path/to/texture OR r,g,b\n")))
		return (-1);
	if (!(splitted_arg = ft_split(line, ",")))
		return (split_error());
	arg_splitlen = splitlen(splitted_arg);
	if (arg_splitlen != 1 && arg_splitlen != 3)
		ret = wrong_color_arg_error(line);
	else if (arg_splitlen == 1 && !(*text = ft_strdup(splitted_line[1])))
		ret = malloc_error();
	else if (*text)
		ret = (1);
	else if (arg_splitlen == 3)
		ret = color_from_split(line, splitted_arg, color);
	free_split(splitted_line);
	free_split(splitted_arg);
	return (ret);
}
