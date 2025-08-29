/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:11:30 by ilsadi            #+#    #+#             */
/*   Updated: 2025/08/29 16:12:23 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_commands(t_mini *mini)
{
	char	*cmd_path;
	char	**cmd_args;
	char	**env;

	env = var_to_envp(mini->env);
	if (!env)
		ft_error_exit("Error creating environment\n");
	if (handle_redirections(mini->first) < 0)
	{
		ft_free_tab(env);
		exit(1);
	}
	cmd_args = token_to_cmd(&mini->first, mini);
	if (!cmd_args || !cmd_args[0] || cmd_args[0][0] == '\0')
	{
		destroy_tab(mini->env);
		ft_error_exit("command not found\n");
	}
	cmd_path = find_cmd_path(cmd_args[0], env, mini);
	if (!cmd_path)
	{
		destroy_tab(mini->env);
		free(mini->rb);
		command_not_found(cmd_args[0]);
	}
	execve(cmd_path, cmd_args, env);
	perror("execve");
	free(cmd_path);
	exit(1);
}
