# **************************************************************************** #
#                                  VARIABLES                                   #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -g3 

SRCS = main.c \
	paaaaarsing/redirections.c \
	paaaaarsing/quotes.c \
	paaaaarsing/slash.c \
	paaaaarsing/parsing.c \
	paaaaarsing/pipe.c \

OBJS = ${SRCS:.c=.o}

NAME = minishell

LIBFT = libft/libft.a

INC = minishell.h

all: $(NAME)

libft/libft.a:
	@$(MAKE) -C libft


%.o: %.c $(INC)
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
