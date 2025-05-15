/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:45:21 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/22 23:13:47 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function that prints a different error for each type of delimiter token. */
void	print_err(int check)
{
	if (check == 2)
		ft_msn(ERR_PIPE, 2);
	else if (check == 3)
		ft_msn(ERR_INPUT, 2);
	else if (check == 4)
		ft_msn(ERR_TRUNC, 2);
	else if (check == 7)
		ft_msn(ERR_HEREDOC, 2);
	else if (check == 8)
		ft_msn(ERR_APPEND, 2);
}

/* Function that returns the type of token that is detected. */
int	check_type(int type)
{
	int	check;

	check = -1;
	if (type == INPUT)
		check = type;
	else if (type == TRUNC)
		check = type;
	else if (type == HEREDOC)
		check = type;
	else if (type == APPEND)
		check = type;
	else if (type == PIPE)
		check = type;
	if (check != -1)
	{
		print_err(check);
		return (1);
	}
	return (0);
}

void	write_msn(t_data *data, char *value)
{
	write(2, "minishell: ", 11);
	write(2, value, ft_strlen(value));
	write(2, ": ambiguous redirect\n", 21);
	data->rt_value = 1;
}

int	verify_previous_type(t_data *d, int i, char *value, int flag)
{
	if (i == 0)
		return (3);
	if (d->tokens[i - 1] != NULL && d->tokens[i - 1]->type == SPACES)
	{
		if (d->tokens[i - 2] && (d->tokens[i - 2]->type == INPUT
				|| d->tokens[i - 2]->type == TRUNC
				|| d->tokens[i - 2]->type == APPEND))
		{
			if (flag == 1)
				return (write_msn(d, value), 1);
			return (0);
		}
		else if (d->tokens[i - 2] && (d->tokens[i - 2]->type == HEREDOC))
			return (2);
	}
	else if (d->tokens[i - 1]->type == INPUT || d->tokens[i - 1]->type == TRUNC
		|| d->tokens[i - 1]->type == APPEND)
	{
		if (flag == 1)
			return (write_msn(d, value), 1);
		return (0);
	}
	else if (d->tokens[i - 1] && (d->tokens[i - 1]->type == HEREDOC))
		return (2);
	return (0);
}

/* Function that checks the next type of token to avoid 
having tokens of the same type together when Bash returns an error. */
int	verify_next_type(t_data *d)
{
	int	i;

	i = 0;
	while (d->tokens[i])
	{
		if (d->tokens[i]->type == INPUT || d->tokens[i]->type == TRUNC
			|| d->tokens[i]->type == HEREDOC || d->tokens[i]->type == APPEND)
		{
			if (d->tokens[i + 1] && check_type(d->tokens[i + 1]->type) == 1)
			{
				d->rt_value = 2;
				return (1);
			}
		}
		else if ((d->tokens[i]->type == PIPE)
			&& (d->tokens[i + 1]->type == PIPE))
		{
			ft_msn(ERR_PIPE, 2);
			d->rt_value = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
