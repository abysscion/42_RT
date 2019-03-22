/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 05:21:02 by emayert           #+#    #+#             */
/*   Updated: 2019/03/21 20:40:38 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rt.h"

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
    t_clr   ref_color;
    t_v     trans_vec;
    double  closest;

    if ((refract(lc.orig_dest, lc.orig_norm, &trans_vec,
			((t_surf *)surface->obj)->transp)) == 1)
		{
			env->ray.start = lc.surf_point;
			env->ray.dest = trans_vec;
			env->ray.min = RAY_LENMIN;
			env->ray.max = RAY_LENMAX;
			closest = closest_intersection(env, NULL);
			lc.surf_point = vecsum(env->ray.start, vecmult_num(env->ray.dest, closest));
			calc_surf_normal(env, closest, surface, &lc);
			if ((refract(env->ray.dest, lc.surf_normal, &trans_vec,
				((t_surf *)surface->obj)->transp)) == 1)
			{
				env->ray.start = lc.surf_point;
				env->ray.dest = trans_vec;
				env->ray.min = RAY_LENMIN;
				env->ray.max = RAY_LENMAX;
				ref_color = trace_ray(env, rec - 1);
				return (ref_color);
			}
			env->ray.dest = lc.orig_dest;
			ref_color = trace_ray(env, rec - 1);
			return (ref_color);
		}
		else
		{
			env->ray.start = lc.surf_point;
			env->ray.dest = calc_reflected_ray(lc.to_start, lc.surf_normal);
			env->ray.min = RAY_LENMIN;
			env->ray.max = RAY_LENMAX;
			ref_color = trace_ray(env, rec - 1);
			return (ref_color);
		}
}