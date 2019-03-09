/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing_render.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdibbert <fdibbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 17:14:27 by fdibbert          #+#    #+#             */
/*   Updated: 2019/03/09 17:16:11 by fdibbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static t_v	vp_to_global2(t_v vp_p)
{
	t_v ret;

	ret.x = vp_p.x * 1 / (WIN_W * 2);
	ret.y = vp_p.y * 1 / (WIN_H * 2);
	ret.z = 1;
	return (ret);
}

void	aliasing_render(t_env *e, int i, int j)
{
	t_v				dest;
	int				k;
	unsigned char	*color;
	int				x;
	int				y;

	y = i;
	k = 0;
	while (y <= i + 1)
	{
		x = j;
		while (x <= j + 1)
		{
			dest = vp_to_global2((t_v){x, y, 0});
			dest = vec_rotate(e->cam->rot, dest);
			dest = vecnorm(dest);
			create_renvar(e, dest);
			color = trace_ray(e->ren_var, e, RECURSION);
			e->aliasing[k] = color[0] * 0x10000 + color[1] * 0x100 + color[2];
			free(color);
			k++;
			x++;
		}
		y++;
	}
}