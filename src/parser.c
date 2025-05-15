/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:44:10 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/10 21:55:59 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function that searches for the same type of quote as char c 
   (double or single quote) and returns the counter, which indicates 
   the position where the find_pipe function should continue advancing. */
int	end_quote(char *input, char c, int i)
{
	while (input[i] != '\0')
	{
		if (input[i] == c)
			return (i);
		i++;
	}
	return (i);
}

/* First, it checks the beginning of the prompt for a pipe and returns an error 
if it finds a quote. It then advances to the corresponding closing quote, 
since a pipe inside quotes is printable and not a delimiter. 
If it finds a pipe afterward, it analyzes the next character; 
if it is the end of the string or another pipe, it returns an error. 
If the function has not exited due to an error and has found a pipe, 
it will count it and return the total number of pipes. 
I cannot perform the check for multiple pipes that returns an error 
because it would exceed the line limit. */
int	find_pipes(char *input)
{
	int	i;

	i = 0;
	if (input && input[0] == '|')
	{
		ft_msn(ERR_PIPE, 2);
		return (1);
	}
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '"')
			i = end_quote(input, input[i], i + 1);
		if (input[i] == '|' && (input[i + 1] == '|' || input[i + 1] == '\0'))
		{
			ft_msn(ERR_PIPE, 2);
			return (1);
		}
		i++;
	}
	return (0);
}

/* Function that searches for the next quote of the same type as quote_type. 
*i+1 is used because *i is already on the first quote, 
and it is passed as a pointer to advance the counter
in the find_quotes function. */
int	find_pair_quote(char *input, int *i, char quote_type)
{
	int	n;

	n = 1;
	while (input[*i + 1] && input[*i + 1] != quote_type)
		(*i)++;
	if (input[*i + 1] == quote_type)
		n++;
	(*i)++;
	return (n);
}

/* Iterates through the prompt and, when it finds a quote (of any type), 
looks for its corresponding closing quote. If it doesn't find one, 
the variables squote or dquote will remain odd, resulting in an 
unmatched dquote which we return as an error. 
Odd quotes within other quotes are respected since the counter i 
is passed as a pointer. */
int	find_quotes(char *input, int squote, int dquote)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
			squote += find_pair_quote(input, &i, input[i]);
		else if (input[i] == '"')
			dquote += find_pair_quote(input, &i, input[i]);
		if (squote % 2 != 0)
		{
			ft_msn(ERR_SQUOTE, 1);
			return (1);
		}
		else if (dquote % 2 != 0)
		{
			ft_msn(ERR_DQUOTE, 2);
			return (1);
		}
		i++;
	}
	return (0);
}

/* 1 - Checks that input exists and then removes leading and trailing spaces 
from the input using ft_strtrim.
2 - Ensures that quotes, whether double or single, are properly closed.
3 - Verifies that there are no pipes at the beginning or end of the input. 
Pipes in the middle are accepted, but those inside quotes are treated 
as plain text rather than pipes. */

int	ft_parser(t_data *data)
{
	if (find_quotes(data->prompt, 0, 0) == 1
		|| find_pipes(data->prompt) == 1
		|| find_others(data->prompt) == 1)
	{
		data->rt_value = 2;
		return (1);
	}
	return (0);
}
