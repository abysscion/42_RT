/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 13:47:08 by sb_fox            #+#    #+#             */
/*   Updated: 2019/04/12 18:09:06 by cschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



/*
**	Possible text entries boundaries check for mouse pointer:
**		add edge to rect x/y, remove from w/h
**
**	Need to invent smth about entries check and text replacing
**		atm its anchored to movements.
**
**	Rerender flag after entry value applying should be changed
**		from ENTER key to kiss lib insides. (or not, lol)
**
*/



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
	txtw3 = kiss_textwidth(kiss_textfont, ("2147483647x"), 0x0) + 7 + kiss_edge;
	shit = GUI_BAR_H + kiss_edge + kiss_textfont.lineheight;
	i = -1;

	kiss_array_new(&g->tbx_obj_arr);
	kiss_array_new(&g->tbx_info_arr);
	kiss_array_new(&g->tbx_eff_arr);

	kiss_array_append(&g->objarr, ARRAY_TYPE, &g->tbx_obj_arr);
	kiss_array_append(&g->objarr, ARRAY_TYPE, &g->tbx_info_arr);
	kiss_array_append(&g->objarr, ARRAY_TYPE, &g->tbx_eff_arr);
	kiss_button_new(&g->bt_arrup, &g->lblock, "Exit", 10, 10);

	kiss_window_new(&g->background, NULL, 0, 0, 0, WIN_W, WIN_H);
	kiss_window_new(&g->bar, NULL, 1, 0, 0, WIN_W, GUI_BAR_H);
	kiss_window_new(&g->rblock, NULL, 1,
		RT__W + GUI_LBLOCK_W, GUI_BAR_H - kiss_edge,
		GUI_RBLOCK_W, GUI_RBLOCK_H + kiss_edge);
	kiss_window_new(&g->lblock, NULL, 1,
		0, GUI_BAR_H - kiss_edge,
		GUI_LBLOCK_W, GUI_LBLOCK_H + kiss_edge);
	kiss_window_new(&g->win_info, NULL, 1,
		g->rblock.rect.x + kiss_edge * 2, shit,
		GUI_RBLOCK_W - kiss_edge * 4, GUI_LBLOCK_H * 0.5);
	kiss_textbox_new(&g->tbx_obj, &g->lblock, 1, &g->tbx_obj_arr,
		kiss_edge * 2, shit,
		GUI_LBLOCK_W - kiss_edge * 4, GUI_LBLOCK_H * 0.5);
	kiss_textbox_new(&g->tbx_info, &g->win_info, 1, &g->tbx_info_arr,
		g->rblock.rect.x + kiss_edge * 2, shit,
		GUI_RBLOCK_W - kiss_edge * 4, GUI_LBLOCK_H * 0.5);
	kiss_textbox_new(&g->tbx_eff, &g->rblock, 1, &g->tbx_eff_arr,
		g->win_info.rect.x,
			g->win_info.rect.y + g->win_info.rect.h + kiss_textfont.lineheight,
		GUI_EFF_W,
			(g->eff_num + 1) * (g->tbx_obj.font.lineheight +
			g->tbx_obj.font.spacing));

	kiss_label_new(&g->lab_tbx_obj, &g->lblock, "Objects overwiew",
		g->tbx_obj.rect.x + (g->tbx_obj.rect.w - txtw0) / 2,
		g->tbx_obj.rect.y - kiss_textfont.lineheight);
	kiss_label_new(&g->lab_tbx_info, &g->lblock, "Object info",
		g->tbx_info.rect.x + (g->tbx_info.rect.w - txtw1) / 2,
		g->tbx_info.rect.y - kiss_textfont.lineheight);
	kiss_label_new(&g->lab_eff, &g->rblock, "Effects",
		g->tbx_eff.rect.x + (g->tbx_eff.rect.w - txtw2) / 2,
		g->tbx_eff.rect.y - kiss_textfont.lineheight);

	kiss_entry_new(&g->ent_pos_x, &g->win_info, 1, "2147483647",
		g->win_info.rect.x + kiss_edge * 2,
		g->win_info.rect.y + kiss_edge * 2 + kiss_textfont.lineheight,
		txtw3);
	kiss_entry_new(&g->ent_pos_y, &g->win_info, 1, "2147483647",
		g->win_info.rect.x + kiss_edge * 2 + txtw3,
		g->win_info.rect.y + kiss_edge * 2 + kiss_textfont.lineheight,
		txtw3);
	kiss_entry_new(&g->ent_pos_z, &g->win_info, 1, "2147483647",
		g->win_info.rect.x + kiss_edge * 2 + txtw3 * 2,
		g->win_info.rect.y + kiss_edge * 2 + kiss_textfont.lineheight,
		txtw3);

	while (++i < g->eff_num)
		kiss_selectbutton_new(&g->sbt_eff_arr[i], &g->rblock,
			g->tbx_eff.rect.x + g->tbx_eff.rect.w - kiss_edge * 2 - GUI_SBT_SIZE,
			g->tbx_eff.rect.y + kiss_edge * 2.5 + g->tbx_eff.font.lineheight * i);
	e->gui->sbt_eff_arr[e->gui->eff_num - 1].selected = 1;

	e->gui->background.visible = 1;
	e->gui->rblock.visible = 1;
	e->gui->lblock.visible = 1;
	e->gui->bar.visible = 1;
	e->gui->win_info.visible = 1;

	kiss_array_appendstring(&g->tbx_obj_arr, 0, "Main camera", 0x0);

	kiss_array_appendstring(&g->tbx_info_arr, 0, "Position: ", 0x0);
	// kiss_array_appendstring(&g->tbx_info_arr, 1, "Rotation: ", 0x0);

	kiss_array_appendstring(&g->tbx_eff_arr, 0, "Antialiasing", 0x0);
	kiss_array_appendstring(&g->tbx_eff_arr, 1, "Stereo", 0x0);
	kiss_array_appendstring(&g->tbx_eff_arr, 2, "Sepia", 0x0);
	kiss_array_appendstring(&g->tbx_eff_arr, 3, "Blur", 0x0);
	kiss_array_appendstring(&g->tbx_eff_arr, 4, "No effects", 0x0);

	ft_strclr(&e->gui->ent_pos_x.text[0]);
	ft_strcpy(&e->gui->ent_pos_x.text[0], ft_itoa((int)e->cam.position.x));
	ft_strclr(&e->gui->ent_pos_y.text[0]);
	ft_strcpy(&e->gui->ent_pos_y.text[0], ft_itoa((int)e->cam.position.y));
	ft_strclr(&e->gui->ent_pos_z.text[0]);
	ft_strcpy(&e->gui->ent_pos_z.text[0], ft_itoa((int)e->cam.position.z));
}

