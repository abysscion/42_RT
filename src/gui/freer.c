/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 17:20:00 by emayert           #+#    #+#             */
/*   Updated: 2019/02/22 21:20:51 by cschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

static	void	free_env(t_env *e)
{
	if (e)
	{
		if (e->mlx)
		{
			if (e->cam)
			{
				if (e->cam->ptr_vp)
					mlx_destroy_image(e->mlx, e->cam->ptr_vp);
				free(e->cam);
			}
			if (e->objs)
				free(e->objs);
			if (e->win)
				mlx_destroy_window(e->mlx, e->win);
			if (e->lit_var)
				free(e->lit_var);
			if (e->ren_var)
				free(e->ren_var);
			free(e->mlx);
		}
		free(e);
	}
}

int				clean_n_close(t_env *e)
{
	free_env(e);
	exit(0);
}
