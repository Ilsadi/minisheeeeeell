/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:09:17 by ilsadi            #+#    #+#             */
/*   Updated: 2025/09/07 17:09:17 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_words(const char *str, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*str == c)
			in_word = 0;
		str++;
	}
	return (count);
}

static char	*rb_get_next_word(const char **str, char c, size_t *len)
{
	while (**str == c)
		(*str)++;
	*len = 0;
	while ((*str)[*len] && (*str)[*len] != c)
		(*len)++;
	return ((char *)*str);
}

static int	rb_fill_result(char **result, const char *str, char c,
		t_rb_list *rb)
{
	size_t	i;
	size_t	len;
	char	*word;

	i = 0;
	while (*str)
	{
		word = rb_get_next_word(&str, c, &len);
		if (len > 0)
		{
			result[i] = rb_malloc(len + 1, rb);
			if (!result[i])
				return (0);
			ft_strlcpy(result[i++], word, len + 1);
			str += len;
		}
	}
	result[i] = NULL;
	return (1);
}

char	**rb_split(const char *str, char c, t_rb_list *rb)
{
	char	**result;
	size_t	count;

	if (!str)
		return (NULL);
	count = count_words(str, c);
	result = rb_malloc((count + 1) * sizeof(char *), rb);
	if (!result)
		return (NULL);
	if (!rb_fill_result(result, str, c, rb))
		return (NULL);
	return (result);
}