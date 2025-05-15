/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:22:00 by esellier          #+#    #+#             */
/*   Updated: 2024/10/22 22:00:35 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins_exe(t_data *data, t_section *section)
{
	int	fd[2];

	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	if (!fd[0] || !fd[1])
		return (error_exe(data, "dup error", 2), data->rt_value);
	if (section->fd_in == -1 || section->fd_out == -1)
		return (1);
	if (section->fd_in != -2)
	{
		if (dup2(section->fd_in, STDIN_FILENO) == -1)
			return (error_exe(data, "dup2 error", 2));
		close (section->fd_in);
	}
	if (section->fd_out != -2 && ft_strcmp(section->cmd[0], "exit") != 0)
	{
		if (dup2(section->fd_out, STDOUT_FILENO) == -1)
			return (error_exe(data, "dup2 error", 2));
		close (section->fd_out);
	}
	data->rt_value = make_builtins(section->cmd, data, 0);
	exe_builtins_redi(data, fd[0], fd[1]);
	return (data->rt_value);
}

int	classic_exe(t_data *data, t_section *section)
{
	if (section->fd_in == -1 || section->fd_out == -1)
		exit (1);
	if (section->fd_in != -2)
	{
		if (dup2(section->fd_in, STDIN_FILENO) == -1)
			return (error_exe(data, "dup2 error", 3));
		close (section->fd_in);
	}
	if (section->fd_out != -2)
	{
		if (dup2(section->fd_out, STDOUT_FILENO) == -1)
			return (error_exe(data, "dup2 error", 3));
		close (section->fd_out);
	}
	close_fd_child(section);
	fd_null(data, section, 0);
	if (check_builtins(section->cmd) == 0)
		return (make_builtins(section->cmd, data, 1));
	section->path_array = lst_to_arr(data->env_lst, data, section->path_array);
	if (search_path(data, section->path_array, section) != 0)
		exit (data->rt_value);
	if (execve(section->path, section->cmd, section->path_array) == -1)
		exit (error_exe(data, section->cmd[0], 4));
	return (0);
}

void	free_array_int(int **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free (array[i]);
		i++;
	}
	free(array);
	return ;
}

int	ft_waitpid_status(t_section *section, t_data *data)
{
	int	**status;
	int	i;
	int	tmp;

	i = 0;
	status = (int **)malloc((data->sections_qt + 1) * sizeof (int *));
	while (section)
	{
		if (section->pid != -2)
		{
			status[i] = (int *)malloc(sizeof (int));
			if (!status[i])
				ft_malloc(data, NULL, NULL);
			waitpid(section->pid, status[i], 0);
			i++;
		}
		section = section->next;
	}
	status[i] = NULL;
	if (i == 0)
		return (free(status), data->rt_value);
	tmp = status[i - 1][0];
	if (WIFEXITED(tmp))
		return (free_array_int(status), WEXITSTATUS(tmp));
	return (free_array_int(status), WTERMSIG(tmp));
}

int	execution(t_data *data, t_section *section)
{
	if (data->sections_qt == 1 && section->cmd
		&& check_builtins(section->cmd) == 0)
		return (builtins_exe(data, section), data->rt_value);
	while (section)
	{
		if (section->cmd)
		{
			section->pid = fork();
			if (section->pid < 0)
				error_exe(data, "fork error", 2);
			if (section->pid == 0)
				data->rt_value = classic_exe(data, section);
			if (data->rt_value == -1)
				ft_free_data(data, 1);
		}
		close_fd(section);
		section = section->next;
	}
	data->rt_value = ft_waitpid_status(data->sections, data);
	return (data->rt_value);
}
