/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scener.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 20:26:12 by cschuste          #+#    #+#             */
/*   Updated: 2019/03/07 15:07:52 by cschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	cr_obj(t_bs bs, int i, t_env *e)
{
	t_oc	*p;

	p = e->objs;
	p->objarr[i]->colour[0] = bs.r;
	p->objarr[i]->colour[1] = bs.g;
	p->objarr[i]->colour[2] = bs.b;
	p->objarr[i]->pos = (t_v){bs.posx, bs.posy, bs.posz};
	p->objarr[i]->rot = (t_v){bs.rotx, bs.roty, bs.rotz};
	p->objarr[i]->radius = bs.rad;
	p->objarr[i]->specular = bs.spec;
	p->objarr[i]->reflect = bs.reflect;
	p->objarr[i]->transp = bs.transp;
	p->objarr[i]->type = bs.type;
}

void	create_objects(t_env *e, char *av)
{
	if (!ft_strcmp(av, "0"))
		create_scene_0(e);
	else if (!ft_strcmp(av, "1"))
		create_scene_1(e);
	else if (!ft_strcmp(av, "2"))
		create_scene_2(e);
	else if (!ft_strcmp(av, "3"))
		create_scene_3(e);
	else if (!ft_strcmp(av, "4"))
		create_scene_4(e);
	else
	{
		ft_putendl(MSG_USAGE);
		clean_n_close(e);
		exit(0);
	}
}
