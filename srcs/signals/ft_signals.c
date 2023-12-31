/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahooghe <ahooghe@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:53:56 by ahooghe           #+#    #+#             */
/*   Updated: 2023/09/28 13:55:26 by ahooghe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_function(int signum, siginfo_t *siginfo, void *ptr)
{
	(void)ptr;
	if (signum == SIGINT)
	{
		if (siginfo->si_pid == 0)
		{
			if (g_mini.inside_heredoc == 1)
				g_mini.inside_heredoc = -1;
			else
				write(1, "\n", 1);
			if (g_mini.status_done == 0)
				g_mini.exit_status = 130;
		}
		else
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_mini.exit_status = 130;
		}
	}
}

void	ft_sigquit(int signum)
{
	if (signum == SIGQUIT)
	{
		if (g_mini.status_done == 0)
		{
			write(1, "Quit (core dumped)\n", 19);
			g_mini.exit_status = signum + 128;
		}
	}
}

void	ft_init_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handler_function;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &sa, 0) == -1)
		exit(1);
	signal(SIGQUIT, SIG_IGN);
}
