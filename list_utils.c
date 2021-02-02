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