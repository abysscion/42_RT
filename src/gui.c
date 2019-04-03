/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 13:47:08 by sb_fox            #+#    #+#             */
/*   Updated: 2019/04/03 10:29:37 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_gui(t_env *e)
{
	kiss_window_new(&e->gui->rblock, NULL, 1,
		RT__W + GUI_LBLOCK_W,			GUI_BAR_H - 2,
		GUI_RBLOCK_W,					RT__H + 2);
	kiss_window_new(&e->gui->lblock, NULL, 1,
		0, 								GUI_BAR_H - 2,
		GUI_LBLOCK_W,					RT__H + 2);
	kiss_window_new(&e->gui->bar, NULL, 1,
		0, 								0,
		WIN_W,							GUI_BAR_H);
	kiss_button_new(&e->gui->bt_arrup, &e->gui->lblock, "Exit",
		10,								10);
	e->gui->rblock.visible = 1;
	e->gui->lblock.visible = 1;
	e->gui->bar.visible = 1;
}

void	draw_gui(t_env *e)
{
	kiss_window_draw(&e->gui->rblock, e->sdl.renderer);
	kiss_window_draw(&e->gui->lblock, e->sdl.renderer);
	kiss_window_draw(&e->gui->bar, e->sdl.renderer);
	kiss_button_draw(&e->gui->bt_arrup, e->sdl.renderer);
}
