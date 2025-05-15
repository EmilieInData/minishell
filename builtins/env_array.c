/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:14:34 by esellier          #+#    #+#             */
/*   Updated: 2024/09/03 16:47:15 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**copy_env(t_data *data, char **array, t_env *env)
{
	int	len;
	int	i;

	i = 0;
	while (env)
	{
		len = ft_strlen(env->name) + ft_strlen(env->value) + 2;
		array[i] = (char *)malloc(len * sizeof(char));
		if (!array[i])
			ft_malloc(data, array, NULL);
		if (env->name)
		{
			ft_strlcpy(array[i], env->name, len - ft_strlen(env->value) - 1);
			ft_strlcat(array[i], "=", ft_strlen(env->name) + 2);
			if (env->value)
				ft_strlcat(array[i], env->value, len);
		}
		i++;
		env = env->next;
	}
	array[i] = '\0';
	return (array);
}

char	**env_array(t_data *data, char **array)
{
	t_env	*env;
	int		i;

	i = 0;
	env = data->env_lst;
	while (env)
	{
		i++;
		env = env->next;
	}
	array = (char **)malloc((i + 1) * sizeof (char *));
	if (!array)
		ft_malloc(data, NULL, NULL);
	env = data->env_lst;
	array = copy_env(data, array, env);
	return (array);
}

t_env	*search_str(char *str, t_data *data)
{
	t_env	*current;

	current = data->env_lst;
	while (current)
	{
		if (ft_strcmp(str, current->name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
