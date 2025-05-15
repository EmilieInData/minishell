/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:10:25 by esellier          #+#    #+#             */
/*   Updated: 2024/07/08 19:41:45 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	ls;
	size_t	ls1;
	char	*m;

	ls = ft_strlen(s1) + ft_strlen(s2);
	ls1 = ft_strlen(s1);
	if (s1 && s2)
	{
		m = (char *)malloc(ls + 1);
		if (!m)
			return (NULL);
		ft_strlcpy(m, s1, ls1 + 1);
		ft_strlcat(m, s2, ls + 1);
		return (m);
	}
	return (0);
}

/*int main()
{
	char	*r;
	char const	*s1 = "Hi";
	char const	*s2 = "42";
	r = ft_strjoin(s1, s2);
	printf("%s", r);
}*/
