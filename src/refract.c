/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 05:21:02 by emayert           #+#    #+#             */
/*   Updated: 2019/04/11 15:17:48 by cschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	t_clr	colorize(t_clr reflect, t_clr refract, double kr)
{
	 t_clr color;

	 color.r = reflect.r * kr + refract.r * (1 - kr);
	 color.g = reflect.g * kr + refract.b * (1 - kr);
	 color.b = reflect.g * kr + refract.b * (1 - kr);
	 return (color);
}

static	double	max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

static	void	fresnel(t_v dest, t_v norm, double refr, double *kr)
{
	double cosi;
	double etai;
	double etat;
	double sint;
	double cost;

	cosi = vecmult_scal(vecnorm(dest), norm);
	etai = 1;
	etat = refr;
	if (cosi > 0)
	{
		sint = etai;
		etai = etat;
		etat = sint;
	}
	sint = etai / etat * sqrt(max(0.0, 1 - cosi * cosi));
	if (sint >= 1)
		*kr = 1;
	else
	{
		cost = sqrt(max(0.0, 1 - sint * sint));
		cosi = fabs(cosi);
		sint = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etat * cost));
		cost = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		*kr = (sint * sint + cost * cost) / 2;
	}
}

static	int		refract(t_v dest, t_v norm, t_v *ref_ray, double refr)
{
	double	cosi;
	double	etai;
	double	etat;
	t_v		n;

	cosi = vecmult_scal(vecnorm(dest), norm);
	etai = 1;
	etat = refr;
	n = norm;
	if (cosi < 0)
		cosi = -cosi;
	else
	{
		etai = etat;
		etat = 1;
		n = vecmult_num(norm, -1);
	}
	etai = etai / etat;
	etat = 1 - etai * etai * (1 - cosi * cosi);
	if (etat < 0)
		return (0);
	else
	{
		n = vecmult_num(n, (etai * cosi - sqrt(etat)));
		*ref_ray = vecsum(vecmult_num(dest, etai), n);
		return (1);
	}
}

t_clr   calc_refract(t_env *env, t_lc lc, t_lst *surface, int rec)
{
	t_clr	refr_color;
	t_clr	refl_color;
	t_v		trans_vec;
	int		temp;
	// double	kr;

	// kr = 0;
	refr_color = (t_clr){0, 0, 0};
	// fresnel(lc.orig_dest, lc.orig_norm, ((t_surf *)surface->obj)->transp, &kr);
	env->ray.start = lc.surf_point;
	env->ray.min = RAY_LENMIN;
	env->ray.max = RAY_LENMAX;
	// if (kr < 1)
	// {
		temp = refract(lc.orig_dest, lc.orig_norm, &trans_vec, ((t_surf *)surface->obj)->transp);
		if (temp == 0)
		{
			env->ray.dest = calc_reflected_ray(lc.orig_norm, lc.orig_dest);
			refl_color = trace_ray(env, rec - 1);
			return (refl_color);
		}
		env->ray.dest = trans_vec;
		refr_color = trace_ray(env, rec - 1);
		return (refr_color);
	// }
	// return (colorize(refl_color, refr_color, kr));
}
