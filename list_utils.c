#include "cub3d.h"

t_sprite *sprite_at(t_list *sprite_list)
{
	return ((t_sprite*)(sprite_list->content));
}

t_ipt2d *ipt2d_at(t_list *elem)
{
	return ((t_ipt2d*)(elem->content));
}

// require non empty path i.e. path != NULL
t_ipt2d *path_destination(t_list *path)
{
	t_list *last_elem;

	last_elem = ft_lstlast(path);
	return (ipt2d_at(last_elem));
}

void	pop_first(t_list **alst, t_ipt2d *res)
{
	t_list *next;

	if (!alst || !*alst)
		return ;
	next = (*alst)->next;
	if (res)
		*res = *(t_ipt2d*)((*alst)->content);
	ft_lstdelone(*alst, free);
	*alst = next;
}

t_list	*ipt2d_lstnew(t_ipt2d val)
{
	t_list *new_elem;
	t_ipt2d *new_val;

	if (!(new_val = malloc(sizeof(t_ipt2d))))
		return (NULL);
	*new_val = val;
	if (!(new_elem = ft_lstnew(new_val)))
	{
		free(new_val);
		return (NULL);
	}
	return (new_elem);
}

int		add_back_ipt2d_once(t_list **alst, t_ipt2d val)
{
	t_list *lst_match;
	t_list *new_elem;

	lst_match = ft_lstfind(*alst, &val, sizeof(t_ipt2d));
	if (lst_match)
		return (1);
	if (!(new_elem = ipt2d_lstnew(val)))
		return (0);
	ft_lstadd_back(alst, new_elem);
	return (1);
}
