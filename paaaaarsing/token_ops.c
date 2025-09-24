/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 21:19:20 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/24 20:15:49 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*quotes(char *line, int *i, t_mini *mini)
{
	int		start;
	char	quote;
	char	*word;
	t_token	*tok;

	quote = line[(*i)++];
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	word = rb_substr(line, start, *i - start, mini->rb);
	if (!word)
		return (NULL);
	if (line[*i] == quote)
		(*i)++;
	tok = create_token(word, ARG, mini);
	if (!tok)
		return (NULL);
	return (tok);
}

t_token	*operator(char *line, int *i, t_mini *mini)
{
	int		type;
	t_token	*tok;

	if (line[*i] == '|')
		type = PIPE;
	else if (line[*i] == '<')
	{
		type = INPUT;
		if (line[*i] == '<' && line[*i + 1] == '<')
			type = HEREDOC;
	}
	else
	{
		type = TRUNC;
		if (line[*i] == '>' && line[*i + 1] == '>')
			type = APPEND;
	}
	if (type == HEREDOC || type == APPEND)
		*i += 2;
	else
		(*i)++;
	tok = create_token(NULL, type, mini);
	if (!tok)
		return (NULL);
	return (tok);
}
