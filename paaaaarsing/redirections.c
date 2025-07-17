/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:25:41 by ilsadi            #+#    #+#             */
/*   Updated: 2025/07/17 14:52:03 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_operator(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
			return (1);
		else if (str[i] == '>' && str[i + 1] == '>')
			return (1);
		else if (str[i] == '>' || str[i] == '<')
			return (1);
		else if (str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	pars_redir(char *str)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (str[i])
	{
		if ((str[i] == '<' && str[i + 1] == '<')
			|| (str[i] == '>' && str[i + 1] == '>'))
		{
			found = 1;
			i += 2;
			while ((str[i] == ' ' || str[i] == '\t') && str[i] != '\0')
				i++;
			if (str[i] != '\0' && !is_operator(&str[i]))
				return (1);
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			found = 1;
			i++;
			while ((str[i] == ' ' || str[i] == '\t') && str[i] != '\0')
				i++;
			if (str[i] != '\0' && !is_operator(&str[i]))
				return (1);
		}
		i++;
	}
	if (found)
	{
		if (str[i] == '\0')
		{
			ft_putstr_fd(ERROR_NEWLINE, 2);
			return (0);
		}
		else if (str[i] == '<' && str[i + 1] == '<')
		{
			ft_putstr_fd("bash: syntax error near unexpected token `<<'\n", 2);
			return (0);
		}
		else if (str[i] == '>' && str[i + 1] == '>')
		{
			ft_putstr_fd("bash: syntax error near unexpected token `>>'\n", 2);
			return (0);
		}
		else
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", 2);
			ft_putchar_fd(str[i], 2);
			ft_putstr_fd("'\n", 2);
			return (0);
		}
	}
	return (1);
}

// int	redirection(char *str)
// {
// 	if (!pars_redir(str))
// 		return (0);
// 	return (1);
// }
