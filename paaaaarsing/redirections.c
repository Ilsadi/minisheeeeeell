/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:25:41 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/24 16:13:10 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char str)
{
	if (str == '>' || str == '<')
		return (1);
	else if (str == '|')
		return (1);
	return (0);
}

static int	error_redir(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (ft_putstr_fd(ERROR_NEWLINE, 2), 0);
	else if (str[i] == '<' && str[i + 1] == '<')
	{
		ft_putstr_fd("syntax error near unexpected token `<<'\n", 2);
		return (0);
	}
	else if (str[i] == '>' && str[i + 1] == '>')
	{
		ft_putstr_fd("syntax error near unexpected token `>>'\n", 2);
		return (0);
	}
	else if (is_operator(str[i]))
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putchar_fd(str[i], 2);
		ft_putstr_fd("'\n", 2);
		return (0);
	}
	return (1);
}

static int	error_redir2(char *str)
{
	int	i;

	i = 0;
	while ((str[i] == ' ' || str[i] == '\t') && str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		ft_putstr_fd(ERROR_NEWLINE, 2);
		return (0);
	}
	else if (is_operator(str[i]))
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putchar_fd(str[i], 2);
		ft_putstr_fd("'\n", 2);
		return (0);
	}
	return (1);
}

int	pars_redir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '<' && str[i + 1] == '<')
			|| (str[i] == '>' && str[i + 1] == '>'))
		{
			i += 2;
			while ((str[i] == ' ' || str[i] == '\t')
				&& str[i] != '\0')
				i++;
			if (!error_redir(str + i))
				return (0);
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			i++;
			if (!error_redir2(str + i))
				return (0);
		}
		else
			i++;
	}
	return (1);
}
