#include "libft.h"
#include <stdio.h>

void add_int(t_list **l, int i)
{
	int *iptr;

	iptr = malloc(sizeof(int));
	*iptr = i;
	ft_lstadd_back(l, ft_lstnew(iptr));
}
void print_int(void *iptr)
{
	printf("%d -> ", *(int*)iptr);
}

void print_ilist(t_list *l)
{
	ft_lstiter(l, &print_int);
	printf("END\n");
}

int main()
{
	t_list *l1;
	t_list *l2;
	int i;

	l1 = NULL;
	l2 = NULL;
	i = -1;
	while (++i < 10)
	{
		add_int(&l1, i);
	}
	printf ("l1 :");
	print_ilist(l1);
	ft_lstcpy(l1, &l2, sizeof(int));
	printf ("l2 :");
	print_ilist(l2);

	// t_list *l = l1->next->next; // 2
	// ft_lstremove(&l1, l, &free);
	// printf ("l1 without '2' : ");
	// print_ilist(l1);
	// l = l1; // HEAD
	// ft_lstremove(&l1, l, &free);
	// printf ("removing head : ");
	// print_ilist(l1);
	// l = ft_lstlast(l1); // TAIL
	// ft_lstremove(&l1, l, &free);
	// printf ("removing last : ");
	// print_ilist(l1);
}