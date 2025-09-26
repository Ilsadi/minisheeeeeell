/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:44:26 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/26 18:51:25 by cbrice           ###   ########.fr       */
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
		if (first->type == ARG && tmp->type == ARG
			&& !str_ends_with_slash(first->str))
		{
			first->str = rb_strfreejoin(first->str, tmp->str, rb);
			first->next = tmp->next;
			continue ;
		}
		first = first->next;
	}
}

static void	get_good_value(t_token **first)
{
	t_token	*value;
	int		i;

	value = *first;
	while (value)
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

static int	is_redir_tok(int type)
{
	return (type >= HEREDOC);
}

static int	validate_redir_target(t_token *tok, t_mini *mini)
{
	if (!tok->next || !tok->next->str || tok->next->str[0] == '\0')
	{
		ft_putstr_fd("$e: ambiguous redirect\n", 2);
		mini->exit_status = 1;
		return (0);
	}
	return (1);
}

static int	handle_find_step(t_token **cur, int *expected, t_mini *mini)
{
	if ((*cur)->type == ARG && *expected)
	{
		(*cur)->type = CMD;
		*expected = 0;
	}
	else if ((*cur)->type == PIPE)
		*expected = 1;
	else if (is_redir_tok((*cur)->type))
	{
		if (!validate_redir_target(*cur, mini))
			return (1);
		*expected = 1;
		*cur = (*cur)->next;
		return (0);
	}
	*cur = (*cur)->next;
	return (0);
}

static int	find_commands(t_token **head, t_mini *mini)
{
	t_token	*cur;
	int		expected;

	if (!head || !*head)
		return (0);
	cur = *head;
	expected = 1;
	while (cur)
		if (handle_find_step(&cur, &expected, mini))
			return (1);
	return (0);
}

static char	*prepare_input(char *str, t_mini *mini)
{
	if (!pars_quotes(str))
		return (NULL);
	if (!pars_pipe(str))
		return (NULL);
	if (!pars_redir(str))
		return (NULL);
	if (!pars_ampersand(str))
		return (NULL);
	return (pars_expand(str, mini));
}

static t_token	*build_tokens(char *str, t_mini *mini)
{
	t_token	*first;

	first = tokenize(str, mini);
	remove_empty_token(&first, mini->rb);
	remove_spaces(&first);
	get_good_value(&first);
	if (find_commands(&first, mini))
		return (NULL);
	return (first);
}

static void	run_child_branch(t_token *first, t_mini *mini)
{
	setup_child_signals();
	if (handle_redirections(first, -1) < 0)
	{
		rb_free_all(mini->rb);
		free(mini->rb);
		exit(1);
	}
	ft_commands(mini);
	exit(3);
}

static void	run_parent_branch(t_mini *mini, pid_t pid)
{
	int	status;
	int	sig;

	sig = 0;
	status = 0;
	setup_parent_signals();
	g_state = STATE_IN_CMD;
	waitpid(pid, &status, 0);
	g_state = STATE_IDLE;
	if (WIFEXITED(status))
		mini->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		mini->exit_status = 128 + sig;
		if (sig == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		else if (sig == SIGINT)
			write(2, "\n", 1);
	}
	if (!sig)
		mini->exit_status = 128 + sig;
	setup_signals();
}

static int	handle_no_fork_cases(t_token *first, t_mini *mini, t_pipex *p)
{
	if (has_pipe(first))
	{
		execute_pipeline(mini, p);
		return (1);
	}
	if (is_builtins(first))
	{
		mini->exit_status = builtin_with_redir(first, mini, p);
		return (1);
	}
	return (0);
}

void	parsing(char *str, t_mini *mini, t_pipex *p)
{
	t_token	*first;
	pid_t	pid;

	str = prepare_input(str, mini);
	if (!str)
		return ;
	first = build_tokens(str, mini);
	if (!first)
	{
		mini->first = NULL;
		return ;
	}
	mini->first = first;
	if (handle_no_fork_cases(first, mini, p))
		return ;
	pid = fork();
	if (pid == 0)
		run_child_branch(first, mini);
	else if (pid > 0)
		run_parent_branch(mini, pid);
}
