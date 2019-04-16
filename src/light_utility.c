/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdibbert <fdibbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 10:08:37 by cschuste          #+#    #+#             */
/*   Updated: 2019/04/16 21:01:38 by fdibbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	max_color(double intens, unsigned char color, int *remain)
{
	*remain = 0;
	if (intens * color > 255)
	{
		*remain = (intens * color - 255) / 3;
		return (255);
	}
	return (intens * color);
}

void			init_new_color(t_clr *new_color, t_surf *surf, t_env *env)
{
	if (surf->disruption > 0 && surf->disruption < 2)
		*new_color = (((int)(1 * env->ray.start.x + 1000) + (int)(1 * env->ray.start.y + 1000)) & 1) ? (t_clr){255 - surf->color.r, 255 - surf->color.g, 255 - surf->color.b} : surf->color;
	else
		*new_color = surf->color;
}

void			calc_color(t_clr *color, double intens,
							t_surf *surface, t_env *env)
{
	int		remain;
	t_clr	new_clr;

	init_new_color(&new_clr, surface, env);
	color->r = max_color(intens, new_clr.r, &remain);
	color->g = new_clr.g + remain > 255 ?
				255 : new_clr.g + remain;
	color->b = new_clr.b + remain > 255 ?
				255 : new_clr.b + remain;
	color->g = max_color(intens, color->g, &remain);
	color->r = color->r + remain > 255 ? 255 : color->r + remain;
	color->b = color->b + remain > 255 ? 255 : color->b + remain;
	color->b = max_color(intens, color->b, &remain);
	color->g = color->g + remain > 255 ? 255 : color->g + remain;
	color->r = color->r + remain > 255 ? 255 : color->r + remain;
}

void			calc_ref_color(t_clr *color, t_clr *ref_color, t_surf *surface)
{
	color->r = color->r * (1 - surface->reflect) + ref_color->r *
				surface->reflect;
	color->g = color->g * (1 - surface->reflect) + ref_color->g *
				surface->reflect;
	color->b = color->b * (1 - surface->reflect) + ref_color->b *
				surface->reflect;
}

t_v				calc_reflected_ray(t_v direction, t_v bisect)
{
	t_v	reflected_ray;

	reflected_ray = vecmult_num(vecmult_num(bisect, 2),
					vecmult_scal(bisect, direction));
	reflected_ray = vecsub(reflected_ray, direction);
	return (reflected_ray);
}

void			init_color_variables(t_env *env, t_lc *lc, double closest)
{
	lc->orig_dest = env->ray.dest;
	lc->to_start = vecmult_num(env->ray.dest, -1);
	lc->surf_point = vecsum(env->ray.start,
		vecmult_num(env->ray.dest, closest));
}
