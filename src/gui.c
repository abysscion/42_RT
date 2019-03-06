/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 15:21:02 by sb_fox            #+#    #+#             */
/*   Updated: 2019/03/06 05:47:13 by sb_fox           ###   ########.fr       */
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
**	Inits buttons array with newly created (new_bt()) buttons.
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
	b[i] = new_bt(WIN_W + gm, gm, &i, e);
	b[i] = new_bt(WIN_W + gm + gg * 2 + gis * 2, gm, &i, e);
	b[i] = new_bt(WIN_W + gm, gm + gis + gg, &i, e);
	b[i] = new_bt(WIN_W + gm + gg * 2 + gis * 2, gm + gis + gg, &i, e);
	b[i] = new_bt(WIN_W + gm + gg + gis, gm, &i, e);
	b[i] = new_bt(WIN_W + gm + gis + gg, gm + gg * 2 + gis * 2, &i, e);
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
	init_images(e);
	init_buttons(e);
}

/*
**	Draws text info about clicked object at (x, y) position
*/

/*	There !MUST! be something better at string bulding. For example another foo
**		which takes void* struct with an array of strings and their count.
**		Maybe it would be just a single-linked list. DUNNO YET...
*/

void			draw_object_info(int x, int y, t_env *e)
{
	char	buff[256];
	char	*tmp;
	char	*p;
	int		i;
	t_obj	*ptj;

	if (e->hitobj->ishit == 1)
	{
		ptj = e->objs->objarr[e->hitobj->index];
		i = 0;

		p = ft_strcpy(&buff[0], "Type: ");
		ft_strcat(p, e->gui->objs_types[ptj->type]);
		mlx_string_put(e->mlx, e->win, x + GUI_MARGIN, y + GUI_TEXT_H * ++i +
			GUI_MARGIN + GUI_ICON_SIZE * 3 + GUI_GAP * 3, CLR_TEXT, p);
		ft_strclr(p);

		p = ft_strcpy(&buff[0], "Radius: ");
		tmp = ft_itoa(ptj->radius);
		ft_strcat(p, tmp);
		mlx_string_put(e->mlx, e->win, x + GUI_MARGIN, y + GUI_TEXT_H * ++i +
			GUI_MARGIN + GUI_ICON_SIZE * 3 + GUI_GAP * 3, CLR_TEXT, p);
		ft_strclr(p);
		free(tmp);

		p = ft_strcpy(&buff[0], "Position: (");
		tmp = ft_itoa((int)ptj->pos.x);
		ft_strcat(p, ft_strcat(tmp, ", "));
		free(tmp);
		tmp = ft_itoa((int)ptj->pos.y);
		ft_strcat(p, ft_strcat(tmp, ", "));
		free(tmp);
		tmp = ft_itoa((int)ptj->pos.z);
		ft_strcat(p, ft_strcat(tmp, ")"));
		mlx_string_put(e->mlx, e->win, x + GUI_MARGIN, y + GUI_TEXT_H * ++i +
			GUI_MARGIN + GUI_ICON_SIZE * 3 + GUI_GAP * 3, CLR_TEXT, p);
		ft_strclr(p);
		free(tmp);

		p = ft_strcpy(&buff[0], "Rotation: (");
		tmp = ft_itoa((int)ptj->rot.x);
		ft_strcat(p, ft_strcat(tmp, ", "));
		free(tmp);
		tmp = ft_itoa((int)ptj->rot.y);
		ft_strcat(p, ft_strcat(tmp, ", "));
		free(tmp);
		tmp = ft_itoa((int)ptj->rot.z);
		ft_strcat(p, ft_strcat(tmp, ")"));
		mlx_string_put(e->mlx, e->win, x + GUI_MARGIN, y + GUI_TEXT_H * ++i +
			GUI_MARGIN + GUI_ICON_SIZE * 3 + GUI_GAP * 3, CLR_TEXT, p);
		ft_strclr(p);
		free(tmp);
	}
	else
	mlx_string_put(e->mlx, e->win, WIN_W + GUI_TOOLBAR_W / 2 - GUI_MSG_NOOBJ_W,
				y + GUI_MARGIN + GUI_ICON_SIZE * 3 + GUI_GAP * 3 + GUI_TEXT_H,
				CLR_TEXT, "No object selected");
}

/*
**	Draws whole GUI content on screen by putting appropriate mlx images.
*/

void			draw_gui(t_env *e)
{
	int	i;

	i = -1;
	mlx_put_image_to_window(e->mlx, e->win, e->gui->pt_back_img, WIN_W, 0);
	while (++i < GUI_BT_NUM)
	{
		if (e->buttons[i]->state == 1)
			e->buttons[i]->ptimg = e->imgarr[2 * i + 1]->ptimg;
		else
			e->buttons[i]->ptimg = e->imgarr[2 * i]->ptimg;
		mlx_put_image_to_window(e->mlx, e->win, e->buttons[i]->ptimg,
								e->buttons[i]->pos.x, e->buttons[i]->pos.y);
	}
	draw_object_info(WIN_W, 0, e);
	e->need_regui = 0;
}