/*
**	Draws every gui element.
*/

void	draw_gui(t_env *e)
{
	t_gui	*g;
	// t_v		p;
	// char	*str;
	int		i;

	g = e->gui;
	i = -1;
	kiss_window_draw(&g->background, e->sdl.renderer);
	kiss_window_draw(&g->rblock, e->sdl.renderer);
	kiss_window_draw(&g->lblock, e->sdl.renderer);
	kiss_window_draw(&g->bar, e->sdl.renderer);
	kiss_window_draw(&g->win_info, e->sdl.renderer);

	kiss_button_draw(&g->bt_arrup, e->sdl.renderer);

	kiss_textbox_draw(&g->tbx_obj, e->sdl.renderer);
	kiss_textbox_draw(&g->tbx_info, e->sdl.renderer);
	kiss_textbox_draw(&g->tbx_eff, e->sdl.renderer);

	while (++i < g->eff_num)
		kiss_selectbutton_draw(&g->sbt_eff_arr[i], e->sdl.renderer);

	kiss_entry_draw(&g->ent_pos_x, e->sdl.renderer);
	kiss_entry_draw(&g->ent_pos_y, e->sdl.renderer);
	kiss_entry_draw(&g->ent_pos_z, e->sdl.renderer);

	kiss_label_draw(&g->lab_tbx_obj, e->sdl.renderer);
	kiss_label_draw(&g->lab_tbx_info, e->sdl.renderer);
	kiss_label_draw(&g->lab_eff, e->sdl.renderer);

	// g->ent_pos_x.text = ft_strcpy(g->ent_pos_x.text, ft_itoa((int)e->cam.position.x));


	// str = (char *)malloc(50);
	// p = e->cam.position;
	// str = ft_strcat(ft_itoa((int)p.x), ", ");
	// str = ft_strcat(str, ft_itoa((int)p.y));
	// str = ft_strcat(str, ", ");
	// str = ft_strcat(str, ft_itoa((int)p.z));
	// kiss_array_assign(&g->tbx_info_arr, 0, 0, ft_strjoin("Position: ", str));
	// ft_strclr(str);
	// p = e->cam.rotation;
	// str = ft_strcat(ft_itoa((int)p.x), ", ");
	// str = ft_strcat(str, ft_itoa((int)p.y));
	// str = ft_strcat(str, ", ");
	// str = ft_strcat(str, ft_itoa((int)p.z));
	// kiss_array_assign(&g->tbx_info_arr, 1, 1, ft_strjoin("Rotation: ", str));
	// free(str);
}

/*
**	Clears render content -> draws everything in order -> updates render view.
*/

void	draw_all(t_env *e)
{
	SDL_RenderClear(e->sdl.renderer);
	draw_gui(e);
	// render(e);
	if (e->flags.need_render == 1)
		check_stereo(e);
	draw_rt(e);
	SDL_RenderPresent(e->sdl.renderer);
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
