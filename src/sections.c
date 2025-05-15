/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 23:27:18 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/09 17:48:17 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to create the nodes for the sections */
t_section	*create_node(t_data *data)
{
	t_section	*node;

	node = malloc(sizeof(t_section));
	if (!node)
		ft_malloc(data, NULL, NULL);
	node->cmd = NULL;
	node->files = NULL;
	node->path_array = NULL;
	node->path = NULL;
	node->flag = -2;
	node->pid = -2;
	node->fd_in = -2;
	node->fd_out = -2;
	node->next = NULL;
	return (node);
}

void	add_redir(t_section *temp_section, t_data *data, int *i)
{
	if (!temp_section->files)
		add_first_redir(temp_section, data->tokens, i, data);
	else
		add_rest_redir(temp_section, data->tokens, i, data);
}

int	ft_isredir(int type)
{
	if (type == INPUT || type == TRUNC || type == APPEND || type == HEREDOC)
		return (1);
	return (0);
}

/* Initializes the sections list if it does not exist.*/
void	init_sections(t_data *data)
{
	if (!data->sections)
		data->sections = create_node(data);
}

/* Function that calls the one that separates the input into commands. 
If it finds a redirection, it saves the type of redirection and assigns 
the name of the following file, and then separates into sections 
when it encounters a pipe. */
void	ft_sections(t_data *data)
{
	int			i;
	t_section	*temp_section;

	i = 0;
	init_sections(data);
	data->sections_qt = 1;
	temp_section = data->sections;
	while (data->tokens[i])
	{
		if (ft_isredir(data->tokens[i]->type))
			add_redir(temp_section, data, &i);
		else if (data->tokens[i]->type == ARG || data->tokens[i]->type == CMD
			|| data->tokens[i]->type == NOEXP)
			temp_section->cmd = add_arg(temp_section, data->tokens[i]->value,
					data);
		else if (data->tokens[i]->type == PIPE)
		{
			temp_section->next = create_node(data);
			if (!temp_section->next)
				exit(EXIT_FAILURE);
			temp_section = temp_section->next;
			data->sections_qt++;
		}
		i++;
	}
}
