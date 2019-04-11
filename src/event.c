/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 05:21:02 by emayert           #+#    #+#             */
/*   Updated: 2019/04/10 13:41:23 by sb_fox           ###   ########.fr       */
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

	rect = (SDL_Rect) {GUI_LBLOCK_W, GUI_BAR_H, RT__W, RT__H};
	if (kiss_pointinrect(event->button.x, event->button.y, &rect))
	{
		p.x = (event->button.x - e->abuse.hrw - GUI_LBLOCK_W) / (double)RT__W;
		p.y = -(event->button.y - e->abuse.hrh - GUI_BAR_H) / (double)RT__H;
		dest = (t_v){p.x, p.y, 1.0};
		dest = vecnorm(vec_rotate(e->cam.rotation, dest));
		init_ray(e, dest);
		getObjByClick(e, &obj, &closeDist);
		if (closeDist < e->ray.max)
		{
			// ((t_surf *)obj->surfaces->obj)->position.x += 2;
			// obj->offset.x += 2;
			e->flags.need_render = 1;
		}
	}
}

void			events_handler(SDL_Event *event, t_env *env)
{
	if (event->type == SDL_MOUSEBUTTONDOWN)
		mouse_click(event, env);
	else
		sdl_key_press_events(event, env);
	draw_all(env);
}
