/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emayert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:06:28 by emayert           #+#    #+#             */
/*   Updated: 2018/11/26 17:07:33 by emayert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		i;
	size_t		dstlen;

	if ((!src || !dst) && dstsize + 1 < dstsize)
		return (0);
	i = -1;
	dstlen = ft_strlen(dst);
	if (dstsize <= dstlen)
		return (ft_strlen(src) + dstsize);
	while (++i < dstsize - dstlen - 1)
		dst[dstlen + i] = src[i];
	dst[dstlen + i] = '\0';
	return (dstlen + ft_strlen(src));
}
