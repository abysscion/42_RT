/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emayert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 10:45:47 by emayert           #+#    #+#             */
/*   Updated: 2018/11/23 10:45:51 by emayert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *psrc;
	unsigned char *pdst;

	psrc = (unsigned char *)src;
	pdst = (unsigned char *)dst;
	if (n == 0 || src == dst)
		return (dst);
	while (n--)
		*pdst++ = *psrc++;
	return (dst);
}
