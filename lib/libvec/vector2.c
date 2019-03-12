/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 10:49:41 by cschuste          #+#    #+#             */
/*   Updated: 2019/03/07 07:00:26 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

double	vecmult_scal(t_v v1, t_v v2)
{
	double	ret;

	ret = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (ret);
}

t_v		vecdiv_num(t_v v, double num)
{
	t_v res;

	res.x = v.x / num;
	res.y = v.y / num;
	res.z = v.z / num;
	return (res);
}

t_v		vecnorm(t_v v)
{
	double	n;

	n = 1.0 / sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v = (t_v) {v.x * n, v.y * n, v.z * n};
	return (v);
}

/*
**	Returns vector rotated by radian angles stored in (t_v) a.
*/

t_v		vec_rotate(t_v a, t_v vec)
{
	t_v	retv;
	t_v temp;

	temp = vec;
	retv.x = temp.x;
	retv.y = temp.y * cos(a.x) - temp.z * sin(a.x);
	retv.z = temp.y * sin(a.x) + temp.z * cos(a.x);
	temp = retv;
	retv.x = temp.x * cos(a.y) + temp.z * sin(a.y);
	retv.y = temp.y;
	retv.z = -temp.x * sin(a.y) + temp.z * cos(a.y);
	return (retv);
}
