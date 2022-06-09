#include "utils.h"

void	obj_add(t_obj **lst, t_obj *new)
{
	t_obj	*p;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	p = *lst;
	while (p->next)
		p = p->next;
	p->next = new;
}

t_obj	*obj_last(t_obj *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
