/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 13:47:08 by sb_fox            #+#    #+#             */
/*   Updated: 2019/04/05 22:20:09 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_gui(t_env *e)
{
	t_gui	*g;
	int		txtw0;
	int		txtw1;
	int		shit;

	g = e->gui;
	txtw0 = kiss_textwidth(kiss_textfont, ("Objects overwiew"), 0x0);
	txtw1 = kiss_textwidth(kiss_textfont, ("Object info"), 0x0);
	shit = GUI_BAR_H + kiss_edge + kiss_textfont.lineheight;
	kiss_array_new(&g->tbx_obj_arr);
	kiss_array_new(&g->tbx_info_arr);
	kiss_array_append(&g->objarr, ARRAY_TYPE, &g->tbx_obj_arr);
	kiss_array_append(&g->objarr, ARRAY_TYPE, &g->tbx_info_arr);
	kiss_button_new(&g->bt_arrup, &g->lblock, "Exit", 10, 10);
	kiss_window_new(&g->background, NULL, 0, 0, 0, WIN_W, WIN_H);
	kiss_window_new(&g->bar, NULL, 1, 0, 0, WIN_W, GUI_BAR_H);
	kiss_window_new(&g->rblock, NULL, 1,
		RT__W + GUI_LBLOCK_W,						GUI_BAR_H - kiss_edge,
		GUI_RBLOCK_W,								GUI_RBLOCK_H + kiss_edge);
	kiss_window_new(&g->lblock, NULL, 1,
		0, 											GUI_BAR_H - kiss_edge,
		GUI_LBLOCK_W,								GUI_LBLOCK_H + kiss_edge);
	kiss_window_new(&g->win_obj_info, NULL, 1,
		WIN_W - GUI_RBLOCK_W + kiss_edge * 2,		shit,
		GUI_RBLOCK_W - kiss_edge * 4,		 		GUI_LBLOCK_H * 0.5);
	kiss_label_new(&g->lab_tbx_obj, &g->lblock, "Objects overwiew",
		(GUI_LBLOCK_W - txtw0) / 2,					GUI_BAR_H + kiss_edge);
	kiss_label_new(&g->lab_tbx_info, &g->lblock, "Object info",
		WIN_W - (GUI_LBLOCK_W + txtw1) / 2,			GUI_BAR_H + kiss_edge);
	kiss_textbox_new(&g->tbx_obj, &g->lblock, 1, &g->tbx_obj_arr,
		kiss_edge * 2,								shit,
		GUI_LBLOCK_W - kiss_edge * 4,				GUI_LBLOCK_H * 0.5);
	kiss_textbox_new(&g->tbx_info, &g->win_obj_info, 1, &g->tbx_info_arr,
		WIN_W - GUI_RBLOCK_W + kiss_edge * 2,		shit,
		GUI_RBLOCK_W - kiss_edge * 4,		 		GUI_LBLOCK_H * 0.5);
	e->gui->background.visible = 1;
	e->gui->rblock.visible = 1;
	e->gui->lblock.visible = 1;
	e->gui->bar.visible = 1;
	e->gui->win_obj_info.visible = 1;
	kiss_array_appendstring(&g->tbx_obj_arr, 0, "Main camera", 0x0);
	kiss_array_appendstring(&g->tbx_info_arr, 0, "Position: ", 0x0);
	kiss_array_appendstring(&g->tbx_info_arr, 1, "Rotation: ", 0x0);
}

void	draw_gui(t_env *e)
{
	t_gui	*g;
	t_v		p;
	char	*str;

	g = e->gui;
	kiss_window_draw(&g->background, e->sdl.renderer);
	kiss_window_draw(&g->rblock, e->sdl.renderer);
	kiss_window_draw(&g->lblock, e->sdl.renderer);
	kiss_window_draw(&g->bar, e->sdl.renderer);
	kiss_window_draw(&g->win_obj_info, e->sdl.renderer);
	kiss_button_draw(&g->bt_arrup, e->sdl.renderer);
	kiss_textbox_draw(&g->tbx_obj, e->sdl.renderer);
	kiss_textbox_draw(&g->tbx_info, e->sdl.renderer);
	kiss_label_draw(&g->lab_tbx_obj, e->sdl.renderer);
	kiss_label_draw(&g->lab_tbx_info, e->sdl.renderer);

	str = (char *)malloc(50);
	p = e->cam.position;
	str = ft_strcat(ft_itoa((int)p.x), ", ");
	str = ft_strcat(str, ft_itoa((int)p.y));
	str = ft_strcat(str, ", ");
	str = ft_strcat(str, ft_itoa((int)p.z));
	kiss_array_assign(&g->tbx_info_arr, 0, 0, ft_strjoin("Position: ", str));
	ft_strclr(str);
	p = e->cam.rotation;
	str = ft_strcat(ft_itoa((int)p.x), ", ");
	str = ft_strcat(str, ft_itoa((int)p.y));
	str = ft_strcat(str, ", ");
	str = ft_strcat(str, ft_itoa((int)p.z));
	kiss_array_assign(&g->tbx_info_arr, 1, 1, ft_strjoin("Rotation: ", str));
	free(str);
}

/*
**	Clears render content -> draws everything in order -> updates render view.
*/

void	draw_all(t_env *e)
{
	SDL_RenderClear(e->sdl.renderer);
	draw_gui(e);
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
