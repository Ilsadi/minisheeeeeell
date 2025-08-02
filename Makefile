# **************************************************************************** #
#                                  VARIABLES                                   #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -g3 -I$(INC)

SRCS = main.c \
	paaaaarsing/redirections.c \
	paaaaarsing/quotes.c \
	paaaaarsing/slash.c \
	paaaaarsing/parsing.c \
	paaaaarsing/pipe.c \
	paaaaarsing/expand.c \
	paaaaarsing/token.c \
	exeeeeec/built_in/built_in.c \
	exeeeeec/built_in/pwd.c \
	exeeeeec/built_in/echo.c \
	exeeeeec/built_in/env.c \
	exeeeeec/built_in/cd.c \
	exeeeeec/built_in/exit.c \
	exeeeeec/built_in/unset.c \
	royal_bin/royal_bin.c \
	royal_bin/rb_substr.c\
	setup/utils_setup.c \
	setup/search_var.c \

OBJS = ${SRCS:.c=.o}

NAME = minishell

LIBFT = libft/libft.a

INC = ./

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
