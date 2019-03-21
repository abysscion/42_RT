/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:29:07 by cschuste          #+#    #+#             */
/*   Updated: 2019/03/21 20:41:52 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	sdl_loop(t_env *env)
{
	char		quit;
	SDL_Event	event;

	quit = 0;
	while(!quit)
	{
		while(SDL_PollEvent(&event) != 0)
			if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
				quit = 1;
			else if (event.type == SDL_KEYDOWN)
				sdl_key_press_events(event.key.keysym.sym, env);
	}
	SDL_DestroyWindow(env->sdl.window);
	SDL_Quit();
	exit(0);
}

int			main(int argc, char **argv)
{
	t_env *env;

	int		 	state;

	state = 0;

	env = (t_env *)malloc(sizeof(t_env));
	env->sdl.image = (int *)malloc(sizeof(int) * WIN_H * WIN_H);
	SDL_CreateWindowAndRenderer(WIN_H, WIN_W, 0, &(env->sdl.window), &(env->sdl.renderer));


	if (argc == 2)
	{
		//init_gui(env);
		load_texture(env);
		init_env(env);
		parse_file(argv[1], env);
		render(env);
		sdl_loop(env);
	}
	ft_putendl(MSG_USAGE);
	exit(0);
}
