/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 00:08:32 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/11 00:08:33 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sigint_handler(int signum)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	g_signal_num = 128 + signum;
	exit(g_signal_num);
}

void	heredoc_sigquit_handler(int signum)
{
	g_signal_num = 128 + signum;
}
