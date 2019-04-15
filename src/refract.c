/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 05:21:02 by emayert           #+#    #+#             */
/*   Updated: 2019/04/15 15:27:29 by cschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	int		calc_eta(double *etai, double *etat, double cosi)
{
	*etai = *etai / *etat;
	*etat = 1 - *etai * *etai * (1 - cosi * cosi);
	if (*etat < 0)
		return (0);
	else
		return (1);
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
	if (calc_eta(&etai, &etat, cosi) < 0)
		return (0);
	else
	{
		n = vecmult_num(n, (etai * cosi - sqrt(etat)));
		*ref_ray = vecsum(vecmult_num(dest, etai), n);
		return (1);
	}
}

t_clr			calc_refract(t_env *env, t_lc lc, t_surf *surface, int rec)
{
	t_clr	refr_color;
	t_clr	refl_color;
	t_v		trans_vec;
	int		temp;

	refr_color = (t_clr){0, 0, 0};
	env->ray.start = lc.surf_point;
	env->ray.min = RAY_LENMIN;
	env->ray.max = RAY_LENMAX;
	temp = refract(lc.orig_dest, lc.orig_norm, &trans_vec, surface->transp);
	if (temp == 0)
	{
		env->ray.dest = calc_reflected_ray(lc.orig_norm, lc.orig_dest);
		refl_color = trace_ray(env, rec - 1);
		return (refl_color);
	}
	env->ray.dest = trans_vec;
	refr_color = trace_ray(env, rec - 1);
	return (refr_color);
}
