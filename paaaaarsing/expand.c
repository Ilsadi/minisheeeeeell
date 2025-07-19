/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:52:04 by ilsadi            #+#    #+#             */
/*   Updated: 2025/07/19 14:14:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*pars_expand(char *str, char **envp)
// {
// 	int		i;
// 	int		j;
// 	char	*varname;
// 	int		start;
// 	char	*var_value;
// 	char	*before_var;
// 	char	*after_var;
// 	char	*tmp;
// 	char	*result;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			i++;
// 			start = i;
// 			before_var = ft_substr(str, 0, start - 1);
// 			while (ft_isalnum(str[i]) || str[i] == '_')
// 			{
// 				i++;
// 			}
// 			varname = ft_substr(str, start, i - start);
// 			after_var = ft_substr(str, i, ft_strlen(str) - i);
// 			var_value = "";
// 			j = 0;
// 			while (envp[j])
// 			{
// 				if (strncmp(envp[j], varname, ft_strlen(varname)) == 0 && envp[j][ft_strlen(varname)] == '=')
// 				{
// 					var_value = envp[j] + ft_strlen(varname) + 1;
// 					break;
// 				}
// 				j++;
// 			}
// 			tmp = ft_strfreejoin(before_var, var_value);
// 			result = ft_strfreejoin(tmp, after_var);
// 			free(varname);
// 			return (result);
// 		}
// 		i++;
// 	}
// 	return (ft_strdup(str));
// }

char	*pars_expand(char *str, char **envp)
{
	int		i;
	int		start;
	char	*varname;
	int		j;
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
				if (start - 1 - last_pos > 0)
				{
					tmp = ft_substr(str, last_pos, start - 1 - last_pos);
					result = ft_strfreejoin(result, tmp);
					free(tmp);
				}
				tmp = ft_substr(str, start - 1, 1);
				result = ft_strfreejoin(result, tmp);
				free(tmp);
				last_pos = i;
				continue;
			}
			tmp = ft_substr(str, last_pos, start - 1 - last_pos);
			result = ft_strfreejoin(result, tmp);
			free(tmp);
			varname = ft_substr(str, start, i - start);
			tmp = ft_strdup("");
			j = 0;
			while (envp[j])
			{
				if (strncmp(envp[j], varname, ft_strlen(varname)) == 0 && envp[j][ft_strlen(varname)] == '=')
				{
					free(tmp);
					tmp = ft_strdup(envp[j] + ft_strlen(varname) + 1);
					break;
				}
				j++;
			}
			result = ft_strfreejoin(result, tmp);
			free(varname);
			last_pos = i;
			continue;
		}
		i++;
	}
	tmp = ft_substr(str, last_pos, ft_strlen(str) - last_pos);
	result = ft_strfreejoin(result, tmp);
	free(tmp);
	return (result);
}
