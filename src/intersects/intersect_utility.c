/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 15:54:13 by eloren-l          #+#    #+#             */
/*   Updated: 2019/04/14 16:03:16 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	*min_root(double *roots)
{
	if (roots[0] > roots[1])
		return (&roots[1]);
	return (&roots[0]);
}

double	*max_root(double *roots)
{
	if (roots[0] > roots[1])
		return (&roots[0]);
	return (&roots[1]);
}
