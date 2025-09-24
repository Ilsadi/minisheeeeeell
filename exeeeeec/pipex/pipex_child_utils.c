/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 20:21:27 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/24 20:04:42 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_with_rb(t_mini *mini, int code)
{
	rb_free_all(mini->rb);
	free(mini->rb);
	exit(code);
}

void	clean_exit(t_pipex *p, t_mini *mini, char **envp, int code)
{
	close_all(p);
	ft_free_tab(envp);
	destroy_tab(mini->env);
	rb_free_all(mini->rb);
	free(mini->rb);
	exit(code);
}

void	child_prepare_io(t_pipex *p, t_token *tokens, t_mini *mini)
{
	if (handle_redirections(tokens, PIPE) < 0)
		exit_with_rb(mini, 1);
	if (!has_input_redirection(tokens))
	{
		if (p->fd_in < 0)
			(close_all(p), exit(1));
		if (dup2(p->fd_in, STDIN_FILENO) == -1)
			(close(p->fd_in), close_all(p), exit(1));
	}
	if (!has_output_redirection(tokens))
	{
		if (p->fd_out < 0)
			(close_all(p), exit(1));
		if (dup2(p->fd_out, STDOUT_FILENO) == -1)
			(close_all(p), exit(1));
	}
	close(p->pipefd[0]);
	close(p->pipefd[1]);
}
