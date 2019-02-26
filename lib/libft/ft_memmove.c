/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emayert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 15:37:53 by emayert           #+#    #+#             */
/*   Updated: 2018/11/23 15:37:54 by emayert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *psrc;
	unsigned char *pdst;

	psrc = (unsigned char *)src;
	pdst = (unsigned char *)dst;
	if (len == 0)
		return (dst);
	if (src < dst)
	{
		while (len--)
			*(pdst + len) = *(psrc + len);
	}
	else
	{
		while (len--)
			*pdst++ = *psrc++;
	}
	return (dst);
}
