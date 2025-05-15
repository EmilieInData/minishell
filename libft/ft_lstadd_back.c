/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:39:34 by esellier          #+#    #+#             */
/*   Updated: 2024/03/13 15:49:21 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
		ft_lstlast(*lst)-> next = new;
}

/*#include <stdio.h>
int main ()
{
	char	*p1;
	char	*p2;
	char	*p3;
	char	*p4;

	p1 = malloc(sizeof(char *));
	p2 = malloc(sizeof(char *));
	p3 = malloc(sizeof(char *));
	p4 = malloc(sizeof(char *));

	p1[0] = '1';
	p1[1] = 0;
	p2[0] = '2';
	p2[1] = 0;
	p3[0] = '3';
	p3[1] = 0;
	p4[0] = '4';
	p4[1] = 0;

	t_list *element1 = ft_lstnew(p1);
	t_list *element2 = ft_lstnew(p2);
	t_list *element3 = ft_lstnew(p3);
	t_list *lst = NULL;
	
	lst = element1;	
	element1 -> next = element2;
	element2 -> next = element3;
	element3 -> next = NULL;

	t_list *new = ft_lstnew(p4);
	ft_lstadd_back(&lst, new);
	
	while(lst != NULL)
	{
		printf("%s\n", (char *) lst -> content);
		lst = lst -> next;
	}
		return (0);
}*/