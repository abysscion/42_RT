/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disruption.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdibbert <fdibbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:44:42 by fdibbert          #+#    #+#             */
/*   Updated: 2019/04/17 16:45:51 by fdibbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			init_new_color(t_clr *new_color, t_surf *surf, t_env *env)
{
	double sin_check;

	if (surf->disruption == 1)
		*new_color = (((int)(env->ray.start.x + 1000)
			+ (int)(env->ray.start.y + 1000)) & 1) ?
			(t_clr){255 - surf->color.r, 255 - surf->color.g, 255 -
			surf->color.b} : surf->color;
	else if (surf->disruption == 2)
		*new_color = (((int)(env->ray.start.x + 1000) + (int)(env->ray.start.y
					+ 1000)) & 9) ? (t_clr){255 - surf->color.r,
					255 - surf->color.g, 255 - surf->color.b} : surf->color;
	else if (surf->disruption == 3)
	{
		sin_check = sin(env->ray.start.x) + sin(env->ray.start.y);
		if (sin_check < -0.3)
			*new_color = (t_clr){255 - surf->color.r, 255 -
							surf->color.g, 255 - surf->color.b};
		else if ((sin_check > -0.3) && (sin_check < 0.3))
			*new_color = (t_clr){(int)(surf->color.r * 0.3),
				(int)(surf->color.g * 0.6), (int)(surf->color.b * 0.45)};
		else
			*new_color = surf->color;
	}
	else
		*new_color = surf->color;
}
