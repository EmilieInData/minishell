/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_expand_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 03:16:01 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/19 03:16:03 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	**init_new_tok(t_data *d, int add_tokens)
{
	t_tokens	**new_tokens;

	new_tokens = (t_tokens **)malloc(sizeof(t_tokens *)
			* (d->tokens_qt + add_tokens + 1));
	if (!new_tokens)
		ft_malloc(d, NULL, NULL);
	return (new_tokens);
}

int	copy_tok_before(t_data *d, t_tokens **new_tokens, int pos)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < pos)
	{
		new_tokens[j] = (t_tokens *)malloc(sizeof(t_tokens));
		if (!new_tokens[j])
			ft_malloc(d, NULL, NULL);
		new_tokens[j]->value = ft_strdup(d->tokens[i]->value);
		new_tokens[j]->type = d->tokens[i]->type;
		i++;
		j++;
	}
	return (j);
}

int	insert_exp_tok(t_data *d, t_tokens **new, char **split_tok, int j)
{
	int	k;

	k = 0;
	while (split_tok[k])
	{
		new[j] = (t_tokens *)malloc(sizeof(t_tokens));
		if (!new[j])
			ft_malloc(d, NULL, NULL);
		new[j]->value = ft_strdup(split_tok[k]);
		new[j]->type = CMD;
		k++;
		j++;
	}
	return (j);
}

int	copy_rest_tok(t_data *d, t_tokens **new_tokens, int pos, int j)
{
	int	i;

	i = pos + 1;
	while (i < d->tokens_qt)
	{
		new_tokens[j] = (t_tokens *)malloc(sizeof(t_tokens));
		if (!new_tokens[j])
			ft_malloc(d, NULL, NULL);
		new_tokens[j]->value = ft_strdup(d->tokens[i]->value);
		new_tokens[j]->type = d->tokens[i]->type;
		i++;
		j++;
	}
	return (j);
}

void	final_tok(t_data *d, t_tokens **new, int total, char **split_tok)
{
	new[total] = NULL;
	ft_free(d->tokens);
	d->tokens = new;
	d->tokens_qt = total;
	free_array(split_tok);
}
