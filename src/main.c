/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emayert <emayert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:29:07 by cschuste          #+#    #+#             */
/*   Updated: 2019/02/23 16:53:00 by emayert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

int		main(int ac, char **av)
{
	t_env *e;

	e = (t_env *)malloc(sizeof(t_env));
	init_env(e);
	if (ac == 2)
	{
		init_mlx(e);
		create_objects(e, av[1]);
		render(e);
		mlx_hook(e->win, 2, 1L, key_hook, e);
		mlx_hook(e->win, 4, ButtonPressMask, mouse_press, e);
		mlx_hook(e->win, 5, ButtonReleaseMask, mouse_release, e);
		mlx_hook(e->win, 6, PointerMotionMask, mouse_move, e);
		mlx_hook(e->win, 12, 1L, expose_hook, e);
		mlx_hook(e->win, 17, 1L, clean_n_close, e);
		mlx_loop(e->mlx);
	}
	ft_putendl(MSG_USAGE);
	clean_n_close(e);
}
