/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_basis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 13:53:35 by eloren-l          #+#    #+#             */
/*   Updated: 2019/04/16 19:06:40 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	calc_basis(t_surf *surf)
{
	surf->basis.z = surf->orientation;
	if (surf->orientation.x == 0 && surf->orientation.y == 0 &&
		(surf->orientation.z == 1 || surf->orientation.z == -1))
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
