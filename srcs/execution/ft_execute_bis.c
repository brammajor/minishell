/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahooghe   <ahooghe@student.s19.be   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:53:56 by ahooghe           #+#    #+#             */
/*   Updated: 2023/09/28 13:43:52 by ahooghe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_before_launch_pipeline(t_minishell *mini)
{
	t_data_env	*data_env;

	data_env = &mini->data_env;
	data_env->stdin = dup(STDIN_FILENO);
	if (data_env->stdin == -1)
		ft_error(1, mini);
	data_env->stdout = dup(STDOUT_FILENO);
	if (data_env->stdout == -1)
		ft_error(1, mini);
	mini->cmd.old_pipefd[0] = -2;
	mini->cmd.old_pipefd[1] = -2;
	mini->cmd.pid = 0;
}

int	ft_init_pipe_before(t_cmd *cmd)
{
	if (cmd->pipe == 1)
		return (1);
	else
		return (0);
}

void	ft_restore_before_next_prompt(t_minishell *mini)
{
	t_data_env	*data_env;

	data_env = &mini->data_env;
	if (dup2(data_env->stdin, STDIN_FILENO) == -1)
		ft_error(1, mini);
	ft_close(&data_env->stdin);
	if (dup2(data_env->stdout, STDOUT_FILENO) == -1)
		ft_error(1, mini);
	ft_close(&data_env->stdout);
	ft_close_all_fds(mini);
	unlink("/tmp/.hdoc.txt");
	ft_free_cmd(&mini->cmd);
	g_mini.inside_heredoc = 0;
}
