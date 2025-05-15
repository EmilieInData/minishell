/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:05:55 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/22 20:07:03 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Function to free arrays
void	ft_free(t_tokens **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		if (arr[i]->value)
			free(arr[i]->value);
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_free_flag(t_data *data, int flag)
{
	if (flag == 1 && data->current_dir)
	{
		free(data->current_dir);
		data->current_dir = NULL;
	}
	if (flag == 1 || flag == 2)
	{
		erase_lst(data->env_lst);
		if (flag == 1)
			exit(data->rt_value);
	}
	return ;
}

void	ft_free_data(t_data *data, int flag)
{
	if (data)
	{
		if (data->prompt)
		{
			free(data->prompt);
			data->prompt = NULL;
		}
		if (data->tokens)
		{
			ft_free(data->tokens);
			data->tokens = NULL;
		}
		if (data->sections)
		{
			ft_free_section(data->sections, NULL);
			data->sections = NULL;
		}
		ft_free_flag(data, flag);
	}
	return ;
}

//Write msn function
int	ft_msn(char *s, int fd)
{
	if (write(fd, s, ft_strlen(s)) == -1)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

//Check if character is a delimiter or a space
int	ft_isdelimiter(char c)
{
	if (ft_isspace(c))
		return (SPACES);
	else if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (INPUT);
	else if (c == '>')
		return (TRUNC);
	else if (c == '"')
		return (DQUOTE);
	else if (c == '\'')
		return (SQUOTE);
	else if (c == '\0')
		return (END);
	else if (c == '$')
		return (VAR);
	else if (c == '\\')
		return (BACKSLASH);
	else if (c == ';')
		return (SEMICOL);
	return (0);
}
