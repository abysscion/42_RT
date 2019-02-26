/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emayert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 17:06:28 by emayert           #+#    #+#             */
/*   Updated: 2018/12/01 17:07:33 by emayert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ret;
	char			*tgt;

	if (s == NULL || f == NULL)
		return (NULL);
	if (!(ret = (char *)malloc(ft_strlen(s) + 1)))
		return (NULL);
	tgt = ret;
	i = 0;
	while (*s)
		*tgt++ = f(i++, (char)*s++);
	*tgt = '\0';
	return (ret);
}
