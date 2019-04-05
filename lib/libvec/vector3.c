/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 23:38:43 by eloren-l          #+#    #+#             */
/*   Updated: 2019/04/04 22:50:10 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

static void	rotate_x(double angle, t_v *vec)
{
	t_v		temp;
	double	rad;
	double	cosine;
	double	sine;

	temp = *vec;
	rad = M_PI / 180 * angle;
	cosine = cos(rad);
	sine = sin(rad);
	vec->x = temp.x;
	vec->y = temp.y * cosine - temp.z * sine;
	vec->z = temp.y * sine + temp.z * cosine;
}

static void	rotate_y(double angle, t_v *vec)
{
	t_v		temp;
	double	rad;
	double	cosine;
	double	sine;

	temp = *vec;
	rad = M_PI / 180 * angle;
	cosine = cos(rad);
	sine = sin(rad);
	vec->x = temp.x * cosine + temp.z * sine;
	vec->y = temp.y;
	vec->z = -temp.x * sine + temp.z * cosine;
}

static void	rotate_z(double angle, t_v *vec)
{
	t_v		temp;
	double	rad;
	double	cosine;
	double	sine;

	temp = *vec;
	rad = M_PI / 180 * angle;
	cosine = cos(rad);
	sine = sin(rad);
	vec->x = temp.x * cosine - temp.y * sine;
	vec->y = temp.x * sine + temp.y * cosine;
}

t_v			vec_rotate(t_v angle, t_v vec)
{
	rotate_x(angle.x, &vec);
	rotate_y(angle.y, &vec);
	rotate_z(angle.z, &vec);
	return (vec);
}
