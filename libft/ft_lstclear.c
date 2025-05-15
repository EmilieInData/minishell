/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:16:28 by esellier          #+#    #+#             */
/*   Updated: 2024/03/13 15:54:44 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	if (!del || ! *lst)
		return ;
	while (*lst)
	{
		next = *lst;
		*lst = (*lst)-> next;
		ft_lstdelone(next, del);
	}
	*lst = NULL;
}

/*void   del(void *content)
{
    if (content)
        free (content);
}*/

/*#include <stdio.h>
int main()
{
    char    *p1;
    char    *p2;
    char    *p3;

    p1 = malloc(sizeof(char *));
    p2 = malloc(sizeof(char *));
    p3 = malloc(sizeof(char *));

    p1[0] = '1';
	p1[1] = 0;
	p2[0] = '2';
	p2[1] = 0;
	p3[0] = '3';
	p3[1] = 0;

    t_list *element1 = ft_lstnew(p1);
    t_list *element2 = ft_lstnew(p2);
    t_list *element3 = ft_lstnew(p3);

    element1 -> next = element2;
    element2 -> next = element3;
    element3 -> next = NULL;

    ft_lstclear(&element1, (void *)del);
    if (element1 == NULL)
        printf("OK");
    else
        printf("KO");
    return (0);
}*/