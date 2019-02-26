/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emayert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 12:36:20 by emayert           #+#    #+#             */
/*   Updated: 2018/11/27 12:36:24 by emayert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	while (*haystack)
	{
		if (*haystack == needle[i])
			++i;
		else
		{
			haystack = haystack - i;
			i = 0;
		}
		if (!needle[i])
			return ((char *)(haystack - i + 1));
		++haystack;
	}
	return (NULL);
}
