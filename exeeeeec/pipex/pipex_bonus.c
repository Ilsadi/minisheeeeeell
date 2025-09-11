/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:05:01 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/11 19:13:38 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_fd(t_pipex *pipex)
{
	if (pipex->fd_in < 0 || pipex->fd_out < 0)
	{
		close_all(pipex);
		exit(1);
	}
	if (dup2(pipex->fd_in, 0) == -1)
	{
		close_all(pipex);
		exit(1);
	}
	if (dup2(pipex->fd_out, 1) == -1)
	{
		close_all(pipex);
		exit(1);
	}
}

static void	ft_child_pro(t_pipex *p, char **cmd_args, char **envp, t_mini *mini)
{
	char	*cmd_path;

	if (!cmd_args || !cmd_args[0] || cmd_args[0][0] == '\0')
	{
		close_all(p);
		ft_free_tab(envp);
		ft_error_exit("Pipex: command not found\n");
	}
	cmd_path = find_cmd_path(cmd_args[0], mini);
	if (!cmd_path)
	{
		close_all(p);
		rb_free_all(mini->rb);
		ft_free_tab(envp);
		destroy_tab(mini->env);
		free(mini->rb);
		exit(127);
	}
	error_fd(p);
	close_all(p);
	execve(cmd_path, cmd_args, envp);
	perror("execve");
	free(cmd_path);
	exit(1);
}

static void	setup_pipe(t_pipex *pipex, t_token **current)
{
	if (*current && (*current)->type == PIPE)
	{
		if (pipe(pipex->pipefd) == -1)
			ft_error_exit("pipe error");
		pipex->fd_out = pipex->pipefd[1];
		*current = (*current)->next;
	}
	else
		pipex->fd_out = pipex->outfile;
}

void	ft_pipex_loop(t_pipex *pipex, t_token *tokens, t_mini *mini)
{
	char	**envp;
	t_token	*current;
	char	**current_cmd;

	pipex->fd_in = pipex->infile;
	envp = var_to_envp(mini->env);
	if (!envp)
		ft_error_exit("Error: var_to_envp");
	current = tokens;
	while (current)
	{
		handle_redirections(current, PIPE);
		current_cmd = token_to_cmd(&current, mini);
		setup_pipe(pipex, &current);
		pipex->pid1 = fork();
		if (pipex->pid1 == 0)
			ft_child_pro(pipex, current_cmd, envp, mini);
		close_test(pipex->fd_in);
		close_test(pipex->fd_out);
		if (current)
			pipex->fd_in = pipex->pipefd[0];
	}
	ft_free_tab(envp);
}

