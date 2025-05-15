/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:10:47 by esellier          #+#    #+#             */
/*   Updated: 2024/03/13 16:37:29 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (0);
	new -> content = content;
	new -> next = NULL;
	return (new);
}

/*#include <stdio.h>
int main ()
{
	char	*content;

	content = malloc(sizeof(char*));
	content[0] = '1';
	content[1] = '2';
	content[2] = '3';
	content[3] = 0;
	
	t_list *print = ft_lstnew(content);
	printf("%s\n", (char *)(print -> content));
	return (0);
}*/