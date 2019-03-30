/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_basis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 13:53:35 by eloren-l          #+#    #+#             */
/*   Updated: 2019/03/30 15:41:45 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	calc_basis_cyl_cone(t_surf *surf)
{
	surf->basis.y = surf->orientation;
	if (surf->basis.y.x == 0 && surf->basis.y.y == 0 &&
		(surf->basis.y.z == 1 || surf->basis.y.z == -1))
		surf->basis.x = (t_v){0, 1, 0};
	else
		surf->basis.x = vecmult_vec(surf->basis.y, (t_v){0, 0, 1});
}

static void	calc_basis_sphere(t_surf *surf)
{
	surf->basis.y = surf->orientation;
	if (surf->basis.y.x == 0 && surf->basis.y.y == 0 &&
		(surf->basis.y.z == 1 || surf->basis.y.z == -1))
		surf->basis.x = (t_v){0, 1, 0};
	else
		surf->basis.x = vecmult_vec(surf->basis.y, (t_v){0, 0, 1});
}

static void	calc_basis_plane(t_surf *surf)
{
	if (surf->orientation.x == 0 && surf->orientation.y == 0 &&
		(surf->orientation.z == 1 || surf->orientation.z == -1))
	{
		surf->basis.x = (t_v){1,0,0};
		surf->basis.y = (t_v){0,1,0};
	}
	else
	{
		surf->basis.z = surf->orientation;
		surf->basis.y = vecmult_vec(surf->basis.z, (t_v){0,0,1});
		surf->basis.x = vecmult_vec(surf->basis.y, surf->basis.z);
	}
}

void		calc_basis(t_surf *surf)
{
	if (surf->type == T_SPHERE)
		calc_basis_sphere(surf);
	if (surf->type == T_CYLINDER || surf->type == T_CONE)
		calc_basis_cyl_cone(surf);
	if (surf->type == T_PLANE)
		calc_basis_plane(surf);
}
