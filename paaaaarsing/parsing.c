/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:44:26 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/05 17:16:00 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free_token(token);
		token = tmp;
	}
}

void	free_token(t_token *token)
{
	free(token->str);
	free(token);
}

void	ft_printlist(t_token *token)
{
	while (token)
	{
		ft_printf("%d ", token->type);
		if (token->str)
			ft_printf("%s ", token->str);
		if (token->next)
			ft_printf("-> ");
		else
			ft_printf("\n");
		token = token->next;
	}
}

void	restore_operators(char *str)
{
	int	i;
	
	i = 0;
	while (str && str[i])
	{
		if (str[i] < 0)
			str[i] *= -1;
		i++;
	}
}

int is_only_spaces(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char	*remove_quotes(const char *str, t_mini *mini)
{
	int	i;
	int	j;
	int	state;
	char	*res;
	
	i = 0;
	j = 0;
	state = 0;
	res = rb_malloc(ft_strlen(str) + 1, mini->rb);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"' && state == 0)
			state = 1;
		else if (str[i] == '"' && state == 1)
			state = 0;
		else if (str[i] == '\'' && state == 0)
			state = 2;
		else if (str[i] == '\'' && state == 2)
			state = 0;
		else
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
	}

static void	remove_spaces(t_token **head)
{
	t_token	*first;
	t_token	*tmp;

	first = *head;

	if (!head || !*head)
		return ;
	while (first && first->next)
	{
		tmp = first->next;
		if (first->type == TMP_SPACE)
			*head = tmp;
		else if (tmp->type == TMP_SPACE)
			first->next = tmp->next;
		first = first->next;
	}
}
	
static void	remove_empty_token(t_token **head, t_rb_list *rb)
{
	t_token	*first;
	t_token	*tmp;

	first = *head;

	if (!head || !*head)
		return ;
	while (first && first->next)
	{
		tmp = first->next;
		if (first->type == ARG && (first->str == NULL || *first->str == '\0') && first == *head)
			*head = tmp;
		// else if ((tmp->type == ARG && (tmp->str == NULL || *tmp->str == '\0')))
		// {
		// 	first->next = tmp->next;
		// 	continue ;
		// }
		else if ((first->type == CMD || first->type == ARG) && tmp->type == ARG)
		{
			first->str = rb_strfreejoin(first->str, tmp->str, rb);
			first->next = tmp->next;
			continue ;
		}
		first = first->next;
	}
}

static void	find_commands(t_token **head)
{
	t_token	*first;
	int		expected;

	first = *head;

	if (!head || !*head)
		return ;
	expected = 1;
	while (first)
	{
		if (first->type == ARG && expected)
		{
			first->type = CMD;
			expected = 0;
		}
		else if (first->type == PIPE)
			expected = 1;
		else if (first->type >= HEREDOC)
		{
			first = first->next;
			expected = 1;
			// if (first->next)
		}
		first = first->next;
	}
}

int	parsing(char *str, t_mini *mini)
{
	t_token	*first;
	pid_t	pid;
	int sig;

	if (!pars_quotes(str))
		return (0);
	if (!pars_pipe(str))
		return (0);
	if (!pars_redir(str))
		return (0);
	// if (!pars_slash(str))
	// 	return (0);
	if (!pars_ampersand(str))
		return (0);
	str = pars_expand(str, mini);
	restore_operators(str);
	// str = remove_quotes(str, mini);
	first = tokenize (str, mini);
	// ft_printlist(first);
	remove_empty_token(&first, mini->rb);
	remove_spaces(&first);
	find_commands(&first);
	// ft_printlist(first);
	mini->first = first;
	if (!first)
	{
		if (is_only_spaces(str))
		{
			return (0);
		}
		else
		{
			ft_error(": command not found\n");
			return (1);
		}
	}
	if (first->str && first->str[0] == '\0')
	{
		ft_error(": command not found\n");
		return (1);
	}
	if (first)
	{
		if (has_pipe(first))
		{
			execute_pipeline(mini);
			return (0);
		}
		if (first->type != CMD)
		{
			command_not_found(first->str);
			return (0);
		}
		if (first->str ==NULL)
		{
			handle_redirections(first);
			return (0);
		}
		else if (is_builtins(first))
		{
			builtin_with_redir(first, mini);
			return (1);
		}
		pid = fork();
		if (pid == 0)
		{
			setup_child_signals();
			ft_commands(mini);
			exit(EXIT_FAILURE);
		}
		else if (pid > 0)
		{
			g_in_cmd = 1;
			waitpid(pid, &mini->exit_status, 0);
			g_in_cmd = 0;
			if (WIFSIGNALED(mini->exit_status))
			{
				sig = WTERMSIG(mini->exit_status);
				if (sig == SIGINT)
					write(1, "\n", 1);
				else if (sig == SIGQUIT)
					write (1, "Quit (core dumped)\n", 20);
			}
		}
		return (0); //iccccccccccccci
	}
	return (1);
}
