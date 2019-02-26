/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emayert <emayert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 01:23:45 by emayert           #+#    #+#             */
/*   Updated: 2019/02/26 14:53:12 by emayert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

/*
**	Raytraces all of the objects, trying to retrieve hit type and index.
**	Sets index and type of proper object if ray hit.
**	Clears index and type variables if nothing hit.
*/

void	rayhit_obj(t_v dest, t_env *e)
{
	double	closest;
	double	t[2];
	int		cross;
	int		i;

	closest = RAY_LENMAX;
	cross = 0;
	e->hitobj->ishit = 0;
	i = -1;
	e->hitobj->ishit = 0;
	dest = vecnorm(vec_rotate(e->cam->rot, dest));
	while (++i < e->objs->n_obj)
	{
		if (e->objs->objarr[i]->type == T_PLANE)
			cross = intersect_plane(e->cam->pos, dest, e->objs->objarr[i], &t[0]);
		else if (e->objs->objarr[i]->type == T_SPHERE)
			cross = intersect_sphere(e->cam->pos, dest, e->objs->objarr[i], &t[0]);
		else if (e->objs->objarr[i]->type == T_CYLINDER)
			cross = intersect_cylinder(e->cam->pos, dest, e->objs->objarr[i], &t[0]);
		else if (e->objs->objarr[i]->type == T_CONE)
			cross = intersect_cone(e->cam->pos, dest, e->objs->objarr[i], &t[0]);
		if (cross)
		{
			if (t[0] > 1 && t[0] < RAY_LENMAX && t[0] < closest)
			{
				closest = t[0];
				e->hitobj->index = i;
				e->hitobj->type = e->objs->objarr[i]->type;
			}
			if (e->objs->objarr[i]->type != T_PLANE &&
				t[1] > 1 && t[1] < RAY_LENMAX && t[1] < closest)
			{
				closest = t[1];
				e->hitobj->index = i;
				e->hitobj->type = e->objs->objarr[i]->type;
			}
		}
	}
	if (closest == RAY_LENMAX)
	{
		e->hitobj->type = -1;
		e->hitobj->index = -1;
	}
	if (e->hitobj->type >= T_PLANE && e->hitobj->type <= T_CONE)
		e->hitobj->ishit = 1;
}

/*
**	Prints information about object that was hit by rayhit_obj().
*/

void	print_info_about_hitobj(t_env *e)
{
	int	index;

	index = e->hitobj->index;
	t_obj *p = e->objs->objarr[index];
	if (e->hitobj->ishit > -1)
	{
		if (e->hitobj->type == T_SPHERE)
		{
			printf("\vSphere №%d\n", index);
			printf("\tPosition: (%7.2f %7.2f %7.2f)\n", p->pos.x, p->pos.y, p->pos.z);
			printf("\tRotation: (%7.2f %7.2f %7.2f)\n", p->rot.x, p->rot.y, p->rot.z);
			printf("\tColor:    (%d, %d, %d)\n", p->colour[0], p->colour[1], p->colour[2]);
			printf("\tRadius:   %.2f\n", p->radius);
		}
		else if (e->hitobj->type == T_PLANE)
		{
			printf("\vPlane №%d\n", index);
			printf("\tPosition: (%7.2f %7.2f %7.2f)\n", p->pos.x, p->pos.y, p->pos.z);
			printf("\tRotation: (%7.2f %7.2f %7.2f)\n", p->rot.x, p->rot.y, p->rot.z);
		}
		else if (e->hitobj->type == T_CYLINDER)
		{
			printf("\vCylinder №%d\n", index);
			printf("\tPosition: (%7.2f %7.2f %7.2f)\n", p->pos.x, p->pos.y, p->pos.z);
			printf("\tRotation: (%7.2f %7.2f %7.2f)\n", p->rot.x, p->rot.y, p->rot.z);
			printf("\tRadius:   %.2f\n", p->radius);
		}
		else if (e->hitobj->type == T_CONE)
		{
			printf("\vCone №%d\n", index);
			printf("\tPosition: (%7.2f %7.2f %7.2f)\n", p->pos.x, p->pos.y, p->pos.z);
			printf("\tRotation: (%7.2f %7.2f %7.2f)\n", p->rot.x, p->rot.y, p->rot.z);
			printf("\tRadius:   %.2f\n", p->radius);
		}
	}
}

/*
**	Reacts on precoded key presses.
*/

static	void	key_handler2(int key, t_env *e)
{
	if (key == K_NUM_4)
		e->cam->rot.y -= M_PI / 180 * ROT_STEP;
	else if (key == K_NUM_6)
		e->cam->rot.y += M_PI / 180 * ROT_STEP;
	if (key == K_NUM_2)
		e->cam->rot.x -= M_PI / 180 * ROT_STEP;
	else if (key == K_NUM_8)
		e->cam->rot.x += M_PI / 180 * ROT_STEP;
	if (key == K_NUM_7)
		e->cam->rot.z -= M_PI / 180 * ROT_STEP;
	else if (key == K_NUM_9)
		e->cam->rot.z += M_PI / 180 * ROT_STEP;
}

void			key_handler(int key, t_env *e)
{
	if (key == K_ESC)
		exit(0);
	if (key == K_ARRUP)
		e->cam->pos.y -= 1;
	if (key == K_ARRDOWN)
		e->cam->pos.y += 1;
	if (key == K_ARRLEFT)
		e->cam->pos.x -= 1;
	if (key == K_ARRRIGHT)
		e->cam->pos.x += 1;
	if (key == K_NUM_PLUS)
		e->cam->pos.z += 2;
	if (key == K_NUM_MINUS)
		e->cam->pos.z -= 2;
	key_handler2(key, e);
}
