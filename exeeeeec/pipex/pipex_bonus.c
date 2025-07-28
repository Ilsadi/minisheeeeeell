/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:05:01 by ilsadi            #+#    #+#             */
/*   Updated: 2025/07/28 13:04:23 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

static void	ft_child_process(t_pipex *pipex, char *cmd, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
	{
		ft_free_tab(cmd_args);
		close_all(pipex);
		ft_error_exit("Error : ft_split");
	}
	if (!cmd_args[0] || cmd_args[0][0] == '\0')
	{
		ft_free_tab(cmd_args);
		close_all(pipex);
		ft_error_exit("Pipex: command not found\n");
	}
	cmd_path = find_cmd_path(cmd_args[0], envp);
	if (!cmd_path)
		return (ft_free_tab(cmd_args), close_all(pipex),
			ft_error_exit("Pipex : command not found\n"));
	error_fd(pipex);
	close_all(pipex);
	execve(cmd_path, cmd_args, envp);
	perror("execve");
	free(cmd_path);
	ft_free_tab(cmd_args);
	exit(1);
}

static void	ft_pipex_loop(t_pipex *pipex, int ac, char **av, t_var **var)
{
	int		i;
	char	**envp;

	pipex->fd_in = pipex->infile;
	envp = var_to_envp(var);
	if (!envp)
		ft_error_exit("Error: var_to_envp");
	i = pipex->cmd_start - 1;
	while (++i < ac - 1)
	{
		pipex->fd_out = choose_out(pipex, i, ac);
		pipex->pid1 = fork();
		if (pipex->pid1 < 0)
		{
			ft_free_tab(envp);
			ft_error_exit("Error : fork");
		}
		if (pipex->pid1 == 0)
		{
			if (pipex->fd_in < 0)
				return (close_all(pipex), perror(av[1]), exit(1));
			if (pipex->fd_out < 0)
				return (close_all(pipex), perror(av[ac - 1]), exit(1));
			ft_child_process(pipex, av[i], envp);
		}
		close_test(pipex->fd_in);
		close_test(pipex->fd_out);
		pipex->fd_in = pipex->pipefd[0];
	}
	close_test(pipex->fd_in);
	ft_free_tab(envp);
}

static void	handle_here_doc(t_pipex *pipex, int ac, char **av)
{
	char	*line;

	if (pipe(pipex->pipefd) == -1)
		ft_error_exit("pipe error");
	while (1)
	{
		line = ft_get_next_line(0);
		if (!line)
			break ;
		if (ft_strlen(line) == ft_strlen(av[2]) + 1
			&& ft_strncmp(line, av[2], ft_strlen(av[2])) == 0)
		{
			free(line);
			break ;
		}
		write(pipex->pipefd[1], line, ft_strlen(line));
		free(line);
	}
	close_test(pipex->pipefd[1]);
	pipex->infile = pipex->pipefd[0];
	pipex->outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	pipex->cmd_start = 3;
}

int	main(int ac, char **av, t_var **var)
{
	t_pipex	pipex;
	int		i;
	int		status;
	int		last_status;

	if (ac < 5)
		return (ft_printf("Error : arguments\n"), 1);
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
		handle_here_doc(&pipex, ac, av);
	else
	{
		pipex.infile = open(av[1], O_RDONLY);
		pipex.outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
		pipex.cmd_start = 2;
	}
	ft_pipex_loop(&pipex, ac, av, var);
	i = 0;
	while (i++ < ac - pipex.cmd_start - 1)
	{
		if (wait(&status) == pipex.pid1)
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
	}
	return (close_test(pipex.infile), close_test(pipex.outfile), last_status);
}
