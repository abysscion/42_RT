/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emayert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 16:00:26 by emayert           #+#    #+#             */
/*   Updated: 2018/11/27 16:00:30 by emayert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*begin;
	const char	*str;
	int			l;

	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack)
	{
		l = (int)len;
		begin = haystack;
		str = needle;
		while (*haystack && *str && *haystack == *str && l--)
		{
			++haystack;
			++str;
		}
		if (l < 0)
			return (NULL);
		if (*str == '\0')
			return ((char *)begin);
		haystack = ++begin;
		--len;
	}
	return (NULL);
}
