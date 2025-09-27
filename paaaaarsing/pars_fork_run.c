/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_fork_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:45:32 by cbrice            #+#    #+#             */
/*   Updated: 2025/09/27 20:45:54 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_child_branch(t_mini *mini)
{
	setup_child_signals();
	ft_commands(mini);
	exit(3);
}

void	run_parent_branch(t_mini *mini, pid_t pid)
{
	int	status;
	int	sig;

	sig = 0;
	status = 0;
	setup_parent_signals();
	waitpid(pid, &status, 0);
	if (g_state == STATE_SIGINT)
		sig = 2;
	g_state = STATE_IDLE;
	if (WIFEXITED(status))
		mini->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		mini->exit_status = 128 + sig;
		if (sig == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		else if (sig == SIGINT)
			write(2, "\n", 1);
	}
	if (sig)
		mini->exit_status = 128 + sig;
	setup_signals();
}
