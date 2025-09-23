/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:22:37 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/23 21:16:07 by cbrice           ###   ########.fr       */
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

char	**var_to_envp(t_var **var)
{
	char	**envp;
	char	*tmp;
	int		i;
	int		count;

	envp = ft_calloc(sizeof(char *), (size_var(var) + 1));
	if (!envp)
		return (NULL);
	i = -1;
	count = 0;
	while (var[++i])
	{
		if ((var[i]->value))
		{
			tmp = ft_strjoin(var[i]->name, "=");
			envp[i - count] = ft_strjoin(tmp, var[i]->value);
			free(tmp);
		}
		else
			count += 1;
	}
	envp[i] = NULL;
	return (envp);
}
