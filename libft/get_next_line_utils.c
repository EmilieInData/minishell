/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:57:11 by esellier          #+#    #+#             */
/*   Updated: 2024/10/04 16:00:50 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_buf_cpy(char **stach_ptr, char *buf, int readed)
{
	int		i;
	int		j;
	char	*tmp;
	char	*stach;

	i = 0;
	j = 0;
	stach = *stach_ptr;
	tmp = malloc((readed + ft_strlen_gnl(stach, 0) + 1) * sizeof(char));
	if (!tmp)
	{
		ft_stach_error (stach_ptr);
		return ;
	}
	while (stach && stach[i] != '\0')
	{
		tmp[i] = stach[i];
		i++;
	}
	while (j < readed)
		tmp[i++] = buf[j++];
	tmp[i] = '\0';
	if (stach)
		free (stach);
	*stach_ptr = tmp;
}

int	ft_strlen_gnl(char *stach, int line)
{
	int	len;

	if (!stach)
		return (0);
	len = 0;
	if (line)
	{
		while (stach[len] != '\n' && stach[len] != '\0')
			len ++;
		return (len);
	}
	while (stach[len] != '\0')
		len++;
	return (len);
}

char	*ft_end_stach(char **stach_ptr)
{
	int		i;
	char	*tmp;
	char	*stach;

	stach = *stach_ptr;
	tmp = malloc((ft_strlen_gnl(stach, 1) + 2) * sizeof(char));
	if (!tmp)
		return (ft_stach_error(stach_ptr));
	i = 0;
	while (stach[i] != '\n')
	{
		tmp[i] = stach[i];
		i++;
	}
	tmp[i] = '\n';
	tmp[i + 1] = '\0';
	*stach_ptr = ft_sub_stach(stach_ptr, i + 1);
	if (!*stach_ptr)
	{
		free (tmp);
		return (NULL);
	}
	if (ft_strlen_gnl(*stach_ptr, 0) == 0)
		ft_stach_error(stach_ptr);
	return (tmp);
}

int	ft_search_line(char *stach)
{
	int	i;

	if (!stach)
		return (0);
	i = 0;
	while (stach[i] != '\n' && stach[i] != '\0')
		i++;
	if (stach[i] == '\n')
		return (1);
	return (0);
}

char	*ft_sub_stach(char **stach_ptr, int start)
{
	char	*stach;
	char	*new;
	int		len;
	int		i;

	i = 0;
	stach = *stach_ptr;
	if (!stach)
		return (NULL);
	len = ft_strlen_gnl(stach, 0) - start;
	new = malloc((len + 1) * sizeof(char));
	if (!new)
		return (ft_stach_error(stach_ptr));
	while (stach[start] != '\0')
		new[i++] = stach[start++];
	new[len] = '\0';
	ft_stach_error(stach_ptr);
	return (new);
}
