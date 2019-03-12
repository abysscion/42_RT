/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emayert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 18:00:28 by emayert           #+#    #+#             */
/*   Updated: 2018/12/01 18:12:33 by emayert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	getlen(int n)
{
	int len;

	len = 1;
	if (n < 0)
		++len;
	while (n < -9 || n > 9)
	{
		n /= 10;
		++len;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	unsigned	int	nlen;
	char			*str;
	char			*ret;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nlen = getlen(n);
	if (!(str = (char *)malloc(nlen + 1)))
		return (NULL);
	ret = str;
	if (n < 0)
	{
		*str++ = '-';
		n *= -1;
		--nlen;
	}
	while (nlen--)
	{
		*str++ = n / ft_power(10, nlen) + '0';
		n %= ft_power(10, nlen);
	}
	*str = '\0';
	return (ret);
}
