/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:11:40 by esellier          #+#    #+#             */
/*   Updated: 2024/10/17 22:09:46 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path_cmd(char **array, int j, t_data *data, char *tmp)
{
	char	*path;

	while (array[j])
	{
		path = ft_strjoin(array[j], tmp);
		if (!path)
		{
			free(tmp);
			ft_malloc(data, array, NULL);
		}
		if (access(path, F_OK | X_OK) == 0)
		{
			free(tmp);
			free_array(array);
			return (path);
		}
		free(path);
		j++;
	}
	free (tmp);
	free_array(array);
	return (NULL);
}

char	*check_path(t_section *section, t_data *data, char *path_lst)
{
	char	**array;
	int		j;
	char	*tmp;

	j = 0;
	array = split_env(path_lst, data);
	if (!array)
		ft_malloc(data, NULL, NULL);
	tmp = ft_strjoin("/", section->cmd[0]);
	if (!tmp)
		ft_malloc(data, array, NULL);
	return (find_path_cmd(array, j, data, tmp));
}

int	search_path(t_data *data, char **array, t_section *section)
{
	int	i;

	i = 0;
	if ((ft_strncmp(section->cmd[0], "/", 1) == 0)
		|| (ft_strncmp(section->cmd[0], ".", 1) == 0))
		return (section->path = section->cmd[0], 0);
	while (array[i])
	{
		if (ft_strncmp("PATH=", array[i], 5) == 0)
		{
			section->path = check_path(section, data, array[i]);
			if (! section->path)
			{
				if (ft_strchr(section->cmd[0], '/') != 0)
					return (error_exe(data, section->cmd[0], 0));
				return (error_exe(data, section->cmd[0], 1));
			}
			return (0);
		}
		else
			i++;
	}
	return (error_exe(data, section->cmd[0], 0));
}

char	**lst_to_arr(t_env *lst, t_data *data, char **array)
{
	int		i;

	i = 0;
	array = (char **)malloc((count_lst(lst) + 1) * sizeof (char *));
	if (!array)
		ft_malloc(data, NULL, NULL);
	while (lst)
	{
		if (lst->name && lst->value)
		{
			array[i] = ft_strjoin_three(lst->name, "=", lst->value);
			if (!array[i])
				ft_malloc(data, array, NULL);
		}
		if (!lst->value)
		{
			array[i] = ft_strjoin(lst->name, "=");
			if (!array[i])
				ft_malloc(data, array, NULL);
		}
		lst = lst->next;
		i++;
	}
	array[i] = '\0';
	return (array);
}

void	create_pipe(t_data *data)
{
	t_section	*current;
	int			tmp[2];

	current = data->sections;
	while (current && current->next)
	{
		if (current->fd_out == -2 && current->next->fd_in == -2)
		{
			if (pipe(tmp) == -1)
				error_exe(data, "pipe error", 2);
			current->fd_out = tmp[1];
			current->next->fd_in = tmp[0];
		}
		current = current->next;
	}
	return ;
}
