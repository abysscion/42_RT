/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 21:03:53 by cschuste          #+#    #+#             */
/*   Updated: 2019/03/07 10:52:03 by cschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static	double			calc_spec(t_env *e, double temp, int i, int obj)
{
	t_lc *lc;

	lc = e->lit_var;
	lc->r = reflect_ray(lc->l, lc->n);
	temp = vecmult_scal(lc->r, lc->v);
	if (temp > 0)
		return (e->light[i]->intensity * pow(temp /
			(veclen(lc->r) * veclen(lc->v)), e->objs->objarr[obj]->specular));
	else
		return (0);
}

static	void			choose_light(t_env *e, int *max, t_lc *lc, int i)
{
	if (!ft_strcmp(e->light[i]->type, "point"))
	{
		*max = 1;
		lc->l = vecsub(e->light[i]->pos, lc->p);
	}
	else
	{
		*max = RAY_LENMAX;
		lc->l = e->light[i]->pos;
	}
}

static	double			compute_light(t_env *e, int obj)
{
	double	intens;
	double	temp;
	int		i;
	int		max;

	light_abuse(&i, &intens);
	while (++i < e->lnum)
	{
		if (!ft_strcmp(e->light[i]->type, "ambient"))
			intens += e->light[i]->intensity;
		else
		{
			choose_light(e, &max, e->lit_var, i);
			if (close_intersection(e, &(t_ren){e->lit_var->p, e->lit_var->l,
				RAY_LENMIN, max}, &e->lit_var->temp) < max)
				continue;
			temp = vecmult_scal(e->lit_var->n, e->lit_var->l);
			if (temp > 0)
				intens += e->light[i]->intensity * temp / (veclen(e->lit_var->n)
					* veclen(e->lit_var->l));
			if (e->objs->objarr[obj]->specular > 0)
				intens += calc_spec(e, temp, i, obj);
		}
	}
	return (intens);
}

unsigned	char		*light_on(t_env *e, t_ren *r_v, double closest, int i, int rec)
{
	t_lc				*light;
	double				intens;
	int					remain;
	unsigned char		*rgb;
	unsigned char		*ref_col;

	light = e->lit_var;
	light->v = vecmult_num(r_v->dest, -1);
	light->p = vecsum(r_v->start, vecmult_num(r_v->dest, closest));
	light->n = vecsub(light->p, e->objs->objarr[i]->pos);
	if (e->objs->objarr[i]->type == T_SPHERE)
		light->n = vecsub(light->p, e->objs->objarr[i]->pos);
	if (e->objs->objarr[i]->type == T_PLANE)
		light->n = normal2plane(e, i);
	if (e->objs->objarr[i]->type == T_CYLINDER)
		light->n = normal2cyl(e, r_v->dest, closest, i);
	if (e->objs->objarr[i]->type == T_CONE)
		light->n = normal2cone(e, r_v->dest, closest, i);
	light->n = vecnorm(light->n);
	intens = compute_light(e, i);
	rgb = (unsigned char *)malloc(sizeof(unsigned char) * 3);
	/**
	 ** For good specular and reflection. I will norme it after adding transparency
	 */
	rgb[0] = max_color(intens, e->objs->objarr[i]->colour[0], &remain);
	rgb[1] = (e->objs->objarr[i]->colour[1] + remain) > 255 ? 255 : e->objs->objarr[i]->colour[1] + remain;
	rgb[2] = (e->objs->objarr[i]->colour[2] + remain) > 255 ? 255 : e->objs->objarr[i]->colour[2] + remain;
	limit_specular(rgb, remain, intens);
	if (rec <= 0 || e->objs->objarr[i]->reflect <= 0)
		return (rgb);
	ref_col = trace_ray(&(t_ren){light->p, reflect_ray(light->v, light->n),
				RAY_LENMIN, RAY_LENMAX}, e, rec - 1);
	count_rgb(rgb, ref_col, e, i);
	free (ref_col);
	return (rgb);
}


