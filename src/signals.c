/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:38:07 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/10 23:44:16 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	readline_sigint_handler(int signum)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_signal_num = 128 + signum;
}

void	readline_sigquit_handler(int signum)
{
	(void) signum;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \b\b", STDOUT_FILENO);
	g_signal_num = 0;
}
