/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_basis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 13:53:35 by eloren-l          #+#    #+#             */
/*   Updated: 2019/04/05 13:18:31 by cschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	calc_basis_cyl_cone(t_surf *surf)
{
	surf->basis.y = surf->orientation;
	surf->basis.x = vecnorm(vecmult_vec(surf->basis.y, (t_v){0, 0, 1}));
	if ((int)(surf->basis.x.x * 1e6) == 0 &&
		(int)(surf->basis.x.y * 1e6) == 0 &&
		(int)(surf->basis.x.z * 1e6) == 0)
		surf->basis.x = (t_v){0, 1, 0};

}

static void	calc_basis_sphere(t_surf *surf)
{
	surf->basis.y = surf->orientation;
	surf->basis.x = vecnorm(vecmult_vec(surf->basis.y, (t_v){0, 0, 1}));
	if ((int)(surf->basis.x.x * 1e6) == 0 &&
		(int)(surf->basis.x.y * 1e6) == 0 &&
		(int)(surf->basis.x.z * 1e6) == 0)
		surf->basis.x = (t_v){0, 1, 0};
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
	if (surf->type == T_CYLINDER || surf->type == T_CONE || surf->type == T_PARAB)
		calc_basis_cyl_cone(surf);
	if (surf->type == T_PLANE)
		calc_basis_plane(surf);
	printf("%lf %lf %lf ; %lf %lf %lf\n", surf->basis.x.x, surf->basis.x.y, surf->basis.x.z,
	surf->basis.y.x, surf->basis.y.y, surf->basis.y.z);
}
