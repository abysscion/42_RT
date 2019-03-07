/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 22:20:00 by emayert           #+#    #+#             */
/*   Updated: 2019/03/07 15:43:49 by cschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			choose_type(t_env *e, int i, t_ren *r_v, double *t)
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

/*static	void	abuse_init(int *i, int *cross, double *closest)
{
	*i = -1;
	*cross = 0;
	*closest = RAY_LENMAX;
} */

double			*close_intersection(t_env *e, t_ren *r_v, int *num_obj)
{
	// double	closest;
	double	roots[2];
	double	*result;
	int		cross;
	int		i;

	i = -1;
	// closest = r_v->max;
	cross = 0;
	result = (double *)malloc(sizeof(double) * 2);
	result[0] = r_v->max;
	while (++i < e->objs->n_obj)
	{
		cross = choose_type(e, i, r_v, roots);
		if (cross && roots[0] > r_v->min && roots[0] < result[0])
		{
			result[0] = roots[0];
			result[1] = roots[1];
			*num_obj = i;

		}
		if (cross && roots[1] > r_v->min && roots[1] < result[0])
		{
			result[0] = roots[1];
			result[1] = roots[0];
			*num_obj = i;
		}
	}
	return (result);
}

unsigned char	*trace_ray(t_ren *ren_var, t_env *e, int rec)
{
	double	*closest;
	unsigned char	*color;
	int		num_obj;

	num_obj = 0;
	closest = close_intersection(e, ren_var, &num_obj);
	if (closest[0] >= ren_var->max)
	{
		color = (unsigned char *)malloc(sizeof(unsigned char) * 3);
		color[0] = 0;
		color[1] = 0;
		color[2] = 0;
		return (color);
	}
	color = light_on(e, ren_var, closest, num_obj, rec);
	return (color);
}

/*
**	Casts rays in every viewport pixel and lighting appropriate pixels
**	on viewport image.
*/

void			render(t_env *e)
{
	t_v		dest;
	unsigned char	*color;
	int		colour;
	int		x;
	int		y;

	if (e->need_rerender == 1)
	{
		y = WIN_H / 2 * -1;
		while (y < WIN_H / 2)
		{
			x = WIN_W / 2 * -1;
			while (x < WIN_W / 2)
			{
				dest = vp_to_global((t_v){x, y, 0});
				dest = vec_rotate(e->cam->rot, dest);
				dest = vecnorm(dest);
				create_renvar(e, dest);
				color = trace_ray(e->ren_var, e, RECURSION);
				colour = color[0] * 0x10000 + color[1] * 0x100 + color[2];
				ppx_on_img(y, x, colour, e);
				free(color);
				++x;
			}
			++y;
		}
		mlx_put_image_to_window(e->mlx, e->win, e->cam->ptr_vp, 0, 0);
		e->need_rerender = 0;
	}
}
