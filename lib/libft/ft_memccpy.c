/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emayert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:14:09 by emayert           #+#    #+#             */
/*   Updated: 2018/11/23 12:14:11 by emayert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *psrc;
	unsigned char *pdst;

	psrc = (unsigned char *)src;
	pdst = (unsigned char *)dst;
	if (n == 0 || src == dst)
		return (NULL);
	while (n--)
	{
		*pdst = *psrc;
		if (*psrc == (unsigned char)c)
			return (pdst + 1);
		++pdst;
		++psrc;
	}
	return (NULL);
}
