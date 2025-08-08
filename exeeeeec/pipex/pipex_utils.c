/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:22:37 by ilsadi            #+#    #+#             */
/*   Updated: 2025/08/08 20:23:36 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_test(int fd)
{
	if (fd > 2)
		close(fd);
}

void	close_all(t_pipex *pipex)
{
	close_test(pipex->infile);
	close_test(pipex->outfile);
	close_test(pipex->fd_in);
	close_test(pipex->fd_out);
	close_test(pipex->pipefd[0]);
	close_test(pipex->pipefd[1]);
}

void	ft_error_exit(const char *msg)
{
	perror(msg);
	exit(127);
}

int	choose_out(t_pipex *pipex)
{
	if (pipex->cmd2)
		return (pipex->pipefd[1]);
	else
		return (pipex->outfile);
}

char	**var_to_envp(t_var **var)
{
	char	**envp;
	char	*tmp;
	int		i;
	int		count;

	count = size_var(var);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (var[i])
	{
		tmp = ft_strjoin(var[i]->name, "=");
		envp[i] = ft_strjoin(tmp, var[i]->value);
		free(tmp);
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
