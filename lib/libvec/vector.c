/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emayert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 17:25:00 by emayert           #+#    #+#             */
/*   Updated: 2019/02/04 17:25:30 by emayert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

t_v		vecmult_num(t_v v, double num)
{
	t_v retv;

	retv = (t_v) {v.x * num, v.y * num, v.z * num};
	return (retv);
}

t_v		vecmult_vec(t_v v1, t_v v2)
{
	t_v retv;

	retv.x = v1.y * v2.z - v1.z * v2.y;
	retv.y = -(v1.x * v2.z - v1.z * v2.x);
	retv.z = v1.x * v2.y - v1.y * v2.x;
	return (retv);
}

t_v		vecsum(t_v v1, t_v v2)
{
	t_v retv;

	retv = (t_v) {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
	return (retv);
}

t_v		vecsub(t_v v1, t_v v2)
{
	t_v retv;

	retv = (t_v) {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
	return (retv);
}

double	veclen(t_v v)
{
	double	ret;

	ret = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	return (ret);
}
