/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing_render.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 17:14:27 by fdibbert          #+#    #+#             */
/*   Updated: 2019/03/12 12:08:59 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*static t_v	vp_to_global2(t_v vp_p)
{
	t_v ret;

	ret.x = vp_p.x * 1 / (WIN_W * 2);
	ret.y = vp_p.y * 1 / (WIN_H * 2);
	ret.z = 1;
	return (ret);
} */

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

			dest = (t_v){x * 1.0 / WIN_W, y * 1.0 / WIN_H, 1.0};
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