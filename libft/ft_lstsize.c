/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:59:02 by esellier          #+#    #+#             */
/*   Updated: 2024/03/26 14:56:06 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 1;
	while (lst && lst -> next != NULL)
	{
		lst = lst -> next;
		i++;
	}
	return (i);
}

/*#include <stdio.h>
int main ()
{
	char	*p1;
	char	*p2;
	char	*p3;

	p1 = malloc(sizeof(char*));
	p2 = malloc(sizeof(char*));
	p3 = malloc(sizeof(char*));

	t_list  *element1 = ft_lstnew(p1);
	t_list  *element2 = ft_lstnew(p2);
	t_list  *element3 = ft_lstnew(p3);

	element1 -> next = element2;
	element2 -> next = element3;
	element3 -> next = NULL;

	printf("%d\n", ft_lstsize(element1));
	return(0);
}*/
