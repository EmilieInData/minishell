/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:50:28 by esellier          #+#    #+#             */
/*   Updated: 2024/10/17 22:10:29 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_path(char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 1;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c)
			count++;
		i++;
	}
	return (count);
}

int	strlen_path(char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] != c && str[len] != '\0')
		len++;
	return (len);
}

char	**put_path(char **array, char *str, char c, int path)
{
	int	i;
	int	j;
	int	len;
	int	s;

	j = 0;
	s = 5;
	while (j <= path)
	{
		i = 0;
		len = strlen_path(&str[s], c);
		array[j] = (char *)malloc((len + 1) * sizeof (char));
		if (!array[j])
			free_array(array);
		while (str[s] != c && str[s] != '\0')
			array[j][i++] = str[s++];
		array[j][i] = '\0';
		j++;
		s++;
	}
	array[j] = NULL;
	return (array);
}

char	**split_env(char *str, t_data *data)
{
	char	**array;
	int		path;
	char	c;

	c = ':';
	if (! str)
		return (NULL);
	path = count_path(str, c);
	array = (char **)malloc((path + 2) * sizeof(char *));
	if (!array)
		ft_malloc(data, NULL, NULL);
	return (put_path(array, str, c, path));
}
