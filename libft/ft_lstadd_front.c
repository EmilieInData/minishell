/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:05:37 by esellier          #+#    #+#             */
/*   Updated: 2024/03/13 15:47:19 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new -> next = *lst;
	*lst = new;
}

/*#include <stdio.h>

int main()
{
	char	*p1;
	char	*p2;
	char	*p3;

	p1 = malloc(sizeof(char *));
	p2 = malloc(sizeof(char *));
	p3 = malloc(sizeof(char *));

	p1[0] = '1';
	p1[1] = 0;
	p2[0] = '2';
	p2[1] = 0;
	p3[0] = '3';
	p3[1] = 0;

	t_list	*element1 = ft_lstnew(p1);
	t_list	*element2 = ft_lstnew(p2);
	t_list	*element3 = ft_lstnew(p3);

	ft_lstadd_front(&element3, element2);
	ft_lstadd_front(&element2, element1);
	
	while (element1)
	{
		printf("%s\n", element1-> content);
		element1 = element1 -> next;
	}
	printf("End.\n");
	return (0);
}*/