/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:17:55 by esellier          #+#    #+#             */
/*   Updated: 2024/10/15 21:43:55 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_builtins(char **str, t_data *data, int flag)
{
	int	temp;

	temp = 0;
	if (ft_strcmp("echo", str[0]) == 0)
		make_echo(str);
	else if (ft_strcmp("cd", str[0]) == 0)
		temp = make_cd(str, data);
	else if (ft_strcmp("pwd", str[0]) == 0)
		temp = make_pwd(data);
	else if (ft_strcmp("export", str[0]) == 0)
		make_export(str, data);
	else if (ft_strcmp("unset", str[0]) == 0)
		make_unset(str, data);
	else if (ft_strcmp("env", str[0]) == 0)
		temp = make_env(data, str);
	else if (ft_strcmp("exit", str[0]) == 0)
		temp = make_exit(str, data);
	data->rt_value = temp;
	if (flag == 1)
		exit(data->rt_value);
	return (data->rt_value);
}

int	exit_number(char **str, t_data *data)
{
	long long	num;

	num = ft_atoi(str[1]);
	if (!str[2])
	{
		if (num < 0)
			num = modulo_negativ(num);
		if (num > 255)
			num = num % 256;
		write(1, "exit\n", 5);
		ft_free_data(data, 2);
		exit (num);
	}
	else
	{
		write (1, "exit\n", 5);
		write(2, "minishell : exit: too many arguments\n", 37);
		return (data->rt_value = 1, 1);
	}
	return (0);
}

int	make_exit(char **str, t_data *data)
{
	if (!str[1] || (ft_strncmp(str[1], "0", 1) == 0 && !str[2]))
	{
		write(1, "exit\n", 5);
		ft_free_data(data, 2);
		exit (0);
	}
	if (str[1])
	{
		if (check_minmax(str[1]) == 0)
		{
			if (exit_number(str, data) == 1)
				return (1);
		}
		else
		{
			write(1, "exit\n", 5);
			write(2, "minishell : exit: ", 18);
			write(2, &(*str[1]), ft_strlen(str[1]));
			write(2, ": numeric argument required\n", 28);
			ft_free_data(data, 2);
			exit (2);
		}
	}
	return (0);
}

int	check_echo(char **str, int i)
{
	int	j;

	if (ft_strncmp(str[i], "-n", 2) == 0)
	{
		j = 2;
		while (str[i][j] == 'n')
			j++;
		if (str[i][j] == '\0')
			return (0);
		else
			return (1);
	}
	return (1);
}

void	make_echo(char **str)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	while (str[i])
	{
		if (check_echo(str, i) == 1)
			break ;
		else
			flag = 1;
		i++;
	}
	while (str[i])
	{
		write (1, str[i], ft_strlen(str[i]));
		if (str[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
	return ;
}
