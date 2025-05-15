/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:02:48 by esellier          #+#    #+#             */
/*   Updated: 2024/03/13 16:33:45 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_element;
	t_list	*tmp;

	if (!lst || !f || !del)
		return (NULL);
	new = 0;
	while (lst != NULL)
	{
		tmp = f(lst -> content);
		new_element = ft_lstnew(tmp);
		if (!new_element)
		{
			ft_lstclear(&new, del);
			del(tmp);
			return (NULL);
		}
		ft_lstadd_back(&new, new_element);
		lst = lst -> next;
	}
	return (new);
}

/*void	f(void *content)
{
	char	*p;
	p = (char *)content;
	if (p)
		*p = 'F';
}

void	del(void *content)
{
	if(content)
		free(content);
}*/

/*#include <stdio.h>
int main()
{
	char	*p1;
	char	*p2;
	char	*p3;

	p1 = malloc(sizeof(char *));
	p2 = malloc(sizeof(char *));
	p3 = malloc(sizeof(char *));

	t_list *lst = NULL;
	t_list *element1 = ft_lstnew(p1);
	t_list *element2 = ft_lstnew(p2);
	t_list *element3 = ft_lstnew(p3);

	lst = element1;
	element1 -> next = element2;
	element2 -> next = element3;
	element3 -> next = NULL;

	ft_lstmap(lst,(void *)f,(void *)del);
	if (ft_strncmp(element1 -> content, "F", 1) == 0)
	   printf("ok\n");
	else
		printf("ko\n");
	return (0);
}*/