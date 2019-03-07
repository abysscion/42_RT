/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:34:01 by sb_fox            #+#    #+#             */
/*   Updated: 2019/03/07 10:48:34 by cschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	create_renvar(t_env *e, t_v dest)
{
	e->ren_var->start = e->cam->pos;
	e->ren_var->dest = dest;
	e->ren_var->min = 1;
	e->ren_var->max = RAY_LENMAX;
}

void	init_env(t_env *e)
{
	e->imgarr = (t_im **)malloc(sizeof(t_im *) * GUI_BT_NUM * 2);
	e->buttons = (t_bt **)malloc(sizeof(t_bt *) * GUI_BT_NUM);
	e->ren_var = (t_ren *)malloc(sizeof(t_ren));
	e->lit_var = (t_lc *)malloc(sizeof(t_lc));
	e->gui = (t_gui *)malloc(sizeof(t_gui));
	e->hitobj = (t_ho *)malloc(sizeof(t_ho));
	e->hitobj->ishit = -1;
	e->hitobj->index = -1;
	e->cam = (t_cam *)malloc(sizeof(t_cam));
	e->cam->rot = (t_v) {0, 0, 0};
	e->cam->pos = (t_v) {0, 0, 0};
	e->cam->view_port_addr = 0x0;
	e->objs = (t_oc *)malloc(sizeof(t_oc));
	e->objs->n_obj = 0;
	e->mlx = NULL;
	e->win = NULL;
	e->k = 0;
	e->mouse_pressed = 0;
}

void	init_mlx(t_env *e)
{
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, WIN_W + GUI_TOOLBAR_W, WIN_H, "Raytracer");
	e->cam->ptr_vp = mlx_new_image(e->mlx, WIN_W, WIN_H);
	e->cam->view_port_addr = (int *)mlx_get_data_addr(e->cam->ptr_vp,
		&e->cam->bits_per_pixel, &e->cam->size_line, &e->cam->endian);
}
