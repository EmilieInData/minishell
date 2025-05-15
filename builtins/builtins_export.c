/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:17:55 by esellier          #+#    #+#             */
/*   Updated: 2024/10/22 19:44:05 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	p_exp_loop(t_env *to_print, t_env *old, t_env *cur, t_env *env_lst)
{
	while (to_print == old)
	{
		cur = env_lst;
		while (cur && (cur->print == 1 || cur->flag == 'X'))
			cur = cur->next;
		if (!cur)
			return ;
		to_print = cur;
		while (cur)
		{
			if (cur->print == 0 && (cur->flag == 'v' || cur->flag == 'V'
					|| cur->flag == 'W') && ft_strcmp(cur->name, to_print->name)
				== -1 && ft_strcmp(old->name, cur->name) == -1)
				to_print = cur;
			cur = cur->next;
		}
		if (to_print->flag == 'W')
			printf("declare -x %s\n", to_print->name);
		else if (to_print->value)
			printf("declare -x %s=\"%s\"\n", to_print->name, to_print->value);
		else
			printf("declare -x %s=\"\"\n", to_print->name);
		old = to_print;
		to_print->print = 1;
	}
}

void	print_export(t_env *env_lst)
{
	t_env	*to_print;
	t_env	*current;
	t_env	*old;

	current = env_lst;
	to_print = current;
	while (current)
	{
		if ((current->flag == 'v' || current->flag == 'V')
			&& ft_strcmp(current->name, to_print->name) == -1)
			to_print = current;
		current = current->next;
	}
	printf("declare -x %s=\"%s\"\n", to_print->name, to_print->value);
	old = to_print;
	to_print->print = 1;
	p_exp_loop(to_print, old, current, env_lst);
	current = env_lst;
	while (current)
	{
		if (current->print == 1)
			current->print = 0;
		current = current->next;
	}
	return ;
}

void	export_malloc(char **str, int i, t_env *current, t_data *data)
{
	if (!current->next)
		ft_malloc(data, NULL, NULL);
	if (exp_new(str[i], current->next) == 1)
		ft_malloc(data, NULL, NULL);
}

int	make_export(char **str, t_data *data)
{
	t_env	*current;
	int		i;

	current = data->env_lst;
	if (!str[1])
		print_export(current);
	else
	{
		while (current->next)
			current = current->next;
		i = 1;
		while (str[i])
		{
			if ((check_args(str[i]) == 0)
				&& (check_name(str[i], i, data->env_lst, data) == 0))
			{
				current->next = malloc(sizeof(t_env));
				export_malloc(str, i, current, data);
				current = current->next;
				current->next = NULL;
			}
			i++;
		}
	}
	return (0);
}

int	make_pwd(t_data *data)
{
	printf("%s\n", data->current_dir);
	return (0);
}
