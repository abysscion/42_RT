/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 20:26:12 by cschuste          #+#    #+#             */
/*   Updated: 2019/03/07 15:45:17 by cschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static	void	create_light(t_env *e)
{
	e->lnum = 3;
	e->light = (t_light **)malloc(sizeof(t_light *) * e->lnum);
	e->light[2] = (t_light *)malloc(sizeof(t_light));
	e->light[2]->type = "ambient";
	e->light[2]->intensity = 0.01;
	e->light[0] = (t_light *)malloc(sizeof(t_light));
	e->light[0]->type = "point";
	e->light[0]->intensity = 0.455;
	e->light[0]->pos = (t_v){-11, 0, 10};
	e->light[1] = (t_light *)malloc(sizeof(t_light));
	e->light[1]->type = "point";
	e->light[1]->intensity = 0.455;
	e->light[1]->pos = (t_v){11, 0, 10};
}

static	void	abuse_norme_0(t_env *e, int *i)
{
	cr_obj((t_bs){6, 7, 20, 0, 0, 0,
	2.8, 230, 230, 230, 5, 0, 0, T_SPHERE}, ++*i, e);
	cr_obj((t_bs){6, -7, 20, 0, 0, 0,
	2.8, 230, 230, 230, 5, 0, 0, T_SPHERE}, ++*i, e);
	cr_obj((t_bs){-6, 7, 20, 0, 0, 0,
	2.8, 230, 230, 230, 5, 0, 0, T_SPHERE}, ++*i, e);
	cr_obj((t_bs){-6, -7, 20, 0, 0, 0,
	2.8, 230, 230, 230, 5, 0, 0, T_SPHERE}, ++*i, e);
	cr_obj((t_bs){-6, 7, 40, 0, 0, 0,
	2.8, 230, 230, 230, 5, 0, 0, T_SPHERE}, ++*i, e);
	cr_obj((t_bs){-6, -7, 40, 0, 0, 0,
	2.8, 230, 230, 230, 5, 0, 0, T_SPHERE}, ++*i, e);
	cr_obj((t_bs){6, 7, 40, 0, 0, 0,
	2.8, 230, 230, 230, 5, 0, 0, T_SPHERE}, ++*i, e);
	cr_obj((t_bs){6, -7, 40, 0, 0, 0,
	2.8, 230, 230, 230, 5, 0, 0, T_SPHERE}, ++*i, e);
}

static	void	abuse_norme_1(t_env *e, int *i)
{
	cr_obj((t_bs){0, 5, 22, 0, 0, 0,
	1, 180, 0, 0, 100, 1, 0, T_SPHERE}, ++*i, e);
	cr_obj((t_bs){0, 0, 55, 0, 0, -1,
	0, 80, 140, 250, 0, 0, 0, T_PLANE}, ++*i, e);
	cr_obj((t_bs){0, 7, 0, 0, -1, 0,
	0, 150, 150, 150, 0, 0, 0, T_PLANE}, ++*i, e);
	cr_obj((t_bs){0, -7, 0, 0, 1, 0,
	0, 150, 150, 150, 0, 0, 0, T_PLANE}, ++*i, e);
	cr_obj((t_bs){-6, 0, 20, 0, -1, 0,
	1.5, 230, 230, 230, 10, 0, 0, T_CYLINDER}, ++*i, e);
	cr_obj((t_bs){6, 0, 20, 0, -1, 0,
	1.5, 230, 230, 230, 10, 0, 0, T_CYLINDER}, ++*i, e);
	cr_obj((t_bs){-6, 0, 40, 0, -1, 0,
	1.5, 230, 230, 230, 10, 0, 0, T_CYLINDER}, ++*i, e);
	cr_obj((t_bs){6, 0, 40, 0, -1, 0,
	1.5, 230, 230, 230, 10, 0, 0, T_CYLINDER}, ++*i, e);
}

void			create_scene_4(t_env *e)
{
	int		i;

	i = -1;
	e->objs->n_obj = 16;
	e->objs->objarr = (t_obj **)malloc(sizeof(t_obj *) * e->objs->n_obj);
	while (++i < e->objs->n_obj)
		e->objs->objarr[i] = (t_obj *)malloc(sizeof(t_obj));
	i = -1;
	abuse_norme_0(e, &i);
	abuse_norme_1(e, &i);
	create_light(e);
}
