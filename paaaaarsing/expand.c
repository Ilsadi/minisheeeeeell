/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:52:04 by ilsadi            #+#    #+#             */
/*   Updated: 2025/07/26 01:26:42 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dollar_no_var(char **result, const char *str, int last_pos, int start)
{
	char	*tmp;

	if (start - 1 - last_pos > 0)
	{
		tmp = ft_substr(str, last_pos, start - 1 - last_pos);
		*result = ft_strfreejoin(*result, tmp);
		free(tmp);
	}
	tmp = ft_substr(str, start - 1, 1);
	*result = ft_strfreejoin(*result, tmp);
	free(tmp);
}

// char	*pars_expand(char *str, char **envp)
// {
// 	int		i;
// 	int		start;
// 	char	*varname;
// 	int		j;
// 	char	*result;
// 	char	*tmp;
// 	int		last_pos;

// 	i = 0;
// 	last_pos = 0;
// 	result = ft_strdup("");
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			i++;
// 			start = i;
// 			while (ft_isalnum(str[i]) || str[i] == '_')
// 				i++;
// 			if (i == start)
// 			{
// 				dollar_no_var(&result, str, last_pos, start);
// 				last_pos = i;
// 				continue ;
// 			}
// 			tmp = ft_substr(str, last_pos, start - 1 - last_pos);
// 			result = ft_strfreejoin(result, tmp);
// 			free(tmp);
// 			varname = ft_substr(str, start, i - start);
// 			tmp = ft_strdup("");
// 			j = 0;
// 			while (envp[j])
// 			{
// 				if (strncmp(envp[j], varname, ft_strlen(varname)) == 0
// 					&& envp[j][ft_strlen(varname)] == '=')
// 				{
// 					free(tmp);
// 					tmp = ft_strdup(envp[j] + ft_strlen(varname) + 1);
// 					break ;
// 				}
// 				j++;
// 			}
// 			result = ft_strfreejoin(result, tmp);
// 			free(tmp);
// 			free(varname);
// 			last_pos = i;
// 			continue ;
// 		}
// 		i++;
// 	}
// 	tmp = ft_substr(str, last_pos, ft_strlen(str) - last_pos);
// 	result = ft_strfreejoin(result, tmp);
// 	free(tmp);
// 	return (result);
// }
			
char	*pars_expand(char *str, t_var **tab)
{
	int		i;
	int		start;
	char	*varname;
	char	*result;
	char	*tmp;
	int		last_pos;

	i = 0;
	last_pos = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			start = i;
			while (ft_isalnum(str[i]) || str[i] == '_')
				i++;
			if (i == start)
			{
				dollar_no_var(&result, str, last_pos, start);
				last_pos = i;
				continue ;
			}
			tmp = ft_substr(str, last_pos, start - 1 - last_pos);
			result = ft_strfreejoin(result, tmp);
			free(tmp);
			varname = ft_substr(str, start, i - start);
			printf("Recherche de la variable : '%s'\n", varname);
			tmp = get_value(tab, varname);
			if (tmp)
				result = ft_strfreejoin(result, tmp);
			free(varname);
			last_pos = i;
			continue ;
		}
		i++;
	}
	tmp = ft_substr(str, last_pos, ft_strlen(str) - last_pos);
	result = ft_strfreejoin(result, tmp);
	free(tmp);
	return (result);
}