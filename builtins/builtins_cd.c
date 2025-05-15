/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:17:55 by esellier          #+#    #+#             */
/*   Updated: 2024/10/22 20:56:05 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_free_cd(t_data *data, char *old, char *new, int i)
{
	if (i == 1)
	{
		write(2, "cd: error retrieving current directory: getcwd: cannot ", 56);
		write(2, "access parent directories: No such file or directory\n", 53);
	}
	if (old)
	{
		free (old);
		old = NULL;
	}
	if (new)
	{
		free (new);
		new = NULL;
	}
	if (i == 0)
		ft_malloc(data, NULL, NULL);
	return ;
}

int	change_pwd(t_data *data, char *old, char *new, char **str)
{
	t_env	*current;
	t_env	*previous;

	if (getcwd(new, 256) == 0 && str[1] && str[1][1] == '.')
		return (ft_free_cd(NULL, old, new, 1), 0);
	current = search_str("PWD", data);
	previous = search_str("OLDPWD", data);
	if (previous)
	{
		free (previous->value);
		previous->value = ft_strdup(old);
		if (!previous->value)
			ft_free_cd(data, old, new, 0);
	}
	if (current)
	{
		free (current->value);
		current->value = ft_strdup(new);
		if (!current->value)
			ft_free_cd(data, old, new, 0);
	}
	free (old);
	change_cd_data(data, new);
	free (new);
	return (0);
}

int	cd_home(char **str, t_data *data, char *old_buf, char *new_buf)
{
	char	*tmp;

	tmp = getenv("HOME");
	if (!str[1] && (!tmp || search_str("HOME", data) == 0))
	{
		free (old_buf);
		free (new_buf);
		return (print_errors(str, data, 1), 1);
	}
	if (chdir(tmp) == 0)
		return (change_pwd(data, old_buf, new_buf, str));
	else
		perror("chdir error: ");
	free (old_buf);
	free (new_buf);
	return (1);
}

int	make_cd(char **str, t_data *data)
{
	char	*old_buf;
	char	*new_buf;

	if (str[1] && str[2])
		return (print_errors(str, data, 0), 1);
	old_buf = ft_strdup(data->current_dir);
	if (!old_buf)
		ft_malloc(data, NULL, NULL);
	new_buf = ft_calloc(1, 256);
	if (!new_buf)
	{
		free (old_buf);
		ft_malloc(data, NULL, NULL);
	}
	if (!str[1] || (str[1] && str[1][0] == '~'))
		return (cd_home(str, data, old_buf, new_buf));
	if (check_dir_cd(str) == 1)
		return (ft_free_cd(data, old_buf, new_buf, 2), 1);
	if (chdir(str[1]) != 0)
		return (ft_free_cd(data, old_buf, new_buf, 1), 0);
	if (change_pwd(data, old_buf, new_buf, str) == 1)
		ft_malloc(data, NULL, NULL);
	return (0);
}

/*getcwd = get the actual address (even if PWD is unset)
chdir = go to the directory in arguments
getenv = search and return a specific line in the environnement*/