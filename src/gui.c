/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 05:21:02 by sb_fox            #+#    #+#             */
/*   Updated: 2019/03/04 13:18:15 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

/*
**	Changes given values of position (val) by (add), switches redraw flags.
*/

void			press_mv_button(double *val, double add, void *e)
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
**	Handles all the things that should be evoked when button pressed.
**	(x) and (y) needed to calculate which button was clicked.
**	If button click leads to redraw event - it's being evoked here.
*/

int				handle_gui_click(int x, int y, t_env *e)
{
	handle_arrows(x, y, e);
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
	if (*i == GUI_BT_CUBE)
		bt->state = 1;
	else
		bt->state = 0;
	bt->foo = press_mv_button;
	bt->ptimg = e->imgarr[(*i)++ * 2 + bt->state]->ptimg;
	return	(bt);
}

/*
**	Inits buttons array with newly created (new_bt()) buttons.
**	Buttons positions calculates from GUI_ variables.
**	Imagine @ is picture and Z is another picture:
**	_____________________________________
**	|				 ^					|
**	|	  Gui margin |					|
**	|  Gui margin	 v	  Gui gap		|
**	|<----------->   @   <-------->  Z  |
**	|			  |<--->|				|
**	|		   Gui icon size			|
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
**	Draws whole GUI content on screen by putting appropriate mlx images.
*/

void			draw_gui(t_env *e)
{
	int i;

	i = -1;
	while (++i < GUI_BT_NUM)
	{
		if (i >= GUI_BT_AL && i <= GUI_BT_AD)
		{
			if (e->buttons[i]->state == 1)
				e->buttons[i]->ptimg = e->imgarr[2 * i + 1]->ptimg;
			else
				e->buttons[i]->ptimg = e->imgarr[2 * i]->ptimg;
		}
		mlx_put_image_to_window(e->mlx, e->win, e->buttons[i]->ptimg,
								e->buttons[i]->pos.x, e->buttons[i]->pos.y);
		if (i >= GUI_BT_AL && i <= GUI_BT_AD)
			e->buttons[i]->state = 0;
	}
	e->need_regui = 0;
}

/*
**	Should've create another sequence of foo's calls, cuz
**		mine is such a garbage. Mb should've add some structures for vars.
**	Camera and object choose toggling. Free all shit i've malloc'ed.
*/
