/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:03:19 by esellier          #+#    #+#             */
/*   Updated: 2024/10/22 22:02:01 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_arg(char *arg)
{
	write(2, "minishell: ", 12);
	write(2, arg, ft_strlen(arg));
	return ;
}

int	check_dir(char *arg)
{
	DIR		*dir;

	dir = opendir(arg);
	if (dir)
	{
		closedir(dir);
		write_arg(arg);
		return (write(2, ": Is a directory\n", 17), 126);
	}
	if (access(arg, F_OK) == 0)
	{
		write_arg(arg);
		return (write(2, ": Permission denied\n", 20), 126);
	}
	else if (ft_strchr(arg, '/') == 0)
	{
		write(2, arg, ft_strlen(arg));
		return (write(2, ": command not found\n", 20), 127);
	}
	else
	{
		write_arg(arg);
		return (write(2, ": No such file or directory\n", 28), 127);
	}
}

int	error_exe(t_data *data, char *arg, int i)
{
	if (i == 0 || i == 2 || i == 3)
		write(2, "minishell: ", 12);
	if (i == 0 || i == 1)
	{
		write(2, arg, ft_strlen(arg));
		if (i == 0)
			write(2, ": No such file or directory\n", 28);
		if (i == 1)
			write(2, ": command not found\n", 20);
		return (data->rt_value = 127, 127);
	}
	if (i == 2 || i == 3)
		perror(arg);
	if (i == 2)
		ft_free_data(data, 1);
	if (i == 3)
	{
		ft_free_data(data, 0);
		erase_lst(data->env_lst);
		exit (-1);
	}
	if (i == 4)
		return (check_dir(arg));
	return (data->rt_value = 1, 1);
}

int	access_errors(char *file, t_data *data, int fd, int i)
{
	if (i == 0)
		fd = open(file, O_RDONLY);
	if (i == 1)
		fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	write(2, "minishell : ", 12);
	write(2, file, ft_strlen(file));
	write(2, ": Permission denied\n", 20);
	data->rt_value = 1;
	return (fd);
}
