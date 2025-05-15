/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_section_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:55:46 by esellier          #+#    #+#             */
/*   Updated: 2024/10/22 20:13:24 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_red(t_red *red, t_red *prev)
{
	while (red)
	{
		prev = red;
		if (red->file)
			free(red->file);
		red = red->next;
		free(prev);
	}
	return ;
}

void	ft_free_section(t_section *section, t_section *previous)
{
	t_red		*red;
	t_red		*prev;

	while (section)
	{
		red = NULL;
		previous = section;
		if (section->files)
			red = section->files;
		if (section->cmd)
			free_array(section->cmd);
		prev = red;
		do_red(red, prev);
		if (section->path_array)
			free_array(section->path_array);
		if (section->path)
			free(section->path);
		close_fd(section);
		section = section->next;
		free(previous);
	}
}

void	close_fd(t_section *section)
{
	if (section->fd_out)
		close (section->fd_out);
	if (section->fd_in)
		close (section->fd_in);
	return ;
}

void	close_fd_child(t_section *section)
{
	t_section	*current;

	if (!section->next)
		return ;
	current = section->next;
	while (current)
	{
		close_fd(current);
		current = current->next;
	}
	return ;
}
