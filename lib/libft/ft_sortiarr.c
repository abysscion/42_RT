/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sortiarr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emayert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 12:31:48 by emayert           #+#    #+#             */
/*   Updated: 2018/12/11 12:31:57 by emayert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_sortiarr(int *ptarr, int len)
{
	int temp;
	int i;
	int d;

	i = -1;
	while (++i < len)
	{
		d = -1;
		while (++d < len)
		{
			if (ptarr[d] > ptarr[d + 1])
			{
				temp = ptarr[d];
				ptarr[d] = ptarr[d + 1];
				ptarr[d + 1] = temp;
			}
		}
	}
}
