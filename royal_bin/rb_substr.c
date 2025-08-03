/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsadi <ilsadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:55:05 by ilsadi            #+#    #+#             */
/*   Updated: 2025/08/03 23:21:19 by ilsadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*rb_substr(char const *str, unsigned int st, size_t len, t_rb_list *rb)
{
	size_t	i;
	char	*tab;

	i = 0;
	if (st >= ft_strlen(str))
	{
		tab = rb_malloc(sizeof(char) * 1, rb);
		if (!tab)
			return (NULL);
		tab[0] = '\0';
		return (tab);
	}
	if (ft_strlen(str + st) < len)
		len = ft_strlen(str + st);
	tab = rb_malloc(sizeof(char) * (len + 1), rb);
	if (!tab)
		return (NULL);
	while (i < len)
	{
		tab[i] = str[st + i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	*rb_strfreejoin(char *s1, char *s2, t_rb_list *rb)
{
	int		i;
	int		j;
	char	*s3;

	if (!s1)
	{
		s1 = rb_malloc(sizeof(char) * 1, rb);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	s3 = rb_malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char), rb);
	if (!s3)
		return (NULL);
	i = -1;
	while (s1[++i])
		s3[i] = s1[i];
	j = 0;
	while (s2[j])
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return (s3);
}

char	*rb_strdup(const char *src, t_rb_list *rb)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = rb_malloc(sizeof(char) * ft_strlen(src) + 1, rb);
	if (!dest)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	*rb_calloc(size_t count, size_t size, t_rb_list *rb)
{
	void	*buffer;

	if (count != 0 && size > (size_t) - 1 / count)
		return (NULL);
	if (count == 0 || size == 0)
		buffer = rb_malloc(0, rb);
	else
		buffer = rb_malloc(count * size, rb);
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, count * size);
	return (buffer);
}

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