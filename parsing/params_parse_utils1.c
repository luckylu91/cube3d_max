/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_parse_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:56:31 by lzins             #+#    #+#             */
/*   Updated: 2021/02/16 15:57:36 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "params_parse_utils.h"

static int	check_valid_dimentions(char *line, int w, int h)
{
	if (w <= 200 || h <= 200)
	{
		ft_printf("Error\n");
		ft_printf("Unvalid width or height in resolution parsing\n");
		ft_printf("At least 200 pixels are expected for each value\n");
		ft_printf("Got %d and %d\n", w, h);
		ft_printf("Line : %s\n", line);
		return (-1);
	}
	return (1);
}

static void	cap_dimention(char *field_name, int *val, int cap_value)
{
	if (*val > cap_value)
	{
		ft_printf("Caping %s - arbitrarily - to 1920 (%d was given): "
			"there is no mlx_screen_size in this minilibx"
			"implementation (openGL)\n", field_name, val);
		*val = cap_value;
	}
}

int			parse_resolution(char *line, int *w, int *h)
{
	char	**splitted;

	if (!(splitted = split_and_check_len(line, " ", 3,
			"During resolution-parameter parsing\n")))
		return (-1);
	*w = ft_atoi(splitted[1]);
	*h = ft_atoi(splitted[2]);
	if (check_valid_dimentions(line, *w, *h) == -1)
		return (free_split_error(splitted));
	cap_dimention("WIDTH", w, 1920);
	cap_dimention("HEIGHT", h, 1080);
	free_split(splitted);
	return (0);
}

int			parse_text_param(char *line, char **text)
{
	char	**splitted;

	if (!(splitted = split_and_check_len(line, " ", 2,
			"During text-parameter parsing\n")))
		return (-1);
	*text = ft_strdup(splitted[1]);
	free_split(splitted);
	return (0);
}

int			parse_image_path(char *line, t_pack *p, t_img *im)
{
	char	*fname;
	int		ret;

	fname = NULL;
	if (parse_text_param(line, &fname) == -1)
		ret = -1;
	else
		ret = load_image(p, fname, im);
	free(fname);
	return (ret);
}
