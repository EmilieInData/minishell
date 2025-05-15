/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:46:03 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/10 23:46:04 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_sigint_handler(int signum)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	g_signal_num = 128 + signum;
}

void	exe_sigquit_handler(int signum)
{
	ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
	g_signal_num = 128 + signum;
}
