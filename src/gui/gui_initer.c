/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_initer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 06:36:57 by sb_fox            #+#    #+#             */
/*   Updated: 2019/03/07 08:38:49 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

/*
**	Malloc's and returns pointer to newly created s_image object.
*/

t_im	*new_image(char *path, t_env *e)
{
	t_im	*im;

	im = (t_im *)malloc(sizeof(t_im));
	im->path = path;
	im->len = GUI_ICON_SIZE;
	im->wid = GUI_ICON_SIZE;
	im->ptimg = mlx_xpm_file_to_image(e->mlx, im->path, &im->len, &im->wid);
	return (im);
}

/*
**	Returns pointer to newly created (malloc'ed) button at position [(x), (y)].
**	Icon is being drawn from appropriate xpm image named (fname).
*/

t_bt			*new_button(int x, int y, int i, t_env *e)
{
	t_bt	*bt;

	bt = (t_bt *)malloc(sizeof(t_bt));
	bt->pos = (t_v) {x, y, 0};
	bt->len = GUI_ICON_SIZE;
	bt->wid = GUI_ICON_SIZE;
	if (i == GUI_BT_CAM)
		bt->state = 1;
	else
		bt->state = 0;
	bt->foo = press_mv_button;
	bt->ptimg = e->imgarr[i * 2 + bt->state]->ptimg;
	return	(bt);
}

/*
**	Fills image container imgarr[] with newly created images.
**	New images fills in with a strict order. DO NOT SWAP EM!
**	At the current moment resolution depends on >64x64< part of image path, so
**		to change icon resolution to 32x32 and back just change these numbers
**		and GUI_ICON_SIZE too (to make gui scalable).
*/

void	init_images(t_env *e)
{
	int i;

	i = -1;
	e->imgarr[++i] = new_image("img/64x64/cam.xpm", e);
	e->imgarr[++i] = new_image("img/64x64/cam_p.xpm", e);
	e->imgarr[++i] = new_image("img/64x64/cube.xpm", e);
	e->imgarr[++i] = new_image("img/64x64/cube_p.xpm", e);
	e->imgarr[++i] = new_image("img/64x64/arr_l.xpm", e);
	e->imgarr[++i] = new_image("img/64x64/arr_l_p.xpm", e);
	e->imgarr[++i] = new_image("img/64x64/arr_r.xpm", e);
	e->imgarr[++i] = new_image("img/64x64/arr_r_p.xpm", e);
	e->imgarr[++i] = new_image("img/64x64/arr_u.xpm", e);
	e->imgarr[++i] = new_image("img/64x64/arr_u_p.xpm", e);
	e->imgarr[++i] = new_image("img/64x64/arr_d.xpm", e);
	e->imgarr[++i] = new_image("img/64x64/arr_d_p.xpm", e);
}

/*
**	Inits buttons array with newly created (new_button()) buttons.
**	Buttons positions calculates from GUI_ variables.
**	Imagine @ is picture and Z is another picture:
**	_____________________________________
**	|                ^                  |
**	|     Gui margin |                  |
**	|  Gui margin    v   Gui gap        |
**	|<----------->   @   <-------->  Z  |
**	|             |<--->|               |
**	|          Gui icon size            |
**	_____________________________________
*/

void			init_buttons(t_env *e)
{
	t_bt	**b;
	int		i;
	int		gm;
	int		gis;
	int		gg;

	i = 0;
	gm = GUI_MARGIN;
	gis = GUI_ICON_SIZE;
	gg = GUI_GAP;
	b = e->buttons;
	b[i] = new_button(WIN_W + gm, gm, i, e);
	++i;
	b[i] = new_button(WIN_W + gm + gg * 2 + gis * 2, gm, i, e);
	++i;
	b[i] = new_button(WIN_W + gm, gm + gis + gg, i, e);
	++i;
	b[i] = new_button(WIN_W + gm + gg * 2 + gis * 2, gm + gis + gg, i, e);
	++i;
	b[i] = new_button(WIN_W + gm + gg + gis, gm, i, e);
	++i;
	b[i] = new_button(WIN_W + gm + gis + gg, gm + gg * 2 + gis * 2, i, e);
}

/*
**	Initialisates must have things gui need.
**	Multitple ft_strjoins() needed for compact malloc + writing in one line.
*/

void			init_gui(t_env *e)
{
	e->gui->pt_back_img = mlx_new_image(e->mlx,
		GUI_MARGIN * 2 + GUI_ICON_SIZE * 3 + GUI_GAP * 2, WIN_H);
	e->gui->objs_types = (char **)malloc(sizeof(char *) * T_TYPES_COUNT);
	e->gui->objs_types[T_PLANE] = ft_strjoin("", T_PLANE_NAME);
	e->gui->objs_types[T_SPHERE] = ft_strjoin("", T_SPHERE_NAME);
	e->gui->objs_types[T_CYLINDER] = ft_strjoin("", T_CYLINDER_NAME);
	e->gui->objs_types[T_CONE] = ft_strjoin("", T_CONE_NAME);
	e->need_regui = 1;
	e->need_rerender = 1;
	init_images(e);
	init_buttons(e);
}
