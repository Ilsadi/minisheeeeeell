/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:41:44 by ilsadi            #+#    #+#             */
/*   Updated: 2025/08/03 23:29:09 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

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

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	pid_t	pid1;
	pid_t	pid2;
	int		pipefd[2];
	int		fd_in;
	int		fd_out;
	int		cmd_start;
	char	**cmd1;
	char	**cmd2;
}				t_pipex;

typedef struct s_var
{
	char	*name;
	char	*value;
}			t_var;

typedef struct s_mini
{
	struct s_token		*first;
	struct s_rb_list 	*rb;
	struct s_var		**env;
	int					exit_status;
}				t_mini;

typedef struct s_rb_node
{
	void							*ptr;
	struct s_rb_node				*next;
}									t_rb_node;

typedef struct s_rb_list
{
	t_rb_node						*head;
}									t_rb_list;

//		EXEEEEEC

//	pipex

// pipex_pars.c

char	*find_cmd_path(char *cmd, char **envp, t_mini *mini);

// pipex_mini.c

int		has_pipe(t_token *tokens);
void	execute_pipeline(t_mini *mini);
char	**token_to_cmd(t_token **current, t_mini *mini);

// pipex_utils.c

void	close_test(int fd);
void	close_all(t_pipex *pipex);
void	ft_error_exit(const char *msg);
int		choose_out(t_pipex *pipex);
char	**var_to_envp(t_var **var);

// pipex_bonus.c


void	ft_pipex_loop(t_pipex *pipex, t_token *tokens, t_var **var, t_mini *mini);

// pipex_utils.c

void	close_test(int fd);
void	close_all(t_pipex *pipex);
void	ft_error_exit(const char *msg);
char	**var_to_envp(t_var **var);

//	built_in

// built_in .c

int		is_builtin(const char *cmd);

// echo.c

int		ft_echo(t_token *token);

// env.c

int		env(t_var **var);

// pwd.c

int		pwd(void);

// cd.c

int		cd(t_token *token, t_var **var);

// unset.c

t_var	**unset_var(t_var **tab, char *name, t_mini *mini);
int		unset(t_token *token, t_mini *mini);

// export.c

int	ft_export(t_token *token, t_mini *mini);

// exit.c

int		ft_exit(t_token *token);

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

int		parsing(char *str, t_mini *mini);
void	free_token_list(t_token *token);

// expand.c

char	*pars_expand(char *str, t_mini *mini);

// token.c

t_token	*create_token(char *str, int type, t_mini *mini);
void	add_token(t_token **head, t_token **last, t_token *new_token);
t_token	*tokenize(char *line, t_mini *mini);
void	ft_printlist(t_token *token);
void	free_tokens(t_token *token);

//		SETUP

// utils_setup.c

int		size_var(t_var **tab);
int		size_tab(char **env);
void	print_tab(t_var **tab);

// search_var.c

t_var	**created_tab(char **env, t_mini *mini);
char	*get_value(t_var **tab, char *name);
void	destroy_tab(t_var **tab);

//				ROYAL_BIN

// rb_substr.c
char	*rb_substr(char const *str, unsigned int st, size_t len, t_rb_list *rb);
char	*rb_strfreejoin(char *s1, char *s2, t_rb_list *rb);
char	*rb_strdup(const char *src, t_rb_list *rb);
void	*rb_calloc(size_t count, size_t size, t_rb_list *rb);
char	**rb_split(const char *str, char c, t_rb_list *rb);

// royal_bin.c

void	rb_free_all(t_rb_list *rb);
void	*rb_malloc(size_t size, t_rb_list *rb);

#endif