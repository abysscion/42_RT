/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utility.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emayert <emayert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 15:54:46 by emayert           #+#    #+#             */
/*   Updated: 2019/04/17 16:06:31 by emayert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				num_of_lights(t_env *e)
{
	t_lst	*light;
	int		n;

	n = 0;
	light = e->lights;
	while (light)
	{
		++n;
		light = light->next;
	}
	return (n);
}

t_light			*get_light_pointer_to_light(t_env *e, int index)
{
	t_lst	*tmp;

	tmp = e->lights;
	while (e->lights)
		if (tmp)
		{
			if (tmp->id == index)
				return ((t_light *)tmp->obj);
			else
				tmp = tmp->next;
		}
	return (NULL);
}

t_lst			*get_lst_pointer_to_light(t_env *e, int index)
{
	t_lst	*tmp;

	tmp = e->lights;
	while (e->lights)
		if (tmp->id == index)
			return (tmp);
		else
			tmp = tmp->next;
	return (NULL);
}

static	void	init_g_o_b_c(t_env *e, int *inter_type, double *c_dist)
{
	*inter_type = 0;
	*c_dist = e->ray.max;
}

void			get_obj_by_click(t_env *e, t_obj **obj, double *c_dist,
									t_lst *temp)
{
	double	roots[2];
	int		inter_type;
	t_lst	*surface;

	init_g_o_b_c(e, &inter_type, c_dist);
	while (temp)
	{
		surface = ((t_obj *)temp->obj)->surfaces;
		while (surface)
		{
			inter_type = choose_type(e, surface, roots);
			if (inter_type && roots[0] > e->ray.min && roots[0] < *c_dist)
			{
				*c_dist = roots[0];
				obj == NULL ? NULL : (*obj = temp->obj);
			}
			if (inter_type && roots[1] > e->ray.min && roots[1] < *c_dist)
			{
				*c_dist = roots[1];
				obj == NULL ? NULL : (*obj = temp->obj);
			}
			surface = surface->next;
		}
		temp = temp->next;
	}
}
