/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 07:12:33 by sb_fox            #+#    #+#             */
/*   Updated: 2019/03/07 08:32:52 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

/*
**	Handles arrow buttons behaviour calling foo() if click was made in
**		icon's boundaries.
*/

static	void	handle_arrows(int x, int y, t_env *e)
{
	t_v		*ptv;

	if (e->hitobj->ishit == 1)
		ptv = &e->objs->objarr[e->hitobj->index]->pos;
	else
		ptv = &e->cam->pos;
	if (is_within_border(x, y, GUI_BT_AL, e) == 1)
	{
		e->buttons[GUI_BT_AL]->foo(&ptv->x, -1, e);
		e->buttons[GUI_BT_AL]->state = 1;
	}
	else if (is_within_border(x, y, GUI_BT_AR, e) == 1)
	{
		e->buttons[GUI_BT_AR]->foo(&ptv->x, 1, e);
		e->buttons[GUI_BT_AR]->state = 1;
	}
	else if (is_within_border(x, y, GUI_BT_AU, e) == 1)
	{
		e->buttons[GUI_BT_AU]->foo(&ptv->y, -1, e);
		e->buttons[GUI_BT_AU]->state = 1;
	}
	else if (is_within_border(x, y, GUI_BT_AD, e) == 1)
	{
		e->buttons[GUI_BT_AD]->foo(&ptv->y, 1, e);
		e->buttons[GUI_BT_AD]->state = 1;
	}
}

/*
**	Handles camera and object (cube) buttons behaviour switching buttons states
**		and changing redraw flags to 1 if click	was made in icon's boundaries.
*/

static	void	handle_camncube(int x, int y, t_env *e)
{
	if (is_within_border(x, y, GUI_BT_CAM, e) == 1)
	{
		e->buttons[GUI_BT_CAM]->state = 1;
		e->buttons[GUI_BT_CUBE]->state = 0;
		e->hitobj->ishit = -1;
		e->need_regui = 1;
	}
	else if (is_within_border(x, y, GUI_BT_CUBE, e) == 1)
		if (e->hitobj->index > -1)
		{
			e->buttons[GUI_BT_CAM]->state = 0;
			e->buttons[GUI_BT_CUBE]->state = 1;
			e->hitobj->ishit = 1;
			e->need_regui = 1;
		}
}

/*
**	Handles all the things that should be evoked when button pressed.
**	(x) and (y) needed to calculate which button was clicked.
**	If button click leads to redraw event - it's being evoked here.
*/

int				handle_gui_click(int x, int y, t_env *e)
{
	int	clicked;

	clicked = 0;
	handle_arrows(x, y, e);
	handle_camncube(x, y, e);
	draw_gui(e);
	render(e);
	if (e->need_regui == 1 || e->need_rerender == 1)
		clicked = 1;
	return (clicked);
}
