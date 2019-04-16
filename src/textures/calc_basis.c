/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_basis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 13:53:35 by eloren-l          #+#    #+#             */
/*   Updated: 2019/04/16 20:16:47 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	calc_basis(t_surf *surf)
{
	surf->basis.z = surf->rotation;
	if (surf->rotation.x == 0 && surf->rotation.y == 0 &&
		(surf->rotation.z == 1 || surf->rotation.z == -1))
	{
		surf->basis.x = (t_v){1, 0, 0};
		surf->basis.y = (t_v){0, 1, 0};
		return ;
	}
	surf->basis.y = vecnorm(vecmult_vec(surf->basis.z, (t_v){0, 0, 1}));
	surf->basis.x = vecnorm(vecmult_vec(surf->basis.y, surf->basis.z));
	if ((int)(surf->basis.y.x * 1e6) == 0 &&
		(int)(surf->basis.y.y * 1e6) == 0 &&
		(int)(surf->basis.y.z * 1e6) == 0)
	{
		surf->basis.x = (t_v){1, 0, 0};
		surf->basis.y = (t_v){0, 1, 0};
		surf->basis.z = (t_v){0, 0, 1};
		return ;
	}
}
