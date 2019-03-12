/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:29:07 by cschuste          #+#    #+#             */
/*   Updated: 2019/03/11 19:26:44 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		main(int argc, char **argv)
{
	t_env *env;

	env = (t_env *)malloc(sizeof(t_env));
	if (argc == 2)
	{
		init_env(env);
		init_mlx(env);
		//init_gui(env);
		parse_file(argv[1], env);
		render(env);
		mlx_hook(env->mlx.win_ptr, 2, 1L, key_hook, env);
	//	mlx_hook(env->mlx.win_ptr, 4, ButtonPressMask, mouse_press, env);
	//	mlx_hook(env->mlx.win_ptr, 5, ButtonReleaseMask, mouse_release, env);
	//	mlx_hook(env->mlx.win_ptr, 6, PointerMotionMask, mouse_move, env);
	//	mlx_hook(env->mlx.win_ptr, 12, 1L, expose_hook, env);
	//	mlx_hook(env->mlx.win_ptr, 17, 1L, clean_n_close, env);
		mlx_loop(env->mlx.mlx_ptr);
	}
	ft_putendl(MSG_USAGE);
	exit(0);
}
