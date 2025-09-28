# **************************************************************************** #
#                                  VARIABLES                                   #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -g3 -I./inc

SRCS = main.c \
	paaaaarsing/redirections.c \
	paaaaarsing/quotes.c \
	paaaaarsing/pipe.c \
	paaaaarsing/expand.c \
	paaaaarsing/parsing.c \
	paaaaarsing/pars_fork_run.c \
	paaaaarsing/pars_utils1.c \
	paaaaarsing/pars_utils2.c \
	paaaaarsing/pars_utils3.c \
	paaaaarsing/expand_utils.c \
	paaaaarsing/error.c \
	paaaaarsing/ampersand.c \
	paaaaarsing/token.c \
	paaaaarsing/token_ops.c \
	paaaaarsing/token_lex_utils.c \
	paaaaarsing/token_lex.c \
	exeeeeec/built_in/built_in.c \
	exeeeeec/built_in/pwd.c \
	exeeeeec/built_in/echo.c \
	exeeeeec/built_in/env.c \
	exeeeeec/built_in/cd.c \
	exeeeeec/built_in/cd_path_utils.c \
	exeeeeec/built_in/cd_env_utils.c \
	exeeeeec/built_in/exit.c \
	exeeeeec/built_in/exit_numeric.c \
	exeeeeec/built_in/unset.c \
	exeeeeec/built_in/export.c \
	exeeeeec/built_in/export_print.c \
	exeeeeec/built_in/export_vars.c \
	exeeeeec/built_in/export_assign.c \
	exeeeeec/built_in/export_validate.c \
	exeeeeec/pipex/pipex_bonus.c \
	exeeeeec/pipex/pipex_child_utils.c \
	exeeeeec/pipex/pipex_redir_utils.c \
	exeeeeec/pipex/pipex_loop.c \
	exeeeeec/pipex/pipex_utils.c \
	exeeeeec/pipex/pipex_mini.c \
	exeeeeec/pipex/pipex_pars.c \
	exeeeeec/commands.c \
	exeeeeec/redirs/redir_io.c \
	exeeeeec/redirs/heredoc.c \
	exeeeeec/input_trunc.c \
	exeeeeec/signaux/signaux.c \
	exeeeeec/signaux/signaux_heredoc.c \
	royal_bin/royal_bin.c \
	royal_bin/rb_utils.c\
	royal_bin/rb_itoa.c \
	royal_bin/rb_split.c \
	setup/utils_setup.c \
	setup/search_var.c \

OBJS = ${SRCS:.c=.o}

NAME = minishell

LIBFT = libft/libft.a

INC = . ./libft/includes

all: $(NAME)

libft/libft.a:
	@$(MAKE) -C libft


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) 
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

clean:
	@rm -f $(OBJS)
	@make -C libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean

re: fclean all
