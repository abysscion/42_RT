/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_events_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 13:47:08 by sb_fox            #+#    #+#             */
/*   Updated: 2019/04/17 12:03:31 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	void	tbx_obj_event(kiss_textbox *tbx, SDL_Event *ev, int *draw,
								t_env *e)
{
	if (kiss_textbox_event(tbx, ev, draw))
	{
		if (e->gui->selected_object == (t_cam *)&e->cam)
			e->gui->win_info.visible ^= 1;
		else
		{
			e->gui->selected_object = (t_cam *)&e->cam;
			e->gui->selected_object_type = GUI_SELECTED_TYPE_CAM;
			if (e->gui->win_info.visible == 0)
				e->gui->win_info.visible = 1;
		}
		e->gui->need_update_info = 1;
	*draw = 1;
	}
}

static	void	sbt_event(kiss_selectbutton *sbt, SDL_Event *ev, int *draw,
							t_env *e)
{
	int	i;
	int	sum;
	int	last_index;

	i = -1;
	sum = 0;
	last_index = e->gui->eff_num - 1;
	if (kiss_selectbutton_event(sbt, ev, draw))
	{
		if (sbt == (kiss_selectbutton *)&e->gui->sbt_eff_arr[last_index])
			while(++i < last_index)
				e->gui->sbt_eff_arr[i].selected = 0;
		sbt->selected ^= 0;
		i = -1;
		while (++i < last_index)
			if (e->gui->sbt_eff_arr[i].selected == 1)
				++sum;
		e->gui->sbt_eff_arr[last_index].selected = sum > 0 ? 0 : 1;
		e->flags.aa = e->gui->sbt_eff_arr[0].selected == 1 ? 1 : 0;
		e->flags.stereo = e->gui->sbt_eff_arr[1].selected == 1 ? 1 : 0;
		e->flags.sepia = e->gui->sbt_eff_arr[2].selected == 1 ? 1 : 0;
		e->flags.blur = e->gui->sbt_eff_arr[3].selected == 1 ? 1 : 0;
		e->flags.need_render = 1;
		*draw = 1;
	}
}

static	void	ent_event(kiss_entry *ent, SDL_Event *ev, int *draw,
							t_env *e, double *value)
{
	if (kiss_entry_event(ent, ev, draw))
	{
		if (value)
			*value = atof(&ent->text[0]);
		adjust_objects(e);
		e->gui->need_update_info = 1;
		*draw = 1;
	}
}

static	void	cbb_event(kiss_combobox *cbb, SDL_Event *ev, int *draw,
																t_env *e)
{
	t_light	*light;
	int		index;

	if (kiss_combobox_event(cbb, ev, draw))
	{
		index = ft_atoi(&cbb->entry.text[9]);
		light = get_light_pointer_to_light(e, index);
		if (e->gui->selected_object == (t_light *)light)
			e->gui->win_info.visible ^= 1;
		else
		{
			e->gui->selected_object_type = GUI_SELECTED_TYPE_LIGHT;
			e->gui->selected_object = light;
			if (e->gui->win_info.visible == 0)
				e->gui->win_info.visible = 1;
		}
		e->gui->need_update_info = 1;
		*draw = 1;
	}
}

void			gui_handle_events(t_env *e, SDL_Event *ev, int *draw)
{
	int	i;

	i = -1;
	while (++i < e->gui->eff_num)
		sbt_event(&e->gui->sbt_eff_arr[i], ev, draw, e);
	tbx_obj_event(&e->gui->tbx_obj, ev, draw, e);
	ent_event(&e->gui->ent_pos_x, ev, draw, e,
										get_pointer_to_obj_value(e, 10));
	ent_event(&e->gui->ent_pos_y, ev, draw, e,
										get_pointer_to_obj_value(e, 11));
	ent_event(&e->gui->ent_pos_z, ev, draw, e,
										get_pointer_to_obj_value(e, 12));
	ent_event(&e->gui->ent_rot_x, ev, draw, e,
										get_pointer_to_obj_value(e, 20));
	ent_event(&e->gui->ent_rot_y, ev, draw, e,
										get_pointer_to_obj_value(e, 21));
	ent_event(&e->gui->ent_rot_z, ev, draw, e,
										get_pointer_to_obj_value(e, 22));
	cbb_event(&e->gui->cbb_light, ev, draw, e);
}
