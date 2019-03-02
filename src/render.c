/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 22:20:00 by emayert           #+#    #+#             */
/*   Updated: 2019/03/02 03:51:17 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int		choose_type(t_env *e, int i, t_ren *r_v, double *t)
{
	if (e->objs->objarr[i]->type == T_PLANE)
		return (intersect_plane(r_v->start, r_v->dest,
			e->objs->objarr[i], &t[0]));
	else if (e->objs->objarr[i]->type == T_SPHERE)
		return (intersect_sphere(r_v->start, r_v->dest,
			e->objs->objarr[i], &t[0]));
	else if (e->objs->objarr[i]->type == T_CYLINDER)
		return (intersect_cylinder(r_v->start, r_v->dest,
			e->objs->objarr[i], &t[0]));
	else
		return (intersect_cone(r_v->start, r_v->dest,
			e->objs->objarr[i], &t[0]));
}

static	void	abuse_init(int *i, int *cross, double *closest)
{
	*i = -1;
	*cross = 0;
	*closest = RAY_LENMAX;
}

double			close_intersection(t_env *e, t_ren *r_v, int *num_obj)
{
	double	closest;
	double	t[2];
	int		cross;
	int		i;

	abuse_init(&i, &cross, &closest);
	while (++i < e->objs->n_obj)
	{
		cross = choose_type(e, i, r_v, t);
		if (cross)
		{
			if (t[0] > r_v->min && t[0] < r_v->max && t[0] < closest)
			{
				closest = t[0];
				*num_obj = i;
			}
			if (e->objs->objarr[i]->type != T_PLANE &&
				t[1] > r_v->min && t[1] < r_v->max && t[1] < closest)
			{
				closest = t[1];
				*num_obj = i;
			}
		}
	}
	return (closest);
}

static	int		trace_ray(t_v dest, t_env *e)
{
	double	closest;
	int		color;
	int		num_obj;

	num_obj = 0;
	e->ren_var->start = e->cam->pos;
	e->ren_var->dest = dest;
	e->ren_var->min = 1;
	e->ren_var->max = RAY_LENMAX;
	closest = close_intersection(e, e->ren_var, &num_obj);
	if (closest == RAY_LENMAX)
		return (CLR_BACKGROUND);
	color = light_on(e, dest, closest, num_obj);
	return (color);
}

/*
**	Casts rays in every viewport pixel and lighting appropriate pixels
**	on viewport image.
*/

void			render(t_env *e)
{
	t_v		dst;
	int		color;
	int		x;
	int		y;

	y = WIN_H / 2 * -1;
	while (y < WIN_H / 2)
	{
		x = WIN_W / 2 * -1;
		while (x < WIN_W / 2)
		{
			dst = vp_to_global((t_v){x, y, 0});
			dst = vec_rotate(e->cam->rot, dst);
			dst = vecnorm(dst);
			color = trace_ray(dst, e);
			ppx_on_img(y, x, color, e);
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->cam->ptr_vp, 0, 0);
	draw_gui(e);
	e->need_redraw = 0;
}
