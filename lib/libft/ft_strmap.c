/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emayert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 16:36:28 by emayert           #+#    #+#             */
/*   Updated: 2018/12/01 16:37:33 by emayert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char *ret;
	char *tgt;

	if (s == NULL || f == NULL)
		return (NULL);
	if (!(ret = (char *)malloc(ft_strlen(s) + 1)))
		return (NULL);
	tgt = ret;
	while (*s)
		*tgt++ = f((char)*s++);
	*tgt = '\0';
	return (ret);
}
