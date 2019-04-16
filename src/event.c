/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 05:21:02 by emayert           #+#    #+#             */
/*   Updated: 2019/04/16 18:40:05 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	void	getObjByClick(t_env *e, t_obj **obj, double *cDist)
{
	double	roots[2];
	int		interType;
	t_lst	*surface;
	t_lst	*temp;

	interType = 0;
	*cDist = e->ray.max;
	temp = e->objects;
	while (temp)
	{
		surface = ((t_obj *)temp->obj)->surfaces;
		while (surface)
		{
			interType = choose_type(e, surface, roots);
			if (interType && roots[0] > e->ray.min && roots[0] < *cDist)
			{
				*cDist = roots[0];
				obj == NULL ? NULL : (*obj = temp->obj);
			}
			if (interType && roots[1] > e->ray.min && roots[1] < *cDist)
			{
				*cDist = roots[1];
				obj == NULL ? NULL : (*obj = temp->obj);
			}
			surface = surface->next;
		}
		temp = temp->next;
	}
}

static	void	mouse_click(SDL_Event *event, t_env *e)
{
	SDL_Rect	rect;
	t_obj		*obj;
	t_v			dest;
	t_v			p;
	double		closeDist;

	rect = (SDL_Rect) {GUI_LBLOCK_W + kiss_edge, kiss_edge, RT__W, RT__H};
	if (kiss_pointinrect(event->button.x, event->button.y, &rect))
	{
		p.x = (event->button.x - e->constants.half_render_w - GUI_LBLOCK_W) / (double)RT__W;
		p.y = -(event->button.y - e->constants.half_render_h) / (double)RT__H;
		dest = (t_v){p.x, p.y, 1.0};
		dest = vecnorm(vec_rotate(e->cam.rotation, dest));
		init_ray(e, dest);
		getObjByClick(e, &obj, &closeDist);
		if (closeDist < e->ray.max)
		{
			e->gui->selected_object_type = GUI_SELECTED_TYPE_OBJ;
			if (e->gui->selected_object == (t_obj *)obj)
				e->gui->win_info.visible ^= 1;
			else
			{
				e->gui->selected_object = (t_obj *) obj;
				e->gui->win_info.visible = 1;
			}
			e->gui->need_update_info = 1;
			draw_all(e);
		}
	}
}

void			events_handler(SDL_Event *event, t_env *env)
{
	if (event->type == SDL_MOUSEBUTTONDOWN)
		mouse_click(event, env);
	else if (event->type == SDL_KEYDOWN)
		sdl_key_press_events(event, env);
}
