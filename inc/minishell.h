#ifndef MINISHELL_H

# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/wait.h>
# include <termios.h> // a verifier si autorise
# include <limits.h> // a verifier si autorise

# define CMD 1
# define ARG 2
# define PIPE 3
# define HEREDOC 4
# define APPEND 5
# define INPUT 6
# define TRUNC 7
# define TMP_SPACE 8

# define NOT_CMD ": command not found\n"
# define ERROR_NEWLINE "syntax error near unexpected token `newline'\n"
# define ERROR_ENEXPECTED_SLASH "\n"

extern int						g_in_cmd;
extern volatile sig_atomic_t	g_sig;

// typedef struct s_redir
// {
// 	char						*str;
// 	int							type;
// 	struct t_redir				*next;
// };

typedef struct s_token
{
	char						*str;
	int							type;
	struct t_redir				*redir;
	struct s_token				*next;
}								t_token;

typedef struct s_pipex
{
	int							infile;
	int							outfile;
	pid_t						pid1;
	pid_t						pid2;
	int							pipefd[2];
	int							fd_in;
	int							fd_out;
	int							cmd_start;
	char						**cmd1;
	char						**cmd2;
}								t_pipex;

typedef struct s_var
{
	char						*name;
	char						*value;
}								t_var;

typedef struct s_mini
{
	struct s_token				*first;
	struct s_rb_list			*rb;
	struct s_var				**env;
	int							exit_status;
	int							in_pipeline;
}								t_mini;

typedef struct s_rb_node
{
	void						*ptr;
	struct s_rb_node			*next;
}								t_rb_node;

typedef struct s_rb_list
{
	t_rb_node					*head;
}								t_rb_list;

typedef struct s_export_ctx
{
	char	*equal_pos;
	char	*name;
	char	*value;
	int		status;
}			t_export_ctx;

typedef struct s_child_ctx
{
	t_pipex	*p;
	t_token	*tokens;
	t_mini	*mini;
	char	**envp;
	char	**cmd_args;
	char	*cmd_path;
}	t_child_ctx;

typedef struct s_loop_ctx
{
	t_pipex		*pipex;
	t_token		*current;
	t_mini		*mini;
	pid_t		*tab_pid;
	char		**envp;
	int			nb_pipes;
	int			i;
}	t_loop_ctx;

typedef struct s_loop_init
{
	t_pipex	*pipex;
	t_token	*tokens;
	t_mini	*mini;
	pid_t	*tab_pid;
}	t_loop_init;

typedef struct s_tokctx
{
	t_token	**head;
	t_token	**cur;
} t_tokctx;

//		EXEEEEEC

//	signaux

// ctrl.c
void							sigint_handler(int sig);
void							setup_signals(void);
void							setup_child_signals(void);
int								execute_command(char **args, char **envp);
int								print_exit_error(char *str, int code);

// echo_terms.c
void							disable_signal_echo(void);
//	input_trunc.c

int								handle_redirections(t_token *tokens, int stop);

//	pipex

// pipex_pars.c

char							*find_cmd_path(char *cmd, t_mini *mini);

// pipex_mini.c
void							fill_cmd_args(char **cmd, t_token *start, t_mini *mini);
int								count_cmd_args(t_token *start);
int								is_redir_token(int type);
int								has_pipe(t_token *tokens);
void							execute_pipeline(t_mini *mini, t_pipex *pipex);
char							**token_to_cmd(t_token **current, t_mini *mini);

// pipex_utils.c

void							close_test(int fd);
void							close_all(t_pipex *pipex);
void							ft_error_exit(const char *msg);
int								choose_out(t_pipex *pipex);
char							**var_to_envp(t_var **var);

// pipex_bonus.c
void	ft_child_pro(t_pipex *p, t_token *tokens, char **envp, t_mini *mini);
void							ft_pipex_loop(t_pipex *pipex, t_token *tokens,
									t_mini *mini, pid_t *tab_pid);

// pipex_utils.c

void							close_test(int fd);
void							close_all(t_pipex *pipex);
void							ft_error_exit(const char *msg);
char							**var_to_envp(t_var **var);

//	built_in

// built_in .c

int								is_builtins(t_token *first);
int								builtin_with_redir(t_token *first, t_mini *mini,
									t_pipex *p);

// echo.c

int								ft_echo(t_token *token);

// env.c

int								env(t_mini *mini);

// pwd.c

int								pwd(t_token *tokens);

// cd.c

int								cd(t_token *token, t_mini *mini);

// unset.c

t_var							**unset_var(t_var **tab, char *name);
int								unset(t_token *token, t_mini *mini);

// export.c
void							expand_tokens(t_token **tokens, t_mini *mini);
void							update_or_add_var(t_mini *mini, char *name,
									char *value);
t_var							**add_var(t_var **tab, t_var *new_var);
int								ft_export(t_token *token, t_mini *mini);

// exit.c

int								ft_exit(t_token *token, t_mini *mini);

//	commands.c

void							ft_commands(t_mini *mini);

//		PAAAAAARSING

// ampersand.c

int								pars_ampersand(char *str);

// error.c

void							ft_error(char *msg);
void							command_not_found(char *cmd);
void							is_a_directory(char *cmd);

// quotes.c

int								pars_quotes(char *str);
int								char_is_operator(char c);

// redirections.c

int								is_operator(char str);
int								pars_redir(char *str);

// slash.c

int								is_word(char c);
int								pars_slash(char *str);

// pipe.c

int								pars_pipe(char *str);

// parsing.c
int								str_ends_with_slash(char *s);
void							parsing(char *str, t_mini *mini, t_pipex *p);
void							free_token_list(t_token *token);
void							restore_operators(char *str);
char							*remove_quotes(const char *str, t_mini *mini);
int								is_only_spaces(char *str);

// expand.c

char							*pars_expand(char *str, t_mini *mini);

// token.c

t_token							*create_token(char *str, int type,
									t_mini *mini);
void							add_token(t_token **head, t_token **last,
									t_token *new_token);
t_token							*tokenize(char *line, t_mini *mini);
void							ft_printlist(t_token *token);
void							free_token(t_token *token);

//		SETUP

// utils_setup.c

int								size_var(t_var **tab);
int								size_tab(char **env);
void							print_tab(t_var **tab);

// search_var.c

t_var							**created_tab(char **env);
char							*get_value(t_var **tab, char *name);
void							destroy_tab(t_var **tab);

//				ROYAL_BIN

// rb_substr.c
char							*rb_substr(char const *str, unsigned int st,
									size_t len, t_rb_list *rb);
char							*rb_strfreejoin(char *s1, char *s2,
									t_rb_list *rb);
char							*rb_strdup(const char *src, t_rb_list *rb);
void							*rb_calloc(size_t count, size_t size,
									t_rb_list *rb);
char							**rb_split(const char *str, char c,
									t_rb_list *rb);
char							*rb_itoa(int n, t_rb_list *rb);

// royal_bin.c

void							rb_free_all(t_rb_list *rb);
void							*rb_malloc(size_t size, t_rb_list *rb);

#endif