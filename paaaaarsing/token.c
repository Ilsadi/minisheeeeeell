/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbrice <cbrice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 17:32:08 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/23 21:09:21 by cbrice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *str, int type, t_mini *mini)
{
	t_token	*new_token;

	new_token = rb_malloc(sizeof(t_token), mini->rb);
	if (!new_token)
		return (NULL);
	if (str)
	{
		new_token->str = rb_strdup(str, mini->rb);
		if (!new_token->str)
			return (NULL);
	}
	else
		new_token->str = NULL;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

// Fonction pour ajouter un token à la liste chaînée
void	add_token(t_token **head, t_token **last, t_token *new_token)
{
	if (!*head)
	{
		*head = new_token;
		*last = new_token;
	}
	else
	{
		(*last)->next = new_token;
		*last = new_token;
	}
}

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

t_token	*tokenize(char *line, t_mini *mini)
{
	t_token *head = NULL;
	t_token *current = NULL;

	t_token	*new_tok;
	char *word;
	int i = 0;
	int start = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (!line[i])
			break ;
		start = i;
		if (line[i] == '\'' || line[i] == '"')
		{
			new_tok = quotes(line, &i, mini);
			if (!new_tok)
				return (NULL);
			add_token(&head, &current, new_tok);
		}
		else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		{
			new_tok = operator(line, &i, mini);
			if (!new_tok)
				return (NULL);
			add_token(&head, &current, new_tok);
			if (line[i] == '\'' || line[i] == '"')
			{
				t_token *quoted = quotes(line, &i, mini);
				if (!quoted)
					return (NULL);
				add_token(&head, &current, quoted);
			}
			else
			{
				int start_arg = i;
				while (line[i] && line[i] != ' ' && line[i] != '|' && line[i] != '<' && line[i] != '>')
					i++;
				if (i > start_arg)
				{
					word = rb_substr(line, start_arg, i - start_arg, mini->rb);
					if (!word)
						return (NULL);
					t_token *arg_tok = create_token(word, ARG, mini);
					if (!arg_tok)
						return (NULL);
					add_token(&head, &current, arg_tok);
				}
			}
		}
		else
		{
			start = i;
			while (line[i] && line[i] != ' ' && line[i] != '|' && line[i] != '<'
				&& line[i] != '>' && line[i] != '"'
				&& line[i] != '\'')
				i++;
			word = rb_substr(line, start, i - start, mini->rb);
			if (!word)
				return (NULL);
			else
				new_tok = create_token(word, ARG, mini);
			if (!new_tok)
				return (NULL);
			add_token(&head, &current, new_tok);
		}
		if (line[i] == ' ')
		{
			new_tok = create_token(NULL, TMP_SPACE, mini);
			add_token(&head, &current, new_tok);
		}
	}
	return (head);
}

