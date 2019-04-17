/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utility.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 13:47:08 by sb_fox            #+#    #+#             */
/*   Updated: 2019/04/17 14:11:52 by cschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*get_string_obj_type(t_env *e)
{
	void	*tmp;

	if (e->gui->selected_object_type == GUI_SELECTED_TYPE_CAM)
		return ("Camera");
	else if (e->gui->selected_object_type == GUI_SELECTED_TYPE_LIGHT)
	{
		tmp = get_lst_pointer_to_light(e,
				ft_atoi(&e->gui->cbb_light.entry.text[9]));
		if (((t_lst *)tmp)->type == T_AMBIENT)
			return ("Ambient light");
		else if (((t_lst *)tmp)->type == T_POINT)
			return ("Point light");
		else if (((t_lst *)tmp)->type == T_DIRECTIONAL)
			return ("Directional light");
	}
	else if (e->gui->selected_object_type == GUI_SELECTED_TYPE_OBJ)
		return ("Object");
	return (NULL);
}

int		numOfLights(t_env *e)
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

t_light	*get_light_pointer_to_light(t_env *e, int index)
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

t_lst	*get_lst_pointer_to_light(t_env *e, int index)
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

void	getObjByClick(t_env *e, t_obj **obj, double *cDist, t_lst *temp)
{
	double	roots[2];
	int		interType;
	t_lst	*surface;

	interType = 0;
	*cDist = e->ray.max;
	while (temp)
	{
		surface = ((t_obj *)temp->obj)->surfaces;
		while (surface)
		{
			interType = choose_type(e, surface, roots);
			if (interType && roots[0] > e->ray.min && roots[0] < *cDist)
			{
				*cDist = roots[0];
				obj == NULL ? NULL : (*obj = temp->obj);
			}
			if (interType && roots[1] > e->ray.min && roots[1] < *cDist)
			{
				*cDist = roots[1];
				obj == NULL ? NULL : (*obj = temp->obj);
			}
			surface = surface->next;
		}
		temp = temp->next;
	}
}
