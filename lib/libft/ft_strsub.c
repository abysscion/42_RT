/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emayert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 20:20:28 by emayert           #+#    #+#             */
/*   Updated: 2018/12/02 20:22:33 by emayert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*ret;

	if (s == NULL)
		return (NULL);
	if (!(str = (char*)malloc(len + 1)))
		return (NULL);
	ret = str;
	while (len--)
		*str++ = *(s++ + start);
	*str = '\0';
	str = NULL;
	return (ret);
}
