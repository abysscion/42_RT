/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emayert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 13:20:28 by emayert           #+#    #+#             */
/*   Updated: 2018/12/03 13:22:33 by emayert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		get_len(char const *str, char c)
{
	int	len;

	len = 0;
	while (*str == c)
		++str;
	while (*str != c && *str != '\0')
	{
		++str;
		++len;
	}
	return (len);
}

static	char	**free_some_shit(int i, char **arr)
{
	while (--i >= 0)
		free(arr[i]);
	return (NULL);
}

static	void	abuse_norminette(int *i, int *j)
{
	*i = -1;
	*j = 0;
}

static	char	**crutch(char **str2, int i)
{
	str2[i] = NULL;
	str2[0] = *free_some_shit(i, str2);
	return (str2);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**str2;
	int		i;
	int		j;
	int		k;
	int		wn;

	if (s)
		wn = ft_wordsnum(s, c);
	else
		return (NULL);
	if (!(str2 = (char **)malloc(sizeof(*str2) * (wn + 1))))
		return (NULL);
	abuse_norminette(&i, &j);
	while (++i < wn && !(k = 0))
	{
		if (!(str2[i] = ft_strnew(get_len(&s[j], c) + 1)))
			return (crutch(str2, i));
		while (s[j] == c)
			++j;
		while (s[j] != c && s[j])
			str2[i][k++] = s[j++];
		str2[i][k] = '\0';
	}
	str2[i] = 0;
	return (str2);
}
