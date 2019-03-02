/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 05:21:02 by emayert           #+#    #+#             */
/*   Updated: 2019/03/02 04:38:05 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

/*
**	Changes given values of position (val) by (add), switches redraw flag.
*/

void	press_mv_button(double *val, double add, int *need_redraw)
{
	*val += add;
	*need_redraw = 1;
}

/*
**	Handles all the things that should be evoked when button pressed.
**	(x) and (y) needed to calculate which button was clicked.
**	If button click leads to redraw event - it's being evoked here.
*/

void	handle_gui_click(int x, int y, t_env *e)
{
	int s;
	int i;

	i = -1;
	s = GUI_ICON_SIZE;
	while (++i < GUI_BT_NUM)
	{
		if (x > e->buttons[i]->pos.x && x < e->buttons[i]->pos.x + s)
			if (y > e->buttons[i]->pos.y && y < e->buttons[i]->pos.y + s)
			{
				if (i == 0)
					e->buttons[i]->foo(&e->cam->pos.y, -1, &e->need_redraw);
				else if (i == 1)
					e->buttons[i]->foo(&e->cam->pos.y, 1, &e->need_redraw);
				else if (i == 2)
					e->buttons[i]->foo(&e->cam->pos.x, -1, &e->need_redraw);
				else if (i == 3)
					e->buttons[i]->foo(&e->cam->pos.x, 1, &e->need_redraw);
			}
	}
	if (e->need_redraw)
		render(e);
}

/*
**	Returns pointer to newly created (malloc'ed) button at position [(x), (y)].
**	Icon is being drawn from appropriate xpm image named (fname).
*/

t_bt	*new_bt(int x, int y, char *name, t_env *e)
{
	t_bt	*bt;

	bt = (t_bt *)malloc(sizeof(t_bt));
	bt->pos = (t_v) {x, y, 0};
	bt->fname = name;
	bt->len = 32;
	bt->wid = 32;
	bt->state = 0;
	bt->foo = press_mv_button;
	bt->imgon = mlx_xpm_file_to_image(e->mlx, bt->fname, &bt->len, &bt->wid);
	return	(bt);
}

/*
**	Malloc's array of pointers to structure (s_button).
**	Then fills array cells with newly crated (new_bt()) buttons.
*/

void	init_buttons(t_env *e)
{
	e->buttons = (t_bt **)malloc(sizeof(t_bt *) * GUI_BT_NUM);
	e->buttons[0] = new_bt(WIN_W + GUI_MARGIN + GUI_ICON_SIZE + GUI_GAP,
							GUI_MARGIN,
							"img/arr_up.xpm", e);
	e->buttons[1] = new_bt(WIN_W + GUI_MARGIN + GUI_ICON_SIZE + GUI_GAP,
							GUI_MARGIN + GUI_ICON_SIZE * 2 + GUI_GAP * 2,
							"img/arr_down.xpm", e);
	e->buttons[2] = new_bt(WIN_W + GUI_MARGIN,
							GUI_MARGIN + GUI_ICON_SIZE + GUI_GAP,
							"img/arr_left.xpm", e);
	e->buttons[3] = new_bt(WIN_W + GUI_MARGIN + GUI_ICON_SIZE * 2 + GUI_GAP * 2,
							GUI_MARGIN + GUI_ICON_SIZE + GUI_GAP,
							"img/arr_right.xpm", e);
}

/*
**	Draws whole GUI content on screen by putting appropriate mlx images.
*/

void	draw_gui(t_env *e)
{
	int i;

	i = -1;
	while (++i < GUI_BT_NUM)
		mlx_put_image_to_window(e->mlx, e->win, e->buttons[i]->imgon,
								e->buttons[i]->pos.x, e->buttons[i]->pos.y);
}

/*
**	TODO: animations by button states, camera/object control switch button.
*/
