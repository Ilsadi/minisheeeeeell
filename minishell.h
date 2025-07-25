/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:41:44 by ilsadi            #+#    #+#             */
/*   Updated: 2025/07/25 17:04:26 by ilsadi           ###   ########.fr       */
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
	// char			**args;
	int				type;
	struct s_token	*next;
}					t_token;

typedef struct s_var
{
	char	*name;
	char	*value;
}			t_var;


//		EXEEEEEC

//	built_in

// built_in .c

int		is_builtin(const char *cmd);

// echo.c

int		ft_echo(t_token *token);

// env.c

int		env(char **envp);

// pwd.c

int		pwd(void);

// cd.c

int		cd(t_token *token, t_var **var);

// exit.c

int		ft_exit(t_token *token, t_var **var);

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

int		parsing(char *str, char **envp, t_var **var);
void	free_token_list(t_token *token);

// expand.c

char	*pars_expand(char *str, t_var **tab);

// token.c

t_token	*create_token(char *str, int type);
void	add_token(t_token **head, t_token **last, t_token *new_token);
t_token	*tokenize(char *line);
void	ft_printlist(t_token *token);
void	free_tokens(t_token *token);

//		SETUP

// utils_setup.c

int		size_var(t_var **tab);
int		size_tab(char **env);
void	print_tab(t_var **tab);

// search_var.c

t_var	**created_tab(char **env);
char	*get_value(t_var **tab, char *name);
void	destroy_tab(t_var **tab);
t_var	**unset_var(t_var **tab, char *name);

#endif