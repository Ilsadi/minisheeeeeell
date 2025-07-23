#include "../minishell.h"

t_token	*create_token(char *str, int type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	if (str)
		new_token->str = ft_strdup(str);
	else
		new_token->str = NULL;
	// new_token->args = NULL;
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

t_token	*quotes(char *line, int *i)
{
	int		start;
	char	quote;
	char	*word;
	t_token	*tok;

	quote = line[*i++];
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	word = ft_substr(line, start, *i - start);
	tok = create_token(word, ARG);
	free(word);

	return (tok);
}

t_token	*operator(char *line, int *i)
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
	tok = create_token(NULL, type);
	return (tok);
}

// t_token *cmd(char *line, int *i)
// {
// 	int	type;
// 	t_token *tok;

// 	if ()
// }

// Fonction qui parse la ligne et construit la liste de tokens
t_token	*tokenize(char *line)
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
			new_tok = quotes(line, &i);
			add_token(&head, &current, new_tok);
		}
		else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		{
			new_tok = operator(line, &i);
			add_token(&head, &current, new_tok);
		}
		else
		{
			start = i;
			while (line[i] && line[i] != ' ' && line[i] != '|' && line[i] != '<' && line[i] != '>')
				i++;
			word = ft_substr(line, start, i - start);
			if (ft_strcmp(word, "echo") == 0)
				new_tok = create_token(word, CMD);
			else if (ft_strcmp(word, "pwd") == 0)
				new_tok = create_token(word, CMD);
			else if (ft_strcmp(word, "env") == 0)
				new_tok = create_token(word, CMD);
			else
				new_tok = create_token(word, ARG);
			add_token(&head, &current, new_tok);
			free(word);
		}
	}
	return (head);
}
