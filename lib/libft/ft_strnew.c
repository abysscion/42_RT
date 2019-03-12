/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emayert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 14:02:28 by emayert           #+#    #+#             */
/*   Updated: 2018/12/01 14:03:33 by emayert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*p;

	if (size + 1 < size)
		return (NULL);
	if (!(p = ft_memalloc(size + 1)) || size == (size_t)-1)
		return (NULL);
	return (p);
}
