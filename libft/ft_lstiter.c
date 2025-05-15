/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:50:58 by esellier          #+#    #+#             */
/*   Updated: 2024/03/13 16:21:52 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst != NULL)
	{
		f (lst -> content);
		lst = lst -> next;
	}
	return ;
}

/*void	f(void *content)
{
	char	*p;
	p = (char *) content;
	if (p)
		*p = 'F';
}*/

/*#include <stdio.h>
int main()
{
	char	*p1;
	char	*p2;
	char	*p3;

	p1 = malloc(sizeof(char *));
	if (!p1)
		return(1);
	p2 = malloc(sizeof(char *));
	if (!p2)
	{
		free(p1);
		return(1);
	}
	p3 = malloc(sizeof(char *));
	if (!p3)
	{
		free(p1);
		free(p2);
		return (1);
	}

	*p1 = '1';
	*p2 = '2';
	*p3 = '3';

	t_list *element1 = ft_lstnew(p1);
	t_list *element2 = ft_lstnew(p2);
	t_list *element3 = ft_lstnew(p3);

	element1 -> next = element2;
	element2 -> next = element3;
	element3 -> next = NULL;

	ft_lstiter(element1,(void *)f);
	printf("%s\n", element1 -> content);
	printf("%s\n", element2 -> content);
	printf("%s\n", element3 -> content);

	free(p1);
	free(p2);
	free(p3);
	return(0);
}*/