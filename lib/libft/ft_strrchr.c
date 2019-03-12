/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emayert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 12:23:28 by emayert           #+#    #+#             */
/*   Updated: 2018/11/27 12:23:31 by emayert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char *p;

	p = s;
	while (*s)
		s++;
	while (p <= s)
		if (*s-- == (char)c)
			return ((char *)++s);
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}
