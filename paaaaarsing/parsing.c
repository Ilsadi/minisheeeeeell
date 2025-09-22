/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:44:26 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/22 19:57:48 by cbrice           ###   ########.fr       */
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

int	is_only_spaces(char *str)
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

// static void	remove_empty_token(t_token **head, t_rb_list *rb)
// {
// 	t_token	*first;
// 	t_token	*tmp;

// 	first = *head;
// 	if (!head || !*head)
// 		return ;
// 	while (first && first->next)
// 	{
// 		tmp = first->next;
// 		if (first->type == ARG && tmp->type == ARG)
// 		{
// 			first->str = rb_strfreejoin(first->str, tmp->str, rb);
// 			first->next = tmp->next;
// 			continue ;
// 		}
// 		first = first->next;
// 	}
// }

int	str_ends_with_slash(char *s)
{
	int	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	return (len > 0 && s[len - 1] == '/');
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

		// Empêche de concaténer si le premier se termine par /
		if (first->type == ARG && tmp->type == ARG && !str_ends_with_slash(first->str))
		{
			first->str = rb_strfreejoin(first->str, tmp->str, rb);
			first->next = tmp->next;
			continue ;
		}
		first = first->next;
	}
}

// static void	find_commands(t_token **head)
// {
// 	t_token	*first;
// 	int		expected;

// 	first = *head;
// 	if (!head || !*head)
// 		return ;
// 	expected = 1;
// 	while (first)
// 	{
// 		if (first->type == ARG && expected)
// 		{
// 			first->type = CMD;
// 			expected = 0;
// 		}
// 		else if (first->type == PIPE)
// 			expected = 1;
// 		else if (first->type >= HEREDOC)
// 		{
// 			if (!first->next)
// 			{
// 				ft_putstr_fd("ambiguous redirect\n", 2);
// 				return ;
// 			}
// 			first = first->next;
// 			expected = 1;
// 		}
// 		first = first->next;
// 	}
// }

static void get_good_value(t_token **first)
{
	t_token *value;
	int i;
	
	value = *first;
	while(value)
	{
		if (value->type == ARG)
		{
			i = 0;
			while (value->str[i])
			{
				if (value->str[i] < 0)
					value->str[i] *= -1;
				i++;
			}
		}
		value = value->next;	
	}
}
static int	find_commands(t_token **head, t_mini *mini)
{
	t_token	*first;
	int		expected;

	first = *head;
	if (!head || !*head)
		return (0);
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
			if (!first->next || !first->next->str || first->next->str[0] == '\0')
			{
				ft_putstr_fd("$e: ambiguous redirect\n", 2);
				mini->exit_status = 1;  // ✅ mettre le bon code d'erreur
				return (1);             // ✅ signaler qu'on a eu une erreur
			}
			first = first->next;
			expected = 1;
		}
		first = first->next;
	}
	return (0);
}


void	parsing(char *str, t_mini *mini, t_pipex *p)
{
	t_token	*first;
	pid_t	pid;
	int		sig;

	if (!pars_quotes(str))
		return ;
	if (!pars_pipe(str))
		return ;
	if (!pars_redir(str))
		return ;
	if (!pars_ampersand(str))
		return ;
	str = pars_expand(str, mini);
	restore_operators(str);
	// str = remove_quotes(str, mini);
	first = tokenize(str, mini);
	// expand_tokens(&first, mini);
	
	remove_empty_token(&first, mini->rb);
	remove_spaces(&first);
	get_good_value(&first);	
	// find_commands(&first, mini);
	if (find_commands(&first, mini))
	{
		mini->first = NULL;
		return;
	}	
		mini->first = first;
	// printf("%p\n", mini->first);
	// ft_printlist(mini->first);
	// exit(1);
	if (!first)
		return ;
	if (has_pipe(first))
	{
		// printf("1 mini: %p\n", mini);
		execute_pipeline(mini, p);
		return ;
	}
	else if (is_builtins(first))
	{
		mini->exit_status = builtin_with_redir(first, mini, p);
		return ;
		// builtin_with_redir(first, mini);
	}
	pid = fork();
	if (pid == 0)
	{
		setup_child_signals();
		if (handle_redirections(first, -1) < 0)
		{
			return (rb_free_all(mini->rb), free(mini->rb), exit(1));
		}
		ft_commands(mini);
		exit(3);
	}
	else if (pid > 0)
	{
		// g_in_cmd = 1;
		waitpid(pid, &mini->exit_status, 0);
		// g_in_cmd = 0;
		if (WIFSIGNALED(mini->exit_status))
		{
			sig = WTERMSIG(mini->exit_status);
			if (sig == SIGINT)
				write(1, "\n", 1);
			else if (sig == SIGQUIT)
				write(1, "Quit (core dumped)\n", 20);
		}
		mini->exit_status = mini->exit_status / 256;
	}
}

