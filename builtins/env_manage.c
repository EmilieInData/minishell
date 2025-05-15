/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:14:34 by esellier          #+#    #+#             */
/*   Updated: 2024/10/17 22:24:20 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_flag(t_env *new_node)
{
	if (ft_strcmp(new_node->name, "_") == 0)
		new_node->flag = 'X';
	else
		new_node->flag = 'v';
	new_node->print = 0;
	return (new_node);
}

t_env	*env_new(char *str, t_env *new_node)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	new_node->name = malloc((i + 1) * sizeof(char));
	if (!new_node->name)
		return (free(new_node), NULL);
	ft_strlcpy(new_node->name, str, i + 1);
	new_node->name[i] = '\0';
	j = 0;
	while (str[i++])
		j++;
	new_node->value = malloc((j + 1) * sizeof(char));
	if (!new_node->value)
	{
		free (new_node->name);
		return (free(new_node), NULL);
	}
	ft_strlcpy(new_node->value, &str[i - j], j);
	new_node->value[j] = '\0';
	new_node = create_flag(new_node);
	return (new_node);
}

t_env	*create_env(char **env, t_data *data)
{
	int		i;
	t_env	*env_lst;
	t_env	*temp;
	t_env	*new_node;

	i = 0;
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		ft_malloc(data, NULL, NULL);
	env_lst = env_new(env[i], new_node);
	temp = env_lst;
	i++;
	while (env[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			ft_malloc(data, NULL, env_lst);
		env_lst->next = env_new(env[i], new_node);
		if (!env_lst->next)
			ft_malloc(data, NULL, env_lst);
		env_lst = env_lst->next;
		i++;
	}
	env_lst->next = '\0';
	return (temp);
}

int	create_value(t_env *new_node, int i, int j, char *str)
{
	if (j > 0)
	{
		new_node->value = malloc((j + 1) * sizeof(char));
		if (!new_node->value)
		{
			free(new_node->name);
			return (free(new_node), 1);
		}
		ft_strlcpy(new_node->value, &str[i - j], j + 1);
	}
	return (0);
}

int	exp_new(char *str, t_env *new_node)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	new_node->name = malloc((i + 1) * sizeof(char));
	if (!new_node->name)
		return (free(new_node), 1);
	ft_strlcpy(new_node->name, str, i + 1);
	new_node->name[i] = '\0';
	j = 0;
	while (str[i] && str[i++])
		j++;
	if (create_value(new_node, i + 1, j, str) == 1)
		return (1);
	new_node->flag = 'v';
	if (j == 0)
		new_node->value = '\0';
	if (j == 0)
		new_node->flag = 'W';
	if (str[i] && str[i] == '=')
		new_node->flag = 'V';
	new_node->print = 0;
	return (0);
}
