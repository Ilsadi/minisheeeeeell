/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:55:35 by cbrice            #+#    #+#             */
/*   Updated: 2025/09/27 19:59:07 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	send_newline_to_readline(void)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return ;
	write(fd[1], "\n", 1);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}

void	sigint_heredoc_handler(int sig)
{
	(void)sig;
	send_newline_to_readline();
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_state = STATE_SIGINT;
}

void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_heredoc_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

int	handle_heredoc_interrupt(int *pipefd, int *last_heredoc_pipe)
{
	close(pipefd[1]);
	if (*last_heredoc_pipe != -1)
		close(*last_heredoc_pipe);
	*last_heredoc_pipe = -1;
	g_state = STATE_IDLE;
	setup_child_signals();
	return (-2);
}
