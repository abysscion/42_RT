/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emayert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 16:06:28 by emayert           #+#    #+#             */
/*   Updated: 2018/11/21 16:06:33 by emayert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t		len;
	char		*str;
	char		*ret;
	const char	*buf;

	len = 0;
	buf = s1;
	while (*s1++)
		len++;
	if (!(str = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	ret = str;
	while (*buf)
		*str++ = *buf++;
	ret[len] = '\0';
	return (ret);
}
