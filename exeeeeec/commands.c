/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:11:30 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/10 13:30:22 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_commands(t_mini *mini)
// {
// 	char	*cmd_path;
// 	char	**cmd_args;
// 	char	**env;

// 	env = var_to_envp(mini->env);
// 	if (!env)
// 		ft_error_exit("Error creating environment\n");
// 	if (handle_redirections(mini->first) < 0)
// 	{
// 		ft_free_tab(env);
// 		exit(1);
// 	}
// 	cmd_args = token_to_cmd(&mini->first, mini);
// 	if (!cmd_args || !cmd_args[0] || cmd_args[0][0] == '\0')
// 	{
// 		destroy_tab(mini->env);
// 		ft_error_exit("command not found\n");
// 	}
// 	cmd_path = find_cmd_path(cmd_args[0], env, mini);
// 	if (!cmd_path)
// 	{
// 		ft_free_tab(env);
// 		if (ft_strchr(cmd_args[0], '/'))
// 		{
// 			if (!access(cmd_args[0], X_OK) || execve(cmd_args[0], cmd_args, env) == -1)
// 			{
// 				ft_putstr_fd(cmd_args[0], 2);
// 				ft_putstr_fd(": No such file or directory\n", 2);
// 				destroy_tab(mini->env);
// 				rb_free_all(mini->rb);
// 				exit(127);
// 			}
// 		}
// 		command_not_found(cmd_args[0]);
// 		destroy_tab(mini->env);
// 		rb_free_all(mini->rb);
// 		free(mini->rb);
// 		exit(127);
// 	}
// 	execve(cmd_path, cmd_args, env);
// 	perror("execve");
// 	ft_free_tab(env);
// 	destroy_tab(mini->env);
// 	rb_free_all(mini->rb);
// 	free(mini->rb);
// 	exit(1);
// }


void	ft_commands(t_mini *mini)
{
	char	*cmd_path;
	char	**cmd_args;
	char	**env;
	DIR		*dir;

	env = var_to_envp(mini->env);
	if (!env)
		ft_error_exit("Error creating environment\n");
	cmd_args = token_to_cmd(&mini->first, mini);
	if (!cmd_args || !cmd_args[0] || cmd_args[0][0] == '\0')
	{
		destroy_tab(mini->env);
		ft_error_exit("command not found\n");
	}
	cmd_path = find_cmd_path(cmd_args[0], env, mini);
	if (cmd_path)
	{
		dir = opendir(cmd_path);
		if (dir)
		{
			ft_putstr_fd(cmd_args[0], 2);
			ft_putstr_fd(": Is a directory\n", 2);
			closedir(dir);
			ft_free_tab(env);
			destroy_tab(mini->env);
			rb_free_all(mini->rb);
			free(mini->rb);
			exit(126);
		}
		execve(cmd_path, cmd_args, env);
		perror(cmd_path);
		ft_free_tab(env);
		destroy_tab(mini->env);
		rb_free_all(mini->rb);
		free(mini->rb);
		exit(1);
	}
	else
	{
		if (access(cmd_args[0], F_OK) != -1)
		{
			// if (access(cmd_args[0], X_OK))
			// {
			execve(cmd_args[0], cmd_args, env);
			dir = opendir(cmd_args[0]);
			ft_putstr_fd(cmd_args[0], 2);
			if (dir)
			{
				ft_putstr_fd(": Is a directory\n", 2);
				closedir(dir);
			}
			else
				ft_putstr_fd(": Permission denied\n", 2);
			ft_free_tab(env);
			destroy_tab(mini->env);
			rb_free_all(mini->rb);
			free(mini->rb);
			exit(1);
		}
		ft_putstr_fd(cmd_args[0], 2);
		if (ft_strchr(cmd_args[0], '/'))
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": command not found\n", 2);
		ft_free_tab(env);
		destroy_tab(mini->env);
		rb_free_all(mini->rb);
		free(mini->rb);
		exit(127);
	}
}
