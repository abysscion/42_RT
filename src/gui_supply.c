/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_supply.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 06:41:38 by sb_fox            #+#    #+#             */
/*   Updated: 2019/03/07 09:40:34 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int		is_within_border(int x, int y, int bt_index, t_env *e)
{
	t_bt	**b;
	int		s;

	b = e->buttons;
	s = GUI_ICON_SIZE;
	if (x > b[bt_index]->pos.x && x < b[bt_index]->pos.x + s)
		if	(y > b[bt_index]->pos.y && y < b[bt_index]->pos.y + s)
			return (1);
	return (0);
}

/*
**	Changes given values of position (val) by (add), switches redraw flags.
*/

void	press_mv_button(double *val, double add, void *e)
{
	t_env	*env;

	env = (t_env *)e;
	translate_obj(val, add, 1, e);
	env->need_regui = 1;
}
