/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:05:01 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/23 22:08:51 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	is_builtins_or_redir(t_token *tokens, int mode)
// {
// 	while (tokens && tokens->type != PIPE)
// 	{
// 		if (mode == 0 && tokens->type == CMD)
// 			return (is_builtins(tokens));
// 		if (mode == 1 && is_redir_token(tokens->type))
// 			return (1);
// 		tokens = tokens->next;
// 	}
// 	return (0);
// }

// static void	clean_exit(t_pipex *p, t_mini *mini, char **envp, int code)
// {
// 	close_all(p);
// 	ft_free_tab(envp);
// 	destroy_tab(mini->env);
// 	rb_free_all(mini->rb);
// 	free(mini->rb);
// 	exit(code);
// }

// static void	handle_dup(t_pipex *p, t_token *tokens)
// {
// 	while (tokens && tokens->type != PIPE)
// 	{
// 		if ((tokens->type == INPUT || tokens->type == HEREDOC)
// 			&& (p->fd_in < 0 || dup2(p->fd_in, STDIN_FILENO) == -1))
// 			(close_all(p), exit(1));
// 		if ((tokens->type == APPEND || tokens->type == TRUNC)
// 			&& (p->fd_out < 0 || dup2(p->fd_out, STDOUT_FILENO) == -1))
// 			(close_all(p), exit(1));
// 		tokens = tokens->next;
// 	}
// }

// static t_child_ctx	init_child_ctx(t_pipex *p, t_token *tokens,
// 									char **envp, t_mini *mini)
// {
// 	t_child_ctx	ctx;

// 	ctx.p = p;
// 	ctx.tokens = tokens;
// 	ctx.envp = envp;
// 	ctx.mini = mini;
// 	ctx.cmd_args = NULL;
// 	ctx.cmd_path = NULL;
// 	return (ctx);
// }

// void	ft_child_pro(t_pipex *p, t_token *tokens, char **envp, t_mini *mini)
// {
// 	t_child_ctx	ctx;
	
// 	int	is_builtin;
// 	int	has_redir;

// 	is_builtin = is_builtins_or_redir(tokens, 0);
// 	has_redir = is_builtins_or_redir(tokens, 1);
// 	ctx = init_child_ctx(p, tokens, envp, mini);
// 	if (handle_redirections(tokens, PIPE) < 0)
// 		(rb_free_all(mini->rb), free(mini->rb), exit(1));
// 	handle_dup(p, tokens);
// 	close(p->pipefd[0]);
// 	close(p->pipefd[1]);
// 	if (is_builtins_or_redir(tokens, 0))
// 		clean_exit(p, mini, envp, builtin_with_redir(tokens, mini, p));
// 	if (is_builtins_or_redir(tokens, 1))
// 		clean_exit(p, mini, envp, 0);
// 	ctx.cmd_args = token_to_cmd(&tokens, mini);
// 	if (!ctx.cmd_args || !ctx.cmd_args[0] || ctx.cmd_args[0][0] == '\0')
// 		(close_all(p), ft_free_tab(envp),
// 			ft_error_exit("Pipex: command not found\n"));
// 	ctx.cmd_path = find_cmd_path(ctx.cmd_args[0], mini);
// 	if (!ctx.cmd_path)
// 		(command_not_found(ctx.cmd_args[0]), clean_exit(p, mini, envp, 127));
// 	execve(ctx.cmd_path, ctx.cmd_args, envp);
// 	perror("execve");
// 	ft_free_tab(envp);
// 	free(ctx.cmd_path);
// 	exit(1);
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
void	ft_child_pro(t_pipex *p, t_token *tokens, char **envp, t_mini *mini)
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

