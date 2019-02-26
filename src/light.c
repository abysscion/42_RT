/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 21:03:53 by cschuste          #+#    #+#             */
/*   Updated: 2019/02/22 20:21:54 by cschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static	double			calc_spec(t_env *e, double temp, int i, int obj)
{
	t_lc *lc;

	lc = e->lit_var;
	lc->r = vecmult_num(vecmult_num(lc->n, 2), vecmult_scal(lc->n, lc->l));
	lc->r = vecsub(lc->r, lc->l);
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

static	unsigned char	max_color(unsigned char col, double lig)
{
	int temp;

	temp = col * lig;
	if (temp > 255)
		return ((unsigned char)255);
	else
		return ((unsigned char)temp);
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

int						light_on(t_env *e, t_v dest, double closest, int i)
{
	t_lc				*light;
	unsigned	char	rgb[3];
	double				col;

	light = e->lit_var;
	light->v = vecmult_num(dest, -1);
	light->p = vecsum(e->cam->pos, vecmult_num(dest, closest));
	light->n = vecsub(light->p, e->objs->objarr[i]->pos);
	if (e->objs->objarr[i]->type == T_SPHERE)
		light->n = vecsub(light->p, e->objs->objarr[i]->pos);
	if (e->objs->objarr[i]->type == T_PLANE)
		light->n = normal2plane(e, i);
	if (e->objs->objarr[i]->type == T_CYLINDER)
		light->n = normal2cyl(e, dest, closest, i);
	if (e->objs->objarr[i]->type == T_CONE)
		light->n = normal2cone(e, dest, closest, i);
	light->n = vecnorm(light->n);
	col = compute_light(e, i);
	rgb[0] = max_color(e->objs->objarr[i]->colour[0], col);
	rgb[1] = max_color(e->objs->objarr[i]->colour[1], col);
	rgb[2] = max_color(e->objs->objarr[i]->colour[2], col);
	return ((int)rgb[0] * 0x10000 + (int)rgb[1] * 0x100 + (int)rgb[2]);
}
