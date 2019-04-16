/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 13:47:08 by sb_fox            #+#    #+#             */
/*   Updated: 2019/04/16 19:18:15 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_gui(t_env *e)
{
	t_gui	*g;
	int		txtw0;
	int		txtw1;
	int		txtw2;
	int		txtw3;
	int		shit;
	int		i;

	g = e->gui;
	g->eff_num = sizeof(g->sbt_eff_arr) / sizeof(kiss_selectbutton);
	txtw0 = kiss_textwidth(kiss_textfont, ("Objects overwiew"), 0x0);
	txtw1 = kiss_textwidth(kiss_textfont, ("Object info"), 0x0);
	txtw2 = kiss_textwidth(kiss_textfont, ("Effects"), 0x0);
	txtw3 = kiss_textwidth(kiss_textfont, ("12345678901"), 0x0) + 7 + kiss_edge;
	shit = kiss_edge + kiss_textfont.lineheight;
	g->selected_object = NULL;

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

	i = -1;
	while (++i < numOfLights(e))
		kiss_array_appendstring(&g->cbb_light_arr, 0, "light №", ft_itoa(i));

	kiss_array_append(&g->objarr, ARRAY_TYPE, &g->tbx_obj_arr);
	kiss_array_append(&g->objarr, ARRAY_TYPE, &g->tbx_info_arr);
	kiss_array_append(&g->objarr, ARRAY_TYPE, &g->tbx_eff_arr);
	kiss_array_append(&g->objarr, ARRAY_TYPE, &g->cbb_light_arr);

	kiss_window_new(&g->background, NULL, 0, 0, 0, WIN_W, WIN_H);
	kiss_window_new(&g->rblock, NULL, 1,
		RT__W + GUI_LBLOCK_W, kiss_edge,
		GUI_RBLOCK_W, GUI_RBLOCK_H + kiss_edge);
	kiss_window_new(&g->lblock, NULL, 1,
		0, kiss_edge,
		GUI_LBLOCK_W, GUI_LBLOCK_H + kiss_edge);
	kiss_window_new(&g->win_info, NULL, 1,
		g->rblock.rect.x + kiss_edge * 2, shit + kiss_edge * 2,
		GUI_RBLOCK_W - kiss_edge * 4, GUI_LBLOCK_H * 0.5);
	kiss_textbox_new(&g->tbx_obj, &g->lblock, 1, &g->tbx_obj_arr,
		kiss_edge * 2, shit + kiss_edge * 2,
		GUI_LBLOCK_W - kiss_edge * 4, GUI_LBLOCK_H * 0.5);
	kiss_textbox_new(&g->tbx_info, &g->win_info, 1, &g->tbx_info_arr,
		g->rblock.rect.x + kiss_edge * 2, shit + kiss_edge * 2,
		GUI_RBLOCK_W - kiss_edge * 4, GUI_LBLOCK_H * 0.5);
	kiss_textbox_new(&g->tbx_eff, &g->rblock, 1, &g->tbx_eff_arr,
		g->lblock.rect.x + g->lblock.rect.w / 2 - GUI_EFF_W / 2,
			g->win_info.rect.y + g->win_info.rect.h + kiss_textfont.lineheight,
		GUI_EFF_W,
			(g->eff_num + 1) * (g->tbx_obj.font.lineheight +
			g->tbx_obj.font.spacing));

	kiss_entry_new(&g->ent_pos_x, &g->win_info, 1, "0.00",
		g->win_info.rect.x + kiss_edge * 2,
		g->win_info.rect.y + g->win_info.rect.h - kiss_edge * 12 - kiss_textfont.lineheight * 2,
		txtw3);
	kiss_entry_new(&g->ent_pos_y, &g->win_info, 1, "0.00",
		g->win_info.rect.x + kiss_edge * 2 + txtw3,
		g->win_info.rect.y + g->win_info.rect.h - kiss_edge * 12 - kiss_textfont.lineheight * 2,
		txtw3);
	kiss_entry_new(&g->ent_pos_z, &g->win_info, 1, "0.00",
		g->win_info.rect.x + kiss_edge * 2 + txtw3 * 2,
		g->win_info.rect.y + g->win_info.rect.h - kiss_edge * 12 - kiss_textfont.lineheight * 2,
		txtw3);
	kiss_entry_new(&g->ent_rot_x, &g->win_info, 1, "0.00",
		g->win_info.rect.x + kiss_edge * 2,
		g->win_info.rect.y + g->win_info.rect.h - kiss_edge * 5 - kiss_textfont.lineheight,
		txtw3);
	kiss_entry_new(&g->ent_rot_y, &g->win_info, 1, "0.00",
		g->win_info.rect.x + kiss_edge * 2 + txtw3,
		g->win_info.rect.y + g->win_info.rect.h - kiss_edge * 5 - kiss_textfont.lineheight,
		txtw3);
	kiss_entry_new(&g->ent_rot_z, &g->win_info, 1, "0.00",
		g->win_info.rect.x + kiss_edge * 2 + txtw3 * 2,
		g->win_info.rect.y + g->win_info.rect.h - kiss_edge * 5 - kiss_textfont.lineheight,
		txtw3);
	kiss_entry_new(&g->ent_type, &g->win_info, 1, "none",
		g->win_info.rect.x + kiss_edge * 2,
		g->tbx_info.rect.y + kiss_edge * 3 + 20,
		GUI_RBLOCK_W - kiss_edge * 8);

	kiss_label_new(&g->lab_tbx_obj, &g->lblock, "Objects overwiew",
		g->tbx_obj.rect.x + (g->tbx_obj.rect.w - txtw0) / 2,
		g->lblock.rect.y + kiss_edge * 2);
	kiss_label_new(&g->lab_tbx_info, &g->lblock, "Object info",
		g->tbx_info.rect.x + (g->tbx_info.rect.w - txtw1) / 2,
		g->rblock.rect.y + kiss_edge * 2);
	kiss_label_new(&g->lab_info_pos, &g->rblock, "Effects",
		g->tbx_eff.rect.x + (g->tbx_eff.rect.w - txtw2) / 2,
		g->tbx_eff.rect.y - kiss_textfont.lineheight);
	kiss_label_new(&g->lab_info_rot, &g->win_info, "Position",
		g->tbx_info.rect.x + kiss_edge * 3,
		g->ent_pos_x.rect.y - kiss_edge * 4);
	kiss_label_new(&g->lab_eff, &g->win_info, "Rotation",
		g->tbx_info.rect.x + kiss_edge * 3,
		g->ent_rot_x.rect.y - kiss_edge * 4);
	kiss_label_new(&g->lab_cbb_light, &g->lblock, "Lights",
		g->tbx_obj.rect.x + kiss_edge * 2 + 1,
		g->tbx_obj.rect.y - kiss_textfont.lineheight + 50);
	kiss_label_new(&g->lab_info_type, &g->win_info, "Type",
		g->tbx_info.rect.x + kiss_edge * 3,
		g->tbx_info.rect.y + kiss_edge * 3);

	kiss_combobox_new(&g->cbb_light, &g->lblock, "", &g->cbb_light_arr,
		kiss_edge * 4, g->lab_cbb_light.rect.y + 20,
		g->lblock.rect.w - kiss_edge * 13, 100);

	i = -1;
	while (++i < g->eff_num)
		kiss_selectbutton_new(&g->sbt_eff_arr[i], &g->rblock,
			g->tbx_eff.rect.x + g->tbx_eff.rect.w - kiss_edge * 2 - GUI_SBT_SIZE,
			g->tbx_eff.rect.y + kiss_edge * 2.5 + g->tbx_eff.font.lineheight * i);
	e->gui->sbt_eff_arr[e->gui->eff_num - 1].selected = 1;

	e->gui->background.visible = 1;
	e->gui->rblock.visible = 1;
	e->gui->lblock.visible = 1;
	e->gui->win_info.visible = 0;
}

/*
**	Draws every gui element.
*/

