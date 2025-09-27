/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:06:42 by cbrice            #+#    #+#             */
/*   Updated: 2025/09/27 20:24:34 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_redir_target(t_token *tok, t_mini *mini)
{
	if (!tok->next || !tok->next->str || tok->next->str[0] == '\0')
	{
		ft_putstr_fd("$e: ambiguous redirect\n", 2);
		mini->exit_status = 1;
		return (0);
	}
	return (1);
}

int	handle_find_step(t_token **cur, int *expected, t_mini *mini)
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

int	find_commands(t_token **head, t_mini *mini)
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

char	*prepare_input(char *str, t_mini *mini)
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

t_token	*build_tokens(char *str, t_mini *mini)
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
