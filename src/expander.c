/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:00:48 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/01 11:50:17 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function that searches for the variable name in the environment */
char	*find_var_name(char *value, int *i, t_data *data)
{
	char	*env_var;
	int		k;
	int		len;

	k = 1;
	len = 0;
	while (value[*i + k] != 32 && value[*i + k] != '\0')
		k++;
	env_var = malloc(sizeof(char *) * k);
	if (!env_var)
		ft_malloc(data, NULL, NULL);
	while (value[*i + len + 1] != 32 && value[*i + len + 1] != '\0')
	{
		env_var[len] = value[*i + len + 1];
		len++;
	}
	env_var[len] = '\0';
	*i = *i + k - 1;
	return (env_var);
}

/* Function that locates any variable to expand within a DQUOTE type token */
int	find_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

/* Function that removes the dollar sign from the variable 
and the first number if it exists */
char	*quit_dollar(char *value, int *i)
{
	int		j;
	char	*new_value;

	new_value = value;
	if (ft_isdigit(value[*i + 1]))
		*i = *i + 2;
	else
		*i = *i +1;
	j = 0;
	while (value[*i] != '\0')
	{
		new_value[j++] = value[(*i)++];
	}
	new_value[j] = '\0';
	if (j == 0)
		new_value = NULL;
	return (new_value);
}

/* Function that removes the first $ and passes the variable name 
to the environment to expand it to its value, if the variable exists, 
otherwise it returns NULL */
char	*expand_var(t_data *data, char *value)
{
	t_env	*current;
	char	*new_value;
	char	*temp;

	current = data->env_lst;
	new_value = value;
	if (!new_value)
		return (NULL);
	while (current)
	{
		if (ft_strcmp(current->name, new_value) == 0)
		{
			temp = current->value;
			if (!temp)
			{
				new_value = "";
				return (new_value);
			}
			new_value = temp;
			return (new_value);
		}
		current = current->next;
	}
	return (NULL);
}

/* Function that identifies the type of token:
tokens of type VAR and DQUOTE will be expanded if they have the $ symbol.
If the first character after the $ is the ? symbol,
it will expand to the return value rt_value from the data structure.
If the first character after the $ is a number, the $ and the first number
will be removed, and the rest of the characters will be returned as the value.
In other cases, the value of the variable will be evaluated from the
environment, and it will expand to the value returned if its possible.
If the variable cannot be expanded and thus equals NULL, and the previous
token is of type INPUT, TRUNC, or APPEND, an error is returned. 
For this reason, I create a copy of the token's value that I must always free.*/
int	ft_expander(t_data *d)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (i < d->tokens_qt)
	{
		if (d->tokens[i]->type == VAR || d->tokens[i]->type == DQUOTE)
		{
			if (check_previous_heredoc(d, i) == 1)
				d->tokens[i]->type = ARG;
			else
			{
				check = expand_check_and_prev(d, NULL, NULL, &i);
				if (check == 1)
					return (1);
			}
		}
		i++;
	}
	return (0);
}