void	draw_gui(t_env *e)
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

/*
**	Updates text in info window.
*/

void	update_info(t_env *e)
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
	else if (e->gui->selected_object_type == GUI_SELECTED_TYPE_LIGHT)
	{
		snprintf(&e->gui->ent_pos_x.text[0], 11, "%.2f",
					((t_light *)e->gui->selected_object)->position.x);
		snprintf(&e->gui->ent_pos_y.text[0], 11, "%.2f",
					((t_light *)e->gui->selected_object)->position.y);
		snprintf(&e->gui->ent_pos_z.text[0], 11, "%.2f",
					((t_light *)e->gui->selected_object)->position.z);
		snprintf(&e->gui->ent_rot_x.text[0], 11, "%s", "NaN");
		snprintf(&e->gui->ent_rot_y.text[0], 11, "%s", "NaN");
		snprintf(&e->gui->ent_rot_z.text[0], 11, "%s", "NaN");
	}
	else
	{
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
	sprintf(&e->gui->ent_type.text[0], "%s", get_string_obj_type(e));
	e->gui->need_redraw = 1;
	e->gui->need_update_info = 0;
}

/*
**	Clears render content -> draws everything in order -> updates render view.
*/

void	draw_all(t_env *e)
{
	SDL_RenderClear(e->sdl.renderer);
	if (e->gui->selected_object && e->gui->need_update_info == 1)
		update_info(e);
	draw_gui(e);
	if (e->flags.need_render == 1)
		check_stereo(e);
	draw_rt(e);
	SDL_RenderPresent(e->sdl.renderer);
	e->gui->need_redraw = 0;
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

int		numOfObjs(t_env *e)
{
	t_lst	*objects;
	int		n;

	n = 0;
	objects = e->objects;
	while (objects)
	{
		++n;
		objects = objects->next;
	}
	return (n);
}

int		numOfSurfs(t_env *e)
{
	t_lst	*objects;
	t_lst	*surface;
	int		n;

	n = 0;
	objects = e->objects;
	while (objects)
	{
		surface = ((t_obj *)objects->obj)->surfaces;
		while (surface)
		{
			++n;
			surface = surface->next;
		}
		objects = objects->next;
	}
	return (n);
}
