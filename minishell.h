/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:41:44 by ilsadi            #+#    #+#             */
/*   Updated: 2025/07/17 12:31:55 by ilsadi           ###   ########.fr       */
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
	char			*arg;
	char			*str;
	int				type;
	struct s_token	*next;
}					t_token;

//		PAAAAAARSING

// quotes.c

int		doubles_quotes_is_closed(char *str);
int		quotes_is_closed(char *str);

// redirections.c

int		is_operator(char *str);
int		pars_redir(char *str);
int		redirection(char *str);

// slash.c

int		is_word(char c);
int		pars_slash(char *str);

// pipe.c

int		pars_pipe(char *str);

// parsing.c

int		parsing(char *str);


#endif