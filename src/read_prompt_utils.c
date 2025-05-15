/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_prompt_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 21:11:35 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/10 21:56:06 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function that removes leading and trailing spaces from the prompt */
void	trim_prompt(t_data *data)
{
	char	*trim_input;

	trim_input = ft_strtrim(data->prompt, " ");
	if (!trim_input)
		ft_malloc(data, NULL, NULL);
	free(data->prompt);
	data->prompt = trim_input;
}

int	find_not_allowed_type(t_data *data)
{
	int	i;

	i = 0;
	while (data->tokens[i])
	{
		if (data->tokens[i]->type == SEMICOL)
		{
			ft_msn(ERR_SEMICOL, 2);
			data->rt_value = 2;
			return (1);
		}
		else if (data->tokens[i]->type == BACKSLASH)
		{
			ft_msn(ERR_BACKSLASH, 2);
			data->rt_value = 2;
			return (1);
		}
		i++;
	}
	return (0);
}

int	verify_num_heredoc(t_data *data)
{
	int	i;
	int	heredoc;

	i = 0;
	heredoc = 0;
	while (data->tokens[i])
	{
		if (data->tokens[i]->type == HEREDOC)
			heredoc++;
		i++;
	}
	if (heredoc > 16)
	{
		ft_msn(MAX_HEREDOC, 2);
		return (1);
	}
	else
		return (0);
}
