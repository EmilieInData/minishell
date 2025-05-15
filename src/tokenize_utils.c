/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:48:18 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/22 22:14:54 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function that removes the quotes from the arguments */
void	remove_quotes(char *str)
{
	char	*src;
	char	*dst;
	char	c;

	src = str;
	dst = str;
	c = str[0];
	while (*src)
	{
		if (*src != c)
			*dst++ = *src;
		src++;
	}
	*dst = '\0';
}

/* Function that removes the quotes from tokens of type SQUOTE and DQUOTE.
Additionally, it checks if there are variables to expand within the DQUOTE.*/
int	clean_quotes(t_data *d, char *res, int i, int check)
{
	while (i < d->tokens_qt)
	{
		if (d->tokens[i]->type == SQUOTE || d->tokens[i]->type == DQUOTE)
		{
			remove_quotes(d->tokens[i]->value);
			check = verify_previous_type(d, i, d->tokens[i]->value, 0);
			if (check == 2)
				d->tokens[i]->type = NOEXP;
			else if (check == 1)
				return (1);
			if (d->tokens[i]->type == DQUOTE
				&& find_dollar(d->tokens[i]->value))
			{
				res = expand_env_variables(d, d->tokens[i]->value, res);
				free(d->tokens[i]->value);
				d->tokens[i]->value = res;
				d->tokens[i]->type = ARG;
			}
			else
				d->tokens[i]->type = ARG;
		}
		i++;
	}
	d->tokens_qt = i;
	return (0);
}

void	ft_move_tokens(t_data *data, int *i, int *j)
{
	while (*j < data->tokens_qt - 1)
	{
		data->tokens[*j] = data->tokens[*j + 1];
		(*j)++;
	}
	data->tokens_qt--;
	data->tokens[data->tokens_qt] = NULL;
	(*i)--;
}

void	delete_token_type(t_data *d, int type)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (d->tokens[i])
	{
		if (d->tokens[i]->type != type)
		{
			if (i != j)
				d->tokens[j] = d->tokens[i];
			j++;
		}
		else
		{
			free(d->tokens[i]->value);
			free(d->tokens[i]);
			d->tokens_qt--;
		}
		i++;
	}
	d->tokens[j] = '\0';
}

void	join_tokens(t_data *d, int i, int j)
{
	char	*new_value;

	while (i < d->tokens_qt - 1)
	{
		if ((d->tokens[i]->type == ARG || d->tokens[i]->type == 12)
			&& (d->tokens[i + 1]->type == ARG || d->tokens[i + 1]->type == 12))
		{
			new_value = malloc(ft_strlen(d->tokens[i]->value)
					+ ft_strlen(d->tokens[i + 1]->value) + 1);
			if (!new_value)
				ft_malloc(d, NULL, NULL);
			ft_strlcpy(new_value, d->tokens[i]->value,
				ft_strlen(d->tokens[i]->value) + 1);
			ft_strlcat(new_value, d->tokens[i + 1]->value,
				(ft_strlen(new_value)
					+ ft_strlen(d->tokens[i + 1]->value)) + 1);
			free(d->tokens[i]->value);
			d->tokens[i]->value = new_value;
			free(d->tokens[i + 1]->value);
			free(d->tokens[i + 1]);
			j = i + 1;
			ft_move_tokens(d, &i, &j);
		}
		i++;
	}
}
