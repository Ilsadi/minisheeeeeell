/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:05:01 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/20 20:20:48 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	error_fd(t_pipex *pipex)
// {

// 	if (pipex->fd_in < 0 || pipex->fd_out < 0)
// 	{
// 		close_all(pipex);
// 		exit(1);
// 	}
// 	if (dup2(pipex->fd_in, 0) == -1)
// 	{
// 		close(pipex->fd_in);
// 		pipex->fd_in = 0;
// 		close_all(pipex);
// 		exit(1);
// 	}
// 	if (dup2(pipex->fd_out, 1) == -1)
// 	{
// 		pipex->fd_out = 1;
// 		close_all(pipex);
// 		exit(1);
// 	}
// 	close(pipex->pipefd[0]);
// 	close(pipex->pipefd[1]);
// }

static int	is_builtins_pipe(t_token *tokens)
{
	while (tokens && tokens->type != CMD && tokens->type != PIPE)
		tokens = tokens->next;
	return (is_builtins(tokens));
}

static int redirection_before_pipe(t_token *tokens)
{
    while (tokens && tokens->type != PIPE)
    {
        if (is_redir_token(tokens->type))
            return 1;
        tokens = tokens->next;
    }
    return 0;
}

int	has_input_redirection(t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == INPUT || tokens->type == HEREDOC)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}
int	has_output_redirection(t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == APPEND || tokens->type == TRUNC)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}
static void	ft_child_pro(t_pipex *p, t_token *tokens, char **envp, t_mini *mini)
{
	char	*cmd_path;
	char	**cmd_args;
	int		exit_builtins;
	int		redir_only_before_pipe;
	int		redir_only;

	// error_fd(p);
	if (handle_redirections(tokens, PIPE) < 0)
		return (rb_free_all(mini->rb), free(mini->rb), exit(1));

	if (!has_input_redirection(tokens))
	{
		if (p->fd_in < 0)
		{
			close_all(p);
			exit(1);
		}
		if (dup2(p->fd_in, STDIN_FILENO) == -1)
		{
			close(p->fd_in);
			close_all(p);
			exit(1);
		}
	}

	if (!has_output_redirection(tokens))
	{
		if (p->fd_out < 0)
		{
			close_all(p);
			exit(1);
		}
		if (dup2(p->fd_out, STDOUT_FILENO) == -1)
		{
			close_all(p);
			exit(1);
		}
	}
	close(p->pipefd[0]);
	close(p->pipefd[1]);
	
	// error_fd(p);
	if (is_builtins_pipe(tokens))
	{
		ft_free_tab(envp);
		close_all(p);
		exit_builtins = builtin_with_redir(tokens, mini, p);
		destroy_tab(mini->env);
		rb_free_all(mini->rb);
		free(mini->rb);
		exit (exit_builtins);
	}
	if (redirection_before_pipe(tokens))
		redir_only_before_pipe = 1;
	else
    	redir_only_before_pipe = 0;
	redir_only = redirection_before_pipe(tokens);
	cmd_args = token_to_cmd(&tokens, mini);
	if (!cmd_args || !cmd_args[0] || cmd_args[0][0] == '\0')
	{
        if (redir_only)
        {
            // simplement fermer les fd, libérer, quitter enfant avec code 0
            close_all(p);
            ft_free_tab(envp);
            destroy_tab(mini->env);
            rb_free_all(mini->rb);
            free(mini->rb);
            exit(0);
        }
        else
        {
            close_all(p);
            ft_free_tab(envp);
            ft_error_exit("Pipex: command not found\n");
        }
	}
	cmd_path = find_cmd_path(cmd_args[0], mini);
	if (!cmd_path)
	{
		command_not_found(*cmd_args);
		close_all(p);
		rb_free_all(mini->rb);
		ft_free_tab(envp);
		destroy_tab(mini->env);
		free(mini->rb);
		exit(127);
	}
	execve(cmd_path, cmd_args, envp);
	perror("execve");
	ft_free_tab(envp);
	free(cmd_path);
	exit(1);
}

static void	setup_pipe(t_pipex *pipex, int to_pipe)
{
	if (to_pipe)
	{
		if (pipe(pipex->pipefd) == -1)
			ft_error_exit("pipe error");
		pipex->fd_out = pipex->pipefd[1];
	}
	else
		pipex->fd_out = pipex->outfile;
}

static void	advance_until_pipe(t_token **current)
{
	while (*current && (*current)->type != PIPE)
		*current = (*current)->next;
	if (*current)
		*current = (*current)->next;
}

void	ft_pipex_loop(t_pipex *pipex, t_token *tokens, t_mini *mini, pid_t *tab_pid)
{
	char	**envp;
	t_token	*current;
	int		i;
	int		number_of_pipes;

	i = 0;
	number_of_pipes = has_pipe(mini->first);
	pipex->fd_in = pipex->infile;
	envp = var_to_envp(mini->env);
	if (!envp)
		ft_error_exit("Error: var_to_envp");
	current = tokens;
	while (current)
	{
		setup_pipe(pipex, i < number_of_pipes);
		pipex->pid1 = fork();
		if (pipex->pid1 == 0)
			ft_child_pro(pipex, current, envp, mini);
		tab_pid[i] = pipex->pid1;
		advance_until_pipe(&current);
		close_test(pipex->fd_in);
		close_test(pipex->fd_out);
		if (current)
			pipex->fd_in = pipex->pipefd[0];
		i++;
	}
	ft_free_tab(envp);
}

// void	ft_pipex_loop(t_pipex *pipex, t_token *tokens, t_mini *mini, pid_t *tab_pid)
// {
// 	char	**envp;
// 	t_token	*current;
// 	int		i;
// 	int		number_of_pipes;

// 	i = 0;
// 	number_of_pipes = has_pipe(mini->first);
// 	pipex->fd_in = pipex->infile;
// 	envp = var_to_envp(mini->env);
// 	if (!envp)
// 		ft_error_exit("Error: var_to_envp");
// 	current = tokens;
// 	while (current)
// 	{
// 		t_token *segment_start = current;
// 		t_token *segment_end = current;

// 		// Avance jusqu’au prochain pipe ou fin
// 		while (segment_end && segment_end->type != PIPE)
// 			segment_end = segment_end->next;

// 		// On isole le segment en coupant temporairement
// 		if (segment_end)
// 		{
// 			t_token *next = segment_end->next;
// 			segment_end->next = NULL;

// 			setup_pipe(pipex, i < number_of_pipes);
// 			pipex->pid1 = fork();
// 			if (pipex->pid1 == 0)
// 				ft_child_pro(pipex, segment_start, envp, mini);
// 			tab_pid[i] = pipex->pid1;

// 			segment_end->next = next; // restaure la liste
// 			current = next;
// 		}
// 		else
// 		{
// 			setup_pipe(pipex, i < number_of_pipes);
// 			pipex->pid1 = fork();
// 			if (pipex->pid1 == 0)
// 				ft_child_pro(pipex, segment_start, envp, mini);
// 			tab_pid[i] = pipex->pid1;

// 			current = NULL;
// 		}
// 		close_test(pipex->fd_in);
// 		close_test(pipex->fd_out);
// 		if (current)
// 			pipex->fd_in = pipex->pipefd[0];
// 		i++;
// 	}
// 	ft_free_tab(envp);
// }

