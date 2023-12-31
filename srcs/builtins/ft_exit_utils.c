/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahooghe <ahooghe@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:53:56 by ahooghe           #+#    #+#             */
/*   Updated: 2023/09/28 16:13:56 by ahooghe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_utils(int status, int no_exit_written, t_minishell *mini)
{
	(void)no_exit_written;
	if (g_mini.status_done == 0 && mini->cmd.final_cmd == 1)
	{
		g_mini.exit_status = status;
		g_mini.status_done = 1;
	}
	if ((mini->cmd.inside_pipe == 1
			&& ft_strcmp("exit", mini->cmd.argv[0]) != 0)
		|| ft_strcmp("exit", mini->cmd.argv[0]) == 0
		|| ft_strcmp("echo", mini->cmd.argv[0]) == 0
		|| ft_strcmp("pwd", mini->cmd.argv[0]) == 0
		|| (ft_strcmp("export", mini->cmd.argv[0]) == 0
			&& mini->cmd.argc == 1)
		|| ft_strcmp("env", mini->cmd.argv[0]) == 0)
	{
		ft_free_all_exec(mini);
		exit(status);
	}
}

int	ft_check_all_digits(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (-1);
		str++;
	}
	return (0);
}

void	ft_error_numeric(char *builtin, char *identifier)
{
	write(2, builtin, ft_strlen(builtin));
	write(2, ": ", 2);
	write(2, identifier, ft_strlen(identifier));
	write(2, ": numeric argument required\n", 28);
}

int	ft_check_numeric_arg(t_minishell *mini)
{
	if (ft_check_all_digits(mini->cmd.argv[1]) == -1)
	{
		if (mini->cmd.inside_pipe != 1)
			write(2, "exit\n", 5);
		ft_error_numeric("exit", mini->cmd.argv[1]);
		ft_exit_utils(2, 1, mini);
		return (-1);
	}
	return (0);
}
