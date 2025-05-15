/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:09:23 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/22 22:11:18 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function that searches for the full name of the variable 
when it starts with $ until it finds another delimiter. */
int	end_variable(char *input, int i)
{
	while (input[i] != '\0')
	{
		if (ft_isdelimiter(input[i]))
			return (i - 1);
		i++;
	}
	return (i);
}

void	tok_delimiter(t_data *data, char *input, int *ind, int *start)
{
	data->tokens[*ind] = malloc(sizeof(t_tokens));
	if (!data->tokens[*ind])
		ft_malloc(data, NULL, NULL);
	data->tokens[*ind]->value = malloc(sizeof(char) * 2);
	if (!data->tokens[*ind]->value)
	{
		free(data->tokens[*ind]);
		ft_malloc(data, NULL, NULL);
	}
	data->tokens[*ind]->value[0] = input[*start];
	data->tokens[*ind]->value[1] = '\0';
	data->tokens[*ind]->type = ft_isdelimiter(input[*start]);
	(*ind)++;
	(*start)++;
}

void	tok_nodelimiter(t_data *data, int *ind, int *start, int *end)
{
	char	*str;

	str = malloc((*end - *start + 1) * sizeof(char));
	if (!str)
		ft_malloc(data, NULL, NULL);
	ft_strlcpy(str, data->prompt + *start, *end - *start + 1);
	data->tokens[*ind] = malloc(sizeof(t_tokens));
	if (!data->tokens[*ind])
	{
		free(str);
		ft_malloc(data, NULL, NULL);
	}
	data->tokens[*ind]->value = str;
	if (ft_isdelimiter(data->prompt[*start]))
	{
		data->tokens[*ind]->type = ft_isdelimiter(data->prompt[*start]);
		if (data->tokens[*ind]->type == INPUT)
			data->tokens[*ind]->type = HEREDOC;
		else if (data->tokens[*ind]->type == TRUNC)
			data->tokens[*ind]->type = APPEND;
	}
	else
		data->tokens[*ind]->type = ARG;
	(*ind)++;
	*start = *end;
}

/* Function that determines what type of delimiter has been found 
and separates by types:
1 - Those that are within double or single quotes; we must find 
their corresponding closing quote.
2 - If it finds a << to distinguish it from <.
3 - If it finds a >> to distinguish it from >.
4 - If it finds consecutive spaces, it simply ignores them.
5 - If it finds $, it should be stored as type VAR until the next space.
6 - Otherwise, it will be a simple delimiter of type | < >. */
void	define_delimiter(t_data *data, int *start, int *end, int *index)
{
	if (ft_isdelimiter(data->prompt[*start]) == SQUOTE
		|| ft_isdelimiter(data->prompt[*start]) == DQUOTE)
	{
		*end = end_quote(data->prompt, data->prompt[*start], *start + 1) + 1;
		tok_nodelimiter(data, index, start, end);
	}
	else if ((ft_isdelimiter(data->prompt[*start]) == INPUT
			&& ft_isdelimiter(data->prompt[*start + 1]) == INPUT)
		|| (ft_isdelimiter(data->prompt[*start]) == TRUNC
			&& ft_isdelimiter(data->prompt[*start + 1]) == TRUNC))
	{
		*end = end_quote(data->prompt, data->prompt[*start], *start + 1) + 1;
		tok_nodelimiter(data, index, start, end);
	}
	else if (ft_isdelimiter(data->prompt[*start]) == VAR)
	{
		*end = end_variable(data->prompt, *start + 1) + 1;
		tok_nodelimiter(data, index, start, end);
	}
	else if (ft_isdelimiter(data->prompt[*start]) == SPACES
		&& ft_isdelimiter(data->prompt[(*start) + 1]) == SPACES)
		(*start)++;
	else
		tok_delimiter(data, data->prompt, index, start);
}

/* Function that traverses the prompt looking for delimiters or 
   groups of words within quotes to separate the words into tokens, 
   each with its corresponding type. */
int	ft_tokenizer(t_data *d, int len, int start, int index)
{
	int	end;

	d->tokens = malloc(MAX_TOKENS * sizeof(t_tokens *));
	if (!d->tokens)
		ft_malloc(d, NULL, NULL);
	while (start < len)
	{
		end = start;
		if (ft_isdelimiter(d->prompt[start]))
			define_delimiter(d, &start, &end, &index);
		else
		{
			while (end < len && !ft_isdelimiter(d->prompt[end]))
				end++;
			tok_nodelimiter(d, &index, &start, &end);
		}
	}
	d->tokens[index] = NULL;
	d->tokens_qt = index;
	if (clean_quotes(d, NULL, 0, 0) == 1)
		return (1);
	return (0);
}
