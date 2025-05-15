/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:17:55 by esellier          #+#    #+#             */
/*   Updated: 2024/10/22 21:24:41 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	write_errors_cd(char **str, char *arg)
{
	write(2, "minishell : ", 12);
	write(2, str[0], ft_strlen(str[0]));
	write(2, ": ", 2);
	write(2, str[1], ft_strlen(str[1]));
	write(2, arg, ft_strlen(arg));
	return ;
}

int	check_dir_cd(char **str)
{
	struct stat	file;

	if (ft_strcmp(str[1], ".") == 0 || ft_strcmp(str[1], "..") == 0)
		return (0);
	if (stat(str[1], &file) == -1)
		return (write_errors_cd(str, ": No such file or directory\n"), 1);
	if (S_ISDIR(file.st_mode))
	{
		if (access(str[1], X_OK) != 0)
			return (write_errors_cd(str, ": Permission denied\n"), 1);
		return (0);
	}
	if (access(str[1], F_OK) == 0)
		return (write_errors_cd(str, ": Not a directory\n"), 1);
	return (0);
}