/*
**	Changes given values of position (val) by (add), switches redraw flags.
*/

static	void	press_mv_button(double *val, double add, void *e)
{
	t_env	*env;

	env = (t_env *)e;
	*val += add;
	env->need_rerender = 1;
	env->need_regui = 1;
}

/*
**	Handles arrow buttons behaviour calling foo() if click was made in
**		icon's boundaries.
*/

static	void	handle_arrows(int x, int y, t_env *e)
{
	t_bt	**b;
	t_v		*ptv;
	int		s;

	b = e->buttons;
	s = GUI_ICON_SIZE;
	if (e->hitobj->ishit == 1)
		ptv = &e->objs->objarr[e->hitobj->index]->pos;
	else
		ptv = &e->cam->pos;
	if (x > b[GUI_BT_AL]->pos.x && x < b[GUI_BT_AL]->pos.x + s)
		if	(y > b[GUI_BT_AL]->pos.y && y < b[GUI_BT_AL]->pos.y + s)
		{
			b[GUI_BT_AL]->foo(&ptv->x, -1, e);
			b[GUI_BT_AL]->state = 1;
		}
	if (x > b[GUI_BT_AR]->pos.x && x < b[GUI_BT_AR]->pos.x + s)
		if	(y > b[GUI_BT_AR]->pos.y && y < b[GUI_BT_AR]->pos.y + s)
		{
			b[GUI_BT_AR]->foo(&ptv->x, 1, e);
			b[GUI_BT_AR]->state = 1;
		}
	if (x > b[GUI_BT_AU]->pos.x && x < b[GUI_BT_AU]->pos.x + s)
		if	(y > b[GUI_BT_AU]->pos.y && y < b[GUI_BT_AU]->pos.y + s)
		{
			b[GUI_BT_AU]->foo(&ptv->y, -1, e);
			b[GUI_BT_AU]->state = 1;
		}
	if (x > b[GUI_BT_AD]->pos.x && x < b[GUI_BT_AD]->pos.x + s)
		if	(y > b[GUI_BT_AD]->pos.y && y < b[GUI_BT_AD]->pos.y + s)
		{
			b[GUI_BT_AD]->foo(&ptv->y, 1, e);
			b[GUI_BT_AD]->state = 1;
		}
}

/*
**	Handles camera and object (cube) buttons behaviour switching buttons states
**		and changing redraw flags to 1 if click	was made in icon's boundaries.
*/

static	void	handle_camncube(int x, int y, t_env *e)
{
	t_bt	**b;
	int		s;

	b = e->buttons;
	s = GUI_ICON_SIZE;
	if (x > b[GUI_BT_CAM]->pos.x && x < b[GUI_BT_CAM]->pos.x + s)
	{
		if	(y > b[GUI_BT_CAM]->pos.y && y < b[GUI_BT_CAM]->pos.y + s)
		{
			b[GUI_BT_CAM]->state = 1;
			b[GUI_BT_CUBE]->state = 0;
			e->hitobj->ishit = -1;
			e->need_regui = 1;
		}
	}
	else if (x > b[GUI_BT_CUBE]->pos.x && x < b[GUI_BT_CUBE]->pos.x + s)
	if	(y > b[GUI_BT_CUBE]->pos.y && y < b[GUI_BT_CUBE]->pos.y + s)
	{
		if (e->hitobj->index > -1)
		{
			b[GUI_BT_CAM]->state = 0;
			b[GUI_BT_CUBE]->state = 1;
			e->hitobj->ishit = 1;
			e->need_regui = 1;
		}
	}
}

/*
**	Handles all the things that should be evoked when button pressed.
**	(x) and (y) needed to calculate which button was clicked.
**	If button click leads to redraw event - it's being evoked here.
*/

int				handle_gui_click(int x, int y, t_env *e)
{
	handle_arrows(x, y, e);
	handle_camncube(x, y, e);
	if (e->need_regui == 1)
		draw_gui(e);
	if (e->need_rerender == 1)
		render(e);
	return (0);
}

/*
**	Returns pointer to newly created (malloc'ed) button at position [(x), (y)].
**	Icon is being drawn from appropriate xpm image named (fname).
*/

t_bt			*new_bt(int x, int y, int *i, t_env *e)
{
	t_bt	*bt;

	bt = (t_bt *)malloc(sizeof(t_bt));
	bt->pos = (t_v) {x, y, 0};
	bt->len = GUI_ICON_SIZE;
	bt->wid = GUI_ICON_SIZE;
	if (*i == GUI_BT_CAM)
		bt->state = 1;
	else
		bt->state = 0;
	bt->foo = press_mv_button;
	bt->ptimg = e->imgarr[(*i)++ * 2 + bt->state]->ptimg;
	return	(bt);
}

/*
**	TODO:
**	1)	Proper functions splits with accordings to norm.
**	2)	Depth changing buttons, rotations control switch.
*/
