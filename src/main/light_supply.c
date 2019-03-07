/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_supply.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 10:08:37 by cschuste          #+#    #+#             */
/*   Updated: 2019/03/07 16:19:01 by cschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	max_color(double intens, unsigned char col, int *remain)
{
	*remain = 0;
	if (intens * col > 255)
	{
		*remain = (intens * col - 255)/ 3;
		col = 255;
	}
	else
		col = intens * col;
	return (col);
}

t_v		reflect_ray(t_v l, t_v n)
{
	t_v r;

	r = vecmult_num(vecmult_num(n, 2), vecmult_scal(n, l));
	return (vecsub(r, l));
}

void    limit_specular(unsigned char *rgb, int remain, double intens)
{
	rgb[1] = max_color(intens, rgb[1], &remain);
	rgb[0] = (rgb[0] + remain) > 255 ? 255 : rgb[0] + remain;
	rgb[2] = (rgb[2] + remain) > 255 ? 255 : rgb[2] + remain;
	rgb[2] = max_color(intens, rgb[2], &remain);
	rgb[0] = (rgb[0] + remain) > 255 ? 255 : rgb[0] + remain;
	rgb[1] = (rgb[1] + remain) > 255 ? 255 : rgb[1] + remain;
}

void    count_reflect(unsigned char *rgb, unsigned char *ref_col, t_env *e, int i)
{
	double	reflect;
	double	transp;

	reflect = e->objs->objarr[i]->reflect;
	transp = e->objs->objarr[i]->transp;
	if (transp > 0)
	{
		rgb[0] = rgb[0] * (1 - (reflect + transp)) + ref_col[0] * reflect;
		rgb[1] = rgb[1] * (1 - (reflect + transp)) + ref_col[1] * reflect;
		rgb[2] = rgb[2] * (1 - (reflect + transp)) + ref_col[2] * reflect;
	}
	else
	{
		rgb[0] = rgb[0] * (1 - reflect) + ref_col[0] * reflect;
		rgb[1] = rgb[1] * (1 - reflect) + ref_col[1] * reflect;
		rgb[2] = rgb[2] * (1 - reflect) + ref_col[2] * reflect;
	}
}

void    count_transp(unsigned char *rgb, unsigned char *ref_col, t_env *e, int i)
{
	double	reflect;
	double	transp;

	reflect = e->objs->objarr[i]->reflect;
	transp = e->objs->objarr[i]->transp;
	if (reflect > 0)
	{
		rgb[0] = rgb[0] + ref_col[0] * transp;
		rgb[1] = rgb[1] + ref_col[1] * transp;
		rgb[2] = rgb[2] + ref_col[2] * transp;
	}
	else
	{
		rgb[0] = rgb[0] * (1 - transp) + ref_col[0] * transp;
		rgb[1] = rgb[1] * (1 - transp) + ref_col[1] * transp;
		rgb[2] = rgb[2] * (1 - transp) + ref_col[2] * transp;
	}
}