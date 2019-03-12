/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 01:23:45 by emayert           #+#    #+#             */
/*   Updated: 2019/03/12 11:43:45 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


/*
**	Translates object using it's pos->(val) to change it by (add).
**	Parameter (rd) needed for possibility of translating without
**		immediate full picture rerender.
*/

void	translate_obj(double *val, double add, int rd, t_env *e)
{
	*val += add;
	if (rd == 1)
		e->need_rerender = 1;
}
