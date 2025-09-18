/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:11:30 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/18 20:26:50 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_command(char **env, t_mini *mini, int exit_code)
{
	ft_free_tab(env);
	destroy_tab(mini->env);
	rb_free_all(mini->rb);
	free(mini->rb);
	exit(exit_code);
}

static void	commands_utils(char *cmd_path, char **cmd_args, char **env,
		t_mini *mini)
{
	DIR	*dir;

	dir = opendir(cmd_path);
	if (dir)
	{
		ft_putstr_fd(cmd_args[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		closedir(dir);
		free_command(env, mini, 126);
	}
	execve(cmd_path, cmd_args, env);
	perror(cmd_path);
	free_command(env, mini, 1);
}

static void	command_utils2(char **cmd_args, char **env,
		t_mini *mini)
{
	if (access(cmd_args[0], F_OK) != -1)
	{
		if (access(cmd_args[0], X_OK) != -1)
		{
			execve(cmd_args[0], cmd_args, env);
			ft_putstr_fd(cmd_args[0], 2);
			ft_putstr_fd(": Permission denied\n", 2);
			free_command(env, mini, 1);
		}
	}
}

void	ft_commands(t_mini *mini)
{
	char	*cmd_path;
	char	**cmd_args;
	char	**env;

	cmd_args = token_to_cmd(&mini->first, mini);
	if (!cmd_args || !cmd_args[0])
		return (rb_free_all(mini->rb), exit(0));
	env = var_to_envp(mini->env);
	if (!env)
		return (rb_free_all(mini->rb), ft_error_exit("Error environment\n"));
	cmd_path = find_cmd_path(cmd_args[0], mini);
	if (cmd_path)
		commands_utils(cmd_path, cmd_args, env, mini);
	else
	{
		command_utils2(cmd_args, env, mini);
		ft_putstr_fd(cmd_args[0], 2);
		if (ft_strchr(cmd_args[0], '/') || !get_value(mini->env, "PATH"))
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": command not found\n", 2);
		free_command(env, mini, 127);
	}
}
