/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:05:01 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/24 21:09:05 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtins_pipe(t_token *tokens)
{
	while (tokens && tokens->type != CMD && tokens->type != PIPE)
		tokens = tokens->next;
	return (is_builtins(tokens));
}

void	ft_child_pro(t_pipex *p, t_token *tokens, char **envp, t_mini *mini)
{
	char	*cmd_path;
	char	**cmd_args;
	int		redir_only;

	setup_child_signals();
	child_prepare_io(p, tokens, mini);
	if (is_builtins_pipe(tokens))
		clean_exit(p, mini, envp, builtin_with_redir(tokens, mini, p));
	redir_only = redirection_before_pipe(tokens);
	cmd_args = token_to_cmd(&tokens, mini);
	if (!cmd_args || !cmd_args[0] || cmd_args[0][0] == '\0')
	{
		if (redir_only)
			clean_exit(p, mini, envp, 0);
		else
			clean_exit(p, mini, envp, 127);
		return ;
	}
	cmd_path = find_cmd_path(cmd_args[0], mini);
	if (!cmd_path)
		(command_not_found(*cmd_args), clean_exit(p, mini, envp, 127));
	execve(cmd_path, cmd_args, envp);
	perror("execve");
	ft_free_tab(envp);
	free(cmd_path);
	exit(1);
}
