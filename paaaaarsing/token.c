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

// Fonction qui parse la ligne et construit la liste de tokens
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

// t_token *tokenize(char *line, t_mini *mini)
// {
//     t_token *head = NULL;
//     t_token *current = NULL;

//     t_token *new_tok;
//     char *word;
//     int i = 0;
//     int start = 0;
//     int last_was_redir = 0;

//     while (line[i])
//     {
//         while (line[i] == ' ')
//             i++;
//         if (!line[i])
//             break;
//         start = i;
//         if (line[i] == '\'' || line[i] == '"')
//         {
//             new_tok = quotes(line, &i, mini);
//             add_token(&head, &current, new_tok);
//             last_was_redir = 0;
//         }
//         else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
//         {
//             new_tok = operator(line, &i, mini);
//             add_token(&head, &current, new_tok);
//             // marquer que le prochain ARG est cible possible de la redirection
//             last_was_redir = 1;
//         }
//         else
//         {
//             if (last_was_redir)
//             {
//                 // Cas après redirection : on prend tout (incluant espaces) jusqu'à un opérateur ou fin
//                 // ou jusqu'à ce qu'on sache que le token doit être séparé (par exemple guillemets)
//                 // On peut détecter guillemets ici aussi
//                 int j = i;
//                 // int in_quotes = 0;
//                 // Si commence par guillemet, traiter comme quotes
//                 if (line[j] == '"' || line[j] == '\'')
//                 {
//                     new_tok = quotes(line, &j, mini);
//                     add_token(&head, &current, new_tok);
//                     i = j;
//                 }
//                 else
//                 {
//                     // Considérer comme mot jusqu'au prochain opérateur < > |, mais *ne pas* couper sur espace
//                     // sauf si vraiment opérateur ou fin de ligne
//                     while (line[j]
//                         && line[j] != '|'
//                         && line[j] != '<'
//                         && line[j] != '>')
//                     {
//                         j++;
//                     }
//                     // => le nom de fichier sera tout de line[i..j-1]
//                     word = rb_substr(line, i, j - i, mini->rb);
//                     new_tok = create_token(word, ARG, mini);
//                     add_token(&head, &current, new_tok);
//                     i = j;
//                 }
//                 last_was_redir = 0;  // reset
//             }
//             else
//             {
//                 // Comportement normal
//                 start = i;
//                 while (line[i] && line[i] != ' ' && line[i] != '|' && line[i] != '<'
//                     && line[i] != '>' && line[i] != '"' && line[i] != '\'')
//                     i++;
//                 word = rb_substr(line, start, i - start, mini->rb);
//                 new_tok = create_token(word, ARG, mini);
//                 add_token(&head, &current, new_tok);
//             }
//         }
//         if (line[i] == ' ')
//         {
//             new_tok = create_token(NULL, TMP_SPACE, mini);
//             add_token(&head, &current, new_tok);
//         }
//     }
//     return head;
// }

// t_token *tokenize(char *line, t_mini *mini)
// {
// 	t_token *head = NULL;
// 	t_token *current = NULL;
// 	t_token *new_tok;
// 	char *word;
// 	int i = 0;
// 	int last_was_redir = 0;

// 	while (line[i])
// 	{
// 		while (line[i] == ' ')
// 			i++;
// 		if (!line[i])
// 			break;

// 		if (line[i] == '\'' || line[i] == '"')
// 		{
// 			new_tok = quotes(line, &i, mini);
// 			if (!new_tok)
// 				return NULL;
// 			add_token(&head, &current, new_tok);
// 			last_was_redir = 0;
// 		}
// 		else if (line[i] == '<' || line[i] == '>' || line[i] == '|')
// 		{
// 			new_tok = operator(line, &i, mini);
// 			if (!new_tok)
// 				return NULL;
// 			add_token(&head, &current, new_tok);
// 			last_was_redir = 1;
// 		}
// 		else if (last_was_redir)
// 		{
// 			int j = i;

// 			// Si quote : traiter comme quote
// 			if (line[j] == '\'' || line[j] == '"')
// 			{
// 				new_tok = quotes(line, &j, mini);
// 				if (!new_tok)
// 					return NULL;
// 				add_token(&head, &current, new_tok);
// 				i = j;
// 			}
// 			else
// 			{
// 				// Ne pas s'arrêter sur espace, on prend tout jusqu'à opérateur
// 				while (line[j] && line[j] != '<' && line[j] != '>' && line[j] != '|')
// 					j++;

// 				word = rb_substr(line, i, j - i, mini->rb);
// 				if (!word)
// 					return NULL;
// 				new_tok = create_token(word, ARG, mini);
// 				if (!new_tok)
// 					return NULL;
// 				add_token(&head, &current, new_tok);
// 				i = j;
// 			}
// 			last_was_redir = 0;
// 		}
// 		else
// 		{
// 			// Normal: couper sur espace ou opérateur
// 			int start = i;
// 			while (line[i] && line[i] != ' ' && line[i] != '<' && line[i] != '>' && line[i] != '|'
// 				&& line[i] != '"' && line[i] != '\'')
// 				i++;
// 			word = rb_substr(line, start, i - start, mini->rb);
// 			if (!word)
// 				return NULL;
// 			new_tok = create_token(word, ARG, mini);
// 			if (!new_tok)
// 				return NULL;
// 			add_token(&head, &current, new_tok);
// 		}

// 		if (line[i] == ' ')
// 		{
// 			new_tok = create_token(NULL, TMP_SPACE, mini);
// 			if (!new_tok)
// 				return NULL;
// 			add_token(&head, &current, new_tok);
// 			i++;
// 		}
// 	}

// 	return head;
// }
