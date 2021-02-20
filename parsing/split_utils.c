/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:57:39 by lzins             #+#    #+#             */
/*   Updated: 2021/02/16 15:59:18 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	free_split(char **splitted)
{
	int i;

	if (!splitted)
		return ;
	i = 0;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
}

int		split_error(void)
{
	ft_printf("Error\n");
	ft_printf("During split");
	return (-1);
}

int		free_split_error(char **splitted)
{
	free_split(splitted);
	return (-1);
}

int		splitlen(char **splitted)
{
	int i;

	i = 0;
	while (splitted[i])
		i++;
	return (i);
}

char	**split_and_check_len(char *str, char *delim, int n_fields,
			char *error_message)
{
	char	**splitted;

	if (!(splitted = ft_split(str, delim)))
	{
		split_error();
		return (NULL);
	}
	if (splitlen(splitted) != n_fields)
	{
		ft_printf("Error\n");
		ft_printf("Wrong number of elements in '%s' (expected %d, got %d)\n",
			str, n_fields, splitlen(splitted));
		ft_printf(error_message);
		free_split(splitted);
		return (NULL);
	}
	return (splitted);
}
