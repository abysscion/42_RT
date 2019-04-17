/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 13:47:08 by sb_fox            #+#    #+#             */
/*   Updated: 2019/04/17 11:14:47 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			init_gui(t_env *e)
{
	t_gui	*g;
	int		i;

	g = e->gui;
	g->eff_num = sizeof(g->sbt_eff_arr) / sizeof(kiss_selectbutton);
	g->selected_object = NULL;
	gui_init_arrays(e);
	gui_init_windows(e);
	gui_init_entries_0(e);
	gui_init_entries_1(e);
	gui_init_labels(e->gui);
	kiss_combobox_new(&g->cbb_light, &g->lblock, "", &g->cbb_light_arr,
		kiss_edge * 4, g->lab_cbb_light.rect.y + 20,
		g->lblock.rect.w - kiss_edge * 13, 100);
	i = -1;
	while (++i < g->eff_num)
		kiss_selectbutton_new(&g->sbt_eff_arr[i], &g->rblock, g->tbx_eff.rect.x
		+ g->tbx_eff.rect.w - kiss_edge * 2 - GUI_SBT_SIZE, g->tbx_eff.rect.y +
		kiss_edge * 2.5 + g->tbx_eff.font.lineheight * i);
	e->gui->sbt_eff_arr[e->gui->eff_num - 1].selected = 1;
	e->gui->background.visible = 1;
	e->gui->rblock.visible = 1;
	e->gui->lblock.visible = 1;
	e->gui->win_info.visible = 0;
}

static	void	update_more_info(t_env *e)
{
	if (e->gui->selected_object_type == GUI_SELECTED_TYPE_LIGHT)
	{
		snprintf(&e->gui->ent_pos_x.text[0], 11, "%.2f",
					((t_light *)e->gui->selected_object)->position.x);
		snprintf(&e->gui->ent_pos_y.text[0], 11, "%.2f",
					((t_light *)e->gui->selected_object)->position.y);
		snprintf(&e->gui->ent_pos_z.text[0], 11, "%.2f",
					((t_light *)e->gui->selected_object)->position.z);
		snprintf(&e->gui->ent_rot_x.text[0], 11, "%s", "-");
		snprintf(&e->gui->ent_rot_y.text[0], 11, "%s", "-");
		snprintf(&e->gui->ent_rot_z.text[0], 11, "%s", "-");
		return ;
	}
		snprintf(&e->gui->ent_pos_x.text[0], 11, "%.2f",
					((t_obj *)e->gui->selected_object)->position.x);
		snprintf(&e->gui->ent_pos_y.text[0], 11, "%.2f",
					((t_obj *)e->gui->selected_object)->position.y);
		snprintf(&e->gui->ent_pos_z.text[0], 11, "%.2f",
					((t_obj *)e->gui->selected_object)->position.z);
		snprintf(&e->gui->ent_rot_x.text[0], 11, "%.2f",
					((t_obj *)e->gui->selected_object)->rotation.x);
		snprintf(&e->gui->ent_rot_y.text[0], 11, "%.2f",
					((t_obj *)e->gui->selected_object)->rotation.y);
		snprintf(&e->gui->ent_rot_z.text[0], 11, "%.2f",
					((t_obj *)e->gui->selected_object)->rotation.z);
}

void			update_info(t_env *e)
{
	if (e->gui->selected_object_type == GUI_SELECTED_TYPE_CAM)
	{
		snprintf(&e->gui->ent_pos_x.text[0], 11, "%.2f", e->cam.position.x);
		snprintf(&e->gui->ent_pos_y.text[0], 11, "%.2f", e->cam.position.y);
		snprintf(&e->gui->ent_pos_z.text[0], 11, "%.2f", e->cam.position.z);
		snprintf(&e->gui->ent_rot_x.text[0], 11, "%.2f", e->cam.rotation.x);
		snprintf(&e->gui->ent_rot_y.text[0], 11, "%.2f", e->cam.rotation.y);
		snprintf(&e->gui->ent_rot_z.text[0], 11, "%.2f", e->cam.rotation.z);
	}
	else
		update_more_info(e);
	sprintf(&e->gui->ent_type.text[0], "%s", get_string_obj_type(e));
	e->gui->need_redraw = 1;
	e->gui->need_update_info = 0;
}

void			draw_all(t_env *e)
{
	SDL_RenderClear(e->sdl.renderer);
	if (e->gui->selected_object && e->gui->need_update_info == 1)
		update_info(e);
	gui_draw(e);
	if (e->flags.need_render == 1)
		check_stereo(e);
	draw_rt(e);
	SDL_RenderPresent(e->sdl.renderer);
	e->gui->need_redraw = 0;
}
