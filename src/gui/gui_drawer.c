/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_drawer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 13:47:08 by sb_fox            #+#    #+#             */
/*   Updated: 2019/04/17 11:23:04 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	void	gui_draw_1(t_env *e)
{
	t_gui	*g;

	g = e->gui;
	kiss_entry_draw(&g->ent_pos_x, e->sdl.renderer);
	kiss_entry_draw(&g->ent_pos_y, e->sdl.renderer);
	kiss_entry_draw(&g->ent_pos_z, e->sdl.renderer);
	kiss_entry_draw(&g->ent_rot_x, e->sdl.renderer);
	kiss_entry_draw(&g->ent_rot_y, e->sdl.renderer);
	kiss_entry_draw(&g->ent_rot_z, e->sdl.renderer);
	kiss_entry_draw(&g->ent_type, e->sdl.renderer);
	kiss_label_draw(&g->lab_tbx_obj, e->sdl.renderer);
	kiss_label_draw(&g->lab_tbx_info, e->sdl.renderer);
	kiss_label_draw(&g->lab_eff, e->sdl.renderer);
	kiss_label_draw(&g->lab_info_pos, e->sdl.renderer);
	kiss_label_draw(&g->lab_info_rot, e->sdl.renderer);
	kiss_label_draw(&g->lab_cbb_light, e->sdl.renderer);
	kiss_label_draw(&g->lab_info_type, e->sdl.renderer);
	kiss_combobox_draw(&g->cbb_light, e->sdl.renderer);
}

void			gui_draw(t_env *e)
{
	t_gui	*g;
	int		i;

	g = e->gui;
	kiss_window_draw(&g->background, e->sdl.renderer);
	kiss_window_draw(&g->rblock, e->sdl.renderer);
	kiss_window_draw(&g->lblock, e->sdl.renderer);
	kiss_window_draw(&g->win_info, e->sdl.renderer);
	kiss_textbox_draw(&g->tbx_obj, e->sdl.renderer);
	kiss_textbox_draw(&g->tbx_info, e->sdl.renderer);
	kiss_textbox_draw(&g->tbx_eff, e->sdl.renderer);
	i = -1;
	while (++i < g->eff_num)
		kiss_selectbutton_draw(&g->sbt_eff_arr[i], e->sdl.renderer);
	gui_draw_1(e);
}
