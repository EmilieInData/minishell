/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 21:42:18 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/19 04:24:26 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_tokens(t_data *d, char *input, int add_tokens, int pos)
{
	t_tokens	**new_tokens;
	char		**split_tokens;
	int			j;

	split_tokens = ft_split(input, ' ');
	new_tokens = init_new_tok(d, add_tokens);
	j = copy_tok_before(d, new_tokens, pos);
	j = insert_exp_tok(d, new_tokens, split_tokens, j);
	j = copy_rest_tok(d, new_tokens, pos, j);
	final_tok(d, new_tokens, j, split_tokens);
}

/* Function that checks if, after expanding,
there is any space within the token */
int	check_var_spaces(t_data *d, char *input, int pos)
{
	int	i;
	int	add_tokens;

	i = 0;
	add_tokens = 0;
	while (input[i] != '\0')
	{
		if (ft_isspace(input[i]))
			add_tokens++;
		i++;
	}
	if (add_tokens != 0)
		ft_add_tokens(d, input, add_tokens, pos);
	return (0);
}

int	check_previous_null(t_data *d, int i, char *cpy)
{
	int	check;

	check = verify_previous_type(d, i, cpy, 1);
	if (check == 3)
		return (3);
	else if (check == 2)
	{
		d->tokens[i]->type = ARG;
		d->tokens[i]->value = cpy;
	}
	else if (check == 1)
	{
		d->tokens[i]->type = END;
		return (free(cpy), 1);
	}
	else
		d->tokens[i]->type = END;
	return (0);
}

int	check_previous_heredoc(t_data *d, int i)
{
	if (i == 0)
		return (0);
	if (d->tokens[i - 1] && d->tokens[i - 1]->type == SPACES)
	{
		if (d->tokens[i - 2] && d->tokens[i - 2]->type == HEREDOC)
			return (1);
	}
	else if (d->tokens[i - 1] && d->tokens[i - 1]->type == HEREDOC)
		return (1);
	return (0);
}

int	expand_check_and_prev(t_data *d, char *cpy, char *expanded, int *i)
{
	cpy = ft_strdup(d->tokens[*i]->value);
	free(d->tokens[*i]->value);
	expanded = expand_env_variables(d, cpy, NULL);
	d->tokens[*i]->value = expanded;
	if (check_var_spaces(d, d->tokens[*i]->value, *i) == 1)
		return (1);
	if (!d->tokens[*i]->value[0])
	{
		if (check_previous_null(d, *i, cpy) == 1)
			return (1);
		else
			free(cpy);
	}
	else
	{
		d->tokens[*i]->type = ARG;
		free(cpy);
	}
	return (0);
}
