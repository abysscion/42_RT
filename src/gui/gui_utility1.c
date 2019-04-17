/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utility1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 13:47:08 by sb_fox            #+#    #+#             */
/*   Updated: 2019/04/17 11:52:44 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	double	*get_pointer_to_obj_value_supply(t_env *e, int axis_code)
{
	double	*value;
	void	*ptobj;

	value = NULL;
	ptobj = e->gui->selected_object;

	if (e->gui->selected_object_type == GUI_SELECTED_TYPE_CAM)
	{
		value = axis_code == 10 ? &(((t_cam *)ptobj)->position.x) : value;
		value = axis_code == 11 ? &(((t_cam *)ptobj)->position.y) : value;
		value = axis_code == 12 ? &(((t_cam *)ptobj)->position.z) : value;
		value = axis_code == 20 ? &(((t_cam *)ptobj)->rotation.x) : value;
		value = axis_code == 21 ? &(((t_cam *)ptobj)->rotation.y) : value;
		value = axis_code == 22 ? &(((t_cam *)ptobj)->rotation.z) : value;
	}
	return (value);
}

/*
**	Takes int code of axis to return proper pointer to value of selected object.
**	10 = position.x		11 = position.y		12 = position.z
**	20 = rotation.x		21 = rotation.y		22 = rotation.z
*/

double			*get_pointer_to_obj_value(t_env *e, int axis_code)
{
	double	*value;
	void	*ptobj;

	value = NULL;
	ptobj = e->gui->selected_object;
	if (e->gui->selected_object_type == GUI_SELECTED_TYPE_OBJ)
	{
		value = axis_code == 10 ? &(((t_obj *)ptobj)->position.x) : value;
		value = axis_code == 11 ? &(((t_obj *)ptobj)->position.y) : value;
		value = axis_code == 12 ? &(((t_obj *)ptobj)->position.z) : value;
		value = axis_code == 20 ? &(((t_obj *)ptobj)->rotation.x) : value;
		value = axis_code == 21 ? &(((t_obj *)ptobj)->rotation.y) : value;
		value = axis_code == 22 ? &(((t_obj *)ptobj)->rotation.z) : value;
	}
	else if (e->gui->selected_object_type == GUI_SELECTED_TYPE_LIGHT)
	{
		value = axis_code == 10 ? &(((t_light *)ptobj)->position.x) : value;
		value = axis_code == 11 ? &(((t_light *)ptobj)->position.y) : value;
		value = axis_code == 12 ? &(((t_light *)ptobj)->position.z) : value;
	}
	else
		return (get_pointer_to_obj_value_supply(e, axis_code));
	return (value);
}
