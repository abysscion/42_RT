/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 10:08:37 by cschuste          #+#    #+#             */
/*   Updated: 2019/03/12 15:53:17 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	max_color(double intens, unsigned char color, int *remain)
{
	*remain = 0;
	if (intens * color > 255)
	{
		*remain = (intens * color - 255) / 3;
		return (255);
	}
	return (intens * color);
}

void			calc_color(t_clr *color, double intens, t_surf *surface)
{
	int	remain;

	color->r = max_color(intens, surface->color.r, &remain);
	color->g = surface->color.g + remain > 255 ?
				255 : surface->color.g + remain;
	color->b = surface->color.b + remain > 255 ?
				255 : surface->color.b + remain;
	color->g = max_color(intens, color->g, &remain);
	color->r = color->r + remain > 255 ? 255 : color->r + remain;
	color->b = color->b + remain > 255 ? 255 : color->b + remain;
	color->b = max_color(intens, color->b, &remain);
	color->g = color->g + remain > 255 ? 255 : color->g + remain;
	color->r = color->r + remain > 255 ? 255 : color->r + remain;
}

void			calc_ref_color(t_clr *color, t_clr *ref_color, t_surf *surface)
{
	color->r = color->r * (1 - surface->reflect) + ref_color->r *
				surface->reflect;
	color->g = color->g * (1 - surface->reflect) + ref_color->g *
				surface->reflect;
	color->b = color->b * (1 - surface->reflect) + ref_color->b *
				surface->reflect;
}

t_v				calc_reflected_ray(t_v direction, t_v bisect)
{
	t_v	reflected_ray;

	reflected_ray = vecmult_num(vecmult_num(bisect, 2),
					vecmult_scal(bisect, direction));
	reflected_ray = vecsub(reflected_ray, direction);
	return (reflected_ray);
}
