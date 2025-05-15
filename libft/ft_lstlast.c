/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:51:46 by esellier          #+#    #+#             */
/*   Updated: 2024/03/13 16:25:41 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst -> next != NULL)
		lst = lst -> next;
	return (lst);
}

/*#include <stdio.h>
int main ()
{
	char	*p1;
	char	*p2;
	char	*p3;

	p1 = malloc(sizeof(char *));
	p2 = malloc(sizeof(char *));
	p3 = malloc(sizeof(char *));

	*p1 = '1';
	*p2 = '2';
	*p3 = '3';

	t_list *element1 = ft_lstnew(p1);
	t_list *element2 = ft_lstnew(p2);
	t_list *element3 = ft_lstnew(p3);

	element1 -> next = element2;
	element2 -> next = element3;
	element3 -> next = NULL;
	t_list *print = ft_lstlast(element1);
	printf("%s\n", (char *) print -> content);
	return (0);
}*/