/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:22:32 by eloren-l          #+#    #+#             */
/*   Updated: 2019/03/24 17:54:50 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


void		calc_basis_cylinder(t_surf *surf)
{
	surf->basis.y = surf->orientation;
	if (surf->basis.y.x == 0 && surf->basis.y.y == 0 &&
		(surf->basis.y.z == 1 || surf->basis.y.z == -1))
		surf->basis.x = (t_v){0, 1, 0};
	else
		surf->basis.x = vecmult_vec(surf->basis.y, (t_v){0, 0, 1});
}

void		calc_basis_sphere(t_surf *surf)
{
	t_v		pole;
	t_v		equator;

	pole = vecsum(surf->position, (t_v){0,surf->radius,0});
	equator = vecsum(surf->position, (t_v){surf->radius,0,0});
	surf->basis.x = vecnorm(vecsub(equator, surf->position));
	surf->basis.y = vecnorm(vecsub(pole, surf->position));
}

void		calc_basis(t_surf *surf)
{
	if (surf->type == T_SPHERE)
	{
		calc_basis_sphere(surf);
		return ;
	}
	if (surf->type == T_CYLINDER)
	{
		calc_basis_cylinder(surf);
		return ;
	}
	if (surf->orientation.x == 0 && surf->orientation.y == 0 &&
		(surf->orientation.z == 1 || surf->orientation.z == -1))
	{
		surf->basis.x = (t_v){1,0,0};
		surf->basis.y = (t_v){0,1,0};
		return ;
	}
	surf->basis.z = surf->orientation;
	surf->basis.y = vecmult_vec(surf->basis.z, (t_v){0,0,1});
	surf->basis.x = vecmult_vec(surf->basis.y, surf->basis.z);
}

void		check_param_num(char **param, int i, char *name)
{
	int		j;

	j = 0;
	while (*param)
	{
		param++;
		j++;
	}
	if (i == j)
		return ;
	ft_putstr("Wrong ");
	ft_putstr(name);
	ft_putstr(" arguments. Exiting.\n");
	exit(0);
}

void		check_floats(char **param, int i, char *name)
{
	char	**num;
	int		j;

	j = 0;
	while (j < i)
	{
		num = ft_strsplit(param[j++], '.');
		check_param_num(num, 2, name);
		free_words(num);
	}
}

void		free_words(char **words)
{
	int		i;

	i = 0;
	while (words[i])
		free(words[i++]);
	free(words);
}

void		set_surf_type(char *surf, t_lst *lst)
{
	if (ft_strcmp(surf, "sphere") == 0)
	{
		lst->type = T_SPHERE;
		((t_surf *)lst->obj)->type = T_SPHERE;
	}
	else if (ft_strcmp(surf, "plane") == 0)
	{
		lst->type = T_PLANE;
		((t_surf *)lst->obj)->type = T_PLANE;
	}
	else if (ft_strcmp(surf, "cylinder") == 0)
	{
		lst->type = T_CYLINDER;
		((t_surf *)lst->obj)->type = T_CYLINDER;
	}
	else if (ft_strcmp(surf, "cone") == 0)
	{
		lst->type = T_CONE;
		((t_surf *)lst->obj)->type = T_CONE;
	}
}