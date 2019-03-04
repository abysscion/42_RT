/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:34:01 by sb_fox            #+#    #+#             */
/*   Updated: 2019/03/04 12:06:56 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

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

void	init_env(t_env *e)
{
	e->objs = (t_oc *)malloc(sizeof(t_oc));
	e->cam = (t_cam *)malloc(sizeof(t_cam));
	e->hitobj = (t_ho *)malloc(sizeof(t_ho));
	e->lit_var = (t_lc *)malloc(sizeof(t_lc));
	e->ren_var = (t_ren *)malloc(sizeof(t_ren));
	e->imgarr = (t_im **)malloc(sizeof(t_im *) * GUI_BT_NUM * 2);
	e->buttons = (t_bt **)malloc(sizeof(t_bt *) * GUI_BT_NUM);
	e->cam->rot = (t_v) {0, 0, 0};
	e->objs->n_obj = 0;
	e->cam->pos = (t_v) {0, 0, 0};
	e->hitobj->ishit = -1;
	e->cam->view_port_addr = 0x0;
	e->mlx = NULL;
	e->win = NULL;
	e->k = 0;
	e->need_regui = 1;
	e->need_rerender = 0;
	e->mouse_pressed = 0;
}

void	init_mlx(t_env *e)
{
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, WIN_W + GUI_GAP * 2 + GUI_ICON_SIZE * 3 +
							GUI_MARGIN * 2, WIN_H, "Raytracer");
	e->cam->ptr_vp = mlx_new_image(e->mlx, WIN_W, WIN_H);
	e->cam->view_port_addr = (int *)mlx_get_data_addr(e->cam->ptr_vp,
		&e->cam->bits_per_pixel, &e->cam->size_line, &e->cam->endian);
}
