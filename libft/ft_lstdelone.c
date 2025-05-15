/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:25:34 by esellier          #+#    #+#             */
/*   Updated: 2024/03/13 16:43:19 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del (lst -> content);
	free (lst);
}

/*void	del(void *content)
{
	if (content)
		free(content);
}*/

/*#include <stdio.h>
int main ()
{
	char	*p1;
	char	*p2;

	p1 = malloc (2);
	p2 = malloc (2);
	
	p1[0] = '1';
	p1[1] = 0;
	p2[0] = '2';
	p2[1] = 0;

	t_list *element1 = ft_lstnew(p1);
	t_list *element2 = ft_lstnew(p2);

	element1 -> next = element2;
	element2 -> next = NULL;

	printf("bef: '%s'\n", element2 -> content);
	ft_lstdelone(element2, del);
	printf("aft: '%s'\n", element2 -> content);
	return (0);
}*/