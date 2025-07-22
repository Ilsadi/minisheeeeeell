/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:41:44 by ilsadi            #+#    #+#             */
/*   Updated: 2025/07/22 13:50:01 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define CMD		1
# define ARG		2
# define PIPE		3
# define HEREDOC	4
# define APPEND		5
# define INPUT		6
# define TRUNC		7

# define ERROR_NEWLINE "bash: syntax error near unexpected token `newline'\n"
# define ERROR_ENEXPECTED_SLASH "bash: syntax error near enexpected token '/'\n"

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
}					t_token;

//		EXEEEEEC

//	built_in

// built_in .c

int		is_builtin(const char *cmd);

// echo.c

int		ft_echo(char **args);

// env.c

int		env(char **envp);

// pwd.c

int		pwd(void);

//		PAAAAAARSING

// quotes.c

int		pars_quotes(char *str);

// redirections.c

int		is_operator(char *str);
int		pars_redir(char *str);

// slash.c

int		is_word(char c);
int		pars_slash(char *str);

// pipe.c

int		pars_pipe(char *str);

// parsing.c

int		parsing(char *str, char **envp);

// expand.c

char	*pars_expand(char *str, char **envp);

// token.c

t_token	*create_token(char *str, int type);
void	add_token(t_token **head, t_token **last, t_token *new_token);
t_token	*tokenize(char *line);
void	ft_printlist(t_token *token);

#endif