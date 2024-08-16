/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:59:43 by esellier          #+#    #+#             */
/*   Updated: 2024/08/16 18:48:49 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	modulo_negativ(int a)
{
	int	r;

	while (a < 0)
		a = a + 256;
	r = a % 256;
	return (r);
}

int	strncmp_long(const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned char	*cs1;
	unsigned char	*cs2;

	cs1 = (unsigned char *) s1;
	cs2 = (unsigned char *) s2;
	i = 0;
	while ((cs1[i] != '\0') && (cs1[i] == cs2[i]))
		i++;
	if ((cs1[i] < cs2[i] && ft_strlen(s1) == ft_strlen(s2))
		|| ft_strlen(s1) < ft_strlen(s2))
		return (-1);
	if ((cs1[i] > cs2[i] && ft_strlen(s1) == ft_strlen(s2))
		|| ft_strlen(s1) > ft_strlen(s2))
		return (1);
	return (0);
}

int	check_minmax(char *str)
{
	if ((ft_atoi(str) != 0 || ft_strncmp(str, "0", 1) == 0)
		|| ft_strncmp(str, "-9223372036854775808", 20) == 0)
	{
		if ((str[0] >= '0' && str[0] <= '9') || str[0] == '+')
		{
			if (strncmp_long(str, "9223372036854775807") <= 0)
				return (0);
			return (1);
		}
		else if (str[0] == '-')
		{
			if (strncmp_long(str, "-9223372036854775808") <= 0)
				return (0);
			return (1);
		}
	}
	return (1);
}
