/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 13:29:32 by lzins             #+#    #+#             */
/*   Updated: 2021/01/27 15:18:43 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcpy(t_list *src, size_t content_size)
{
	t_list	*copy;
	void	*new_content;

	if (!src)
		return (NULL);
	copy = NULL;
	new_content = NULL;
	if (!(new_content = malloc(content_size))
			|| !(copy = ft_lstnew(new_content))
			|| (!(copy->next = ft_lstcpy(src->next, content_size))
					&& src->next))
	{
		free(new_content);
		free(copy);
		return (NULL);
	}
	ft_memcpy(new_content, src->content, content_size);
	return (copy);
}
