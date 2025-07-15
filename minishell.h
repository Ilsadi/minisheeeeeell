/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:41:44 by ilsadi            #+#    #+#             */
/*   Updated: 2025/07/15 15:55:19 by ilsadi           ###   ########.fr       */
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

typedef struct s_token
{
	char			*arg;
	char			*str;
	int				type;
	struct s_token	*next;
}					t_token;

#endif