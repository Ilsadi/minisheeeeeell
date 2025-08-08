/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:37:08 by ilsadi            #+#    #+#             */
/*   Updated: 2025/08/03 20:37:08 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **token_to_cmd(t_token **current, t_mini *mini)
{
    t_token *start;
    t_token *tmp;
    int      count;
    int      i;
    int      skip_next;
    char   **cmd;

    start = *current;
    count = 0;
    skip_next = 0;

    /* 1) Compter */
    tmp = start;
    while (tmp && tmp->type != PIPE)
    {
        if (skip_next) { skip_next = 0; tmp = tmp->next; continue; }

        if (tmp->type == INPUT || tmp->type == TRUNC
         || tmp->type == APPEND || tmp->type == HEREDOC)
        {
            /* ne pas inclure l'opérateur, et skipper aussi son operand (filename/delimiter) */
            skip_next = 1;
            tmp = tmp->next;
            continue;
        }
        if (tmp->type == CMD || tmp->type == ARG)
            count++;
        tmp = tmp->next;
    }

    cmd = rb_calloc(count + 1, sizeof(char *), mini->rb);
    if (!cmd)
        return (NULL);

    /* 2) Remplir */
    i = 0;
    skip_next = 0;
    tmp = start;
    while (tmp && tmp->type != PIPE)
    {
        if (skip_next) { skip_next = 0; tmp = tmp->next; continue; }

        if (tmp->type == INPUT || tmp->type == TRUNC
         || tmp->type == APPEND || tmp->type == HEREDOC)
        {
            skip_next = 1;                 /* sauter le filename */
            tmp = tmp->next;
            continue;
        }
        if (tmp->type == CMD || tmp->type == ARG)
            cmd[i++] = rb_strdup(tmp->str, mini->rb);
        tmp = tmp->next;
    }
    cmd[i] = NULL;

    /* Avancer *current jusqu’au pipe (même comportement que ton code) */
    while (*current && (*current)->type != PIPE)
        *current = (*current)->next;

    return (cmd);
}


// char	**token_to_cmd(t_token **current, t_mini *mini)
// {
// 	t_token *start;
// 	int		count;
// 	char	**cmd;
// 	int		i;

// 	start = *current;
// 	count = 0;
// 	i = 0;
// 	while (*current && (*current)->type != PIPE)
// 	{
// 		if ((*current)->type == CMD || (*current)->type == ARG)
// 			count++;
// 		*current = (*current)->next;
// 	}
// 	cmd = rb_calloc(count + 1, sizeof(char *), mini->rb);
// 	if (!cmd)
// 		return (NULL);
// 	while (start && start->type != PIPE)
// 	{
// 		if (start->type == CMD || start->type == ARG)
// 		{
// 			cmd[i] = rb_strdup(start->str, mini->rb);
// 			i++;
// 		}
// 		start = start->next;
// 	}
// 	cmd[i] = NULL;
// 	return (cmd);
// }

int	has_pipe(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == PIPE)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

void	execute_pipeline(t_mini *mini)
{
	t_token	*current;
	t_pipex	pipex;
	int		status;
	int		last_status = 0;
	pid_t	waited_pid;

	current = mini->first;
	ft_memset(&pipex, 0, sizeof(t_pipex));
	pipex.infile = STDIN_FILENO;
	pipex.outfile = STDOUT_FILENO;
	if (current && current->type == PIPE)
		current = current->next;
	ft_pipex_loop(&pipex, mini->first, mini->env, mini);
	while ((waited_pid = wait(&status)) > 0)
    {
        if (WIFEXITED(status))
            last_status = WEXITSTATUS(status);
    }
	mini->exit_status = last_status;
}