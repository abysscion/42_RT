/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_initer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emayert <emayert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:16:45 by emayert           #+#    #+#             */
/*   Updated: 2019/04/17 16:17:44 by emayert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	gui_init_arrays(t_env *e)
{
	t_gui	*g;
	int		i;

	g = e->gui;
	kiss_array_new(&g->tbx_obj_arr);
	kiss_array_new(&g->tbx_info_arr);
	kiss_array_new(&g->tbx_eff_arr);
	kiss_array_new(&g->cbb_light_arr);
	kiss_array_appendstring(&g->tbx_obj_arr, 0, "Main camera", 0x0);
	kiss_array_appendstring(&g->tbx_eff_arr, 0, "Antialiasing", 0x0);
	kiss_array_appendstring(&g->tbx_eff_arr, 1, "Stereo", 0x0);
	kiss_array_appendstring(&g->tbx_eff_arr, 2, "Sepia", 0x0);
	kiss_array_appendstring(&g->tbx_eff_arr, 3, "Blur", 0x0);
	kiss_array_appendstring(&g->tbx_eff_arr, 4, "No effects", 0x0);
	kiss_array_append(&g->objarr, ARRAY_TYPE, &g->tbx_obj_arr);
	kiss_array_append(&g->objarr, ARRAY_TYPE, &g->tbx_info_arr);
	kiss_array_append(&g->objarr, ARRAY_TYPE, &g->tbx_eff_arr);
	kiss_array_append(&g->objarr, ARRAY_TYPE, &g->cbb_light_arr);
	i = -1;
	while (++i < num_of_lights(e))
		kiss_array_appendstring(&g->cbb_light_arr, 0, "light №", ft_itoa(i));
}

void	gui_init_windows(t_env *e)
{
	t_gui	*g;

	g = e->gui;
	kiss_window_new(&g->background, NULL, 0, 0, 0, WIN_W, WIN_H);
	kiss_window_new(&g->rblock, NULL, 1,
		RT__W + GUI_LBLOCK_W, kiss_edge,
		GUI_RBLOCK_W, GUI_RBLOCK_H + kiss_edge);
	kiss_window_new(&g->lblock, NULL, 1,
		0, kiss_edge,
		GUI_LBLOCK_W, GUI_LBLOCK_H + kiss_edge);
	kiss_window_new(&g->win_info, NULL, 1, g->rblock.rect.x +
		kiss_edge * 2, kiss_textfont.lineheight + kiss_edge * 3,
		GUI_RBLOCK_W - kiss_edge * 4, GUI_LBLOCK_H * 0.5);
	kiss_textbox_new(&g->tbx_obj, &g->lblock, 1, &g->tbx_obj_arr,
		kiss_edge * 2, kiss_textfont.lineheight + kiss_edge * 3,
		GUI_LBLOCK_W - kiss_edge * 4, GUI_LBLOCK_H * 0.5);
	kiss_textbox_new(&g->tbx_info, &g->win_info, 1, &g->tbx_info_arr,
		g->rblock.rect.x + kiss_edge * 2, kiss_textfont.lineheight +
		kiss_edge * 3, GUI_RBLOCK_W - kiss_edge * 4, GUI_LBLOCK_H * 0.5);
	kiss_textbox_new(&g->tbx_eff, &g->rblock, 1, &g->tbx_eff_arr,
		g->lblock.rect.x + g->lblock.rect.w / 2 - GUI_EFF_W / 2,
		g->win_info.rect.y + g->win_info.rect.h + kiss_textfont.lineheight,
		GUI_EFF_W, (g->eff_num + 1) * (g->tbx_obj.font.lineheight +
		g->tbx_obj.font.spacing));
}

void	gui_init_entries_0(t_env *e)
{
	t_gui	*g;
	int		txtw3;

	g = e->gui;
	txtw3 = kiss_textwidth(kiss_textfont, ("12345678901"), 0x0) + 7 + kiss_edge;
	kiss_entry_new(&g->ent_pos_x, &g->win_info, 1, "0.00",
		g->win_info.rect.x + kiss_edge * 2, g->win_info.rect.y +
		g->win_info.rect.h - kiss_edge * 12 - kiss_textfont.lineheight * 2,
		txtw3);
	kiss_entry_new(&g->ent_pos_y, &g->win_info, 1, "0.00",
		g->win_info.rect.x + kiss_edge * 2 + txtw3, g->win_info.rect.y +
		g->win_info.rect.h - kiss_edge * 12 - kiss_textfont.lineheight * 2,
		txtw3);
	kiss_entry_new(&g->ent_pos_z, &g->win_info, 1, "0.00",
		g->win_info.rect.x + kiss_edge * 2 + txtw3 * 2, g->win_info.rect.y +
		g->win_info.rect.h - kiss_edge * 12 - kiss_textfont.lineheight * 2,
		txtw3);
}

void	gui_init_entries_1(t_env *e)
{
	t_gui	*g;
	int		txtw3;

	g = e->gui;
	txtw3 = kiss_textwidth(kiss_textfont, ("12345678901"), 0x0) + 7 + kiss_edge;
	kiss_entry_new(&g->ent_rot_x, &g->win_info, 1, "0.00",
		g->win_info.rect.x + kiss_edge * 2, g->win_info.rect.y +
		g->win_info.rect.h - kiss_edge * 5 - kiss_textfont.lineheight, txtw3);
	kiss_entry_new(&g->ent_rot_y, &g->win_info, 1, "0.00",
		g->win_info.rect.x + kiss_edge * 2 + txtw3, g->win_info.rect.y +
		g->win_info.rect.h - kiss_edge * 5 - kiss_textfont.lineheight, txtw3);
	kiss_entry_new(&g->ent_rot_z, &g->win_info, 1, "0.00",
		g->win_info.rect.x + kiss_edge * 2 + txtw3 * 2, g->win_info.rect.y +
		g->win_info.rect.h - kiss_edge * 5 - kiss_textfont.lineheight, txtw3);
	kiss_entry_new(&g->ent_type, &g->win_info, 1, "none",
		g->win_info.rect.x + kiss_edge * 2, g->tbx_info.rect.y + kiss_edge *
		3 + 20, GUI_RBLOCK_W - kiss_edge * 8);
}

void	gui_init_labels(t_gui *g)
{
	int	txtw0;
	int	txtw1;
	int	txtw2;

	txtw0 = kiss_textwidth(kiss_textfont, ("Overview"), 0x0);
	txtw1 = kiss_textwidth(kiss_textfont, ("Object info"), 0x0);
	txtw2 = kiss_textwidth(kiss_textfont, ("Effects"), 0x0);
	kiss_label_new(&g->lab_tbx_obj, &g->lblock, "Overview", g->tbx_obj.rect.x +
		(g->tbx_obj.rect.w - txtw0) / 2, g->lblock.rect.y + kiss_edge * 2);
	kiss_label_new(&g->lab_tbx_info, &g->lblock, "Object info",
		g->tbx_info.rect.x + (g->tbx_info.rect.w - txtw1) / 2,
		g->rblock.rect.y + kiss_edge * 2);
	kiss_label_new(&g->lab_info_pos, &g->rblock, "Effects",
		g->tbx_eff.rect.x + (g->tbx_eff.rect.w - txtw2) / 2,
		g->tbx_eff.rect.y - kiss_textfont.lineheight);
	kiss_label_new(&g->lab_info_rot, &g->win_info, "Position",
		g->tbx_info.rect.x + kiss_edge * 3,
		g->ent_pos_x.rect.y - kiss_edge * 4);
	kiss_label_new(&g->lab_eff, &g->win_info, "Rotation", g->tbx_info.rect.x +
		kiss_edge * 3, g->ent_rot_x.rect.y - kiss_edge * 4);
	kiss_label_new(&g->lab_cbb_light, &g->lblock, "Lights",
		++g->tbx_obj.rect.x + kiss_edge * 2,
		g->tbx_obj.rect.y - kiss_textfont.lineheight + 50);
	kiss_label_new(&g->lab_info_type, &g->win_info, "Type",
		g->tbx_info.rect.x + kiss_edge * 3, g->tbx_info.rect.y + kiss_edge * 3);
}
