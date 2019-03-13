/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing_render.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdibbert <fdibbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 17:14:27 by fdibbert          #+#    #+#             */
/*   Updated: 2019/03/13 17:00:03 by fdibbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	anti_aliasing_render(t_env *env, int i, int j)
{
	t_v		dest;
	t_clr	color;
	int		k;
	int		x;
	int		y;

	y = i;
	k = 0;
	while (y <= i + 1)
	{
		x = j;
		while (x <= j + 1)
		{

			dest = (t_v){x * 1.0 / (WIN_W * 2), y * 1.0 / (WIN_H * 2), 1.0};
			dest = vecnorm(vec_rotate(env->cam.rotation, dest));
			init_ray(env, dest);
			color = trace_ray(env, RECURSION);		
			env->aliasing[k] = (color.r << 16) + (color.g << 8) + color.b;
			k++;
			x++;
		}
		y++;
	}
}