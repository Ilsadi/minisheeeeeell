# **************************************************************************** #
#                                  VARIABLES                                   #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -g3 $(addprefix -I, $(INC))

SRCS = main.c \
	paaaaarsing/redirections.c \
	paaaaarsing/quotes.c \
	paaaaarsing/slash.c \
	paaaaarsing/parsing.c \
	paaaaarsing/pipe.c \
	paaaaarsing/expand.c \
	paaaaarsing/error.c \
	paaaaarsing/ampersand.c \
	paaaaarsing/token.c \
	exeeeeec/built_in/built_in.c \
	exeeeeec/built_in/pwd.c \
	exeeeeec/built_in/echo.c \
	exeeeeec/built_in/env.c \
	exeeeeec/built_in/cd.c \
	exeeeeec/built_in/exit.c \
	exeeeeec/built_in/unset.c \
	exeeeeec/built_in/export.c \
	exeeeeec/pipex/pipex_bonus.c \
	exeeeeec/pipex/pipex_utils.c \
	exeeeeec/pipex/pipex_mini.c \
	exeeeeec/pipex/pipex_pars.c \
	exeeeeec/commands.c \
	exeeeeec/input_trunc.c \
	exeeeeec/signaux/ctrl.c \
	exeeeeec/signaux/echo_term.c \
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
