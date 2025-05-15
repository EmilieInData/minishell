/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:17:55 by esellier          #+#    #+#             */
/*   Updated: 2024/10/22 18:57:19 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*adjust_env(t_data *data, t_env *to_del)
{
	t_env	*previous;
	t_env	*current;

	previous = NULL;
	current = data->env_lst;
	while ((current) != to_del)
	{
		previous = (current);
		(current) = (current)->next;
	}
	free((current)->name);
	free((current)->value);
	if (previous)
		previous->next = (current)->next;
	if (!previous)
		data->env_lst = (current)->next;
	free(current);
	return (data->env_lst);
}

void	make_unset(char **str, t_data *data)
{
	t_env	*current;
	int		i;

	i = 1;
	while (str[i])
	{
		current = data->env_lst;
		while (current)
		{
			if (ft_strcmp(str[i], current->name) == 0)
			{
				data->env_lst = adjust_env(data, current);
				current = data->env_lst;
			}
			else
				current = current->next;
		}
		i++;
	}
	return ;
}

int	make_env(t_data *data, char **str)
{
	t_env	*current;

	if (str[1])
	{
		write(2, "env: ", 5);
		write(2, str[1], ft_strlen(str[1]));
		return (write(2, ": No such file or directory\n", 28), 1);
	}
	current = data->env_lst;
	if (!current)
	{
		write(2, "env: No such file or directory\n", 31);
		return (1);
	}
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->name, current->value);
		else if (!current->value && current->flag == 'V')
			printf("%s=\n", current->name);
		current = current->next;
	}
	return (0);
}

void	change_cd_data(t_data *data, char *new)
{
	if (data->current_dir)
		free(data->current_dir);
	data->current_dir = ft_strdup(new);
	if (!data->current_dir)
	{
		free (new);
		ft_malloc(data, NULL, NULL);
	}
	return ;
}
