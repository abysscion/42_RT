/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:29:07 by cschuste          #+#    #+#             */
/*   Updated: 2019/04/17 12:02:08 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	void	sdl_loop(t_env *env)
{
	SDL_Event	event;
	int			quit;
	int			*draw;

	quit = 0;
	draw = &env->gui->need_redraw;
	while (!quit)
	{
		SDL_Delay(10);
		while (SDL_PollEvent(&event) != 0)
		{
			if ((event.type == SDL_KEYDOWN &&
				event.key.keysym.sym == SDLK_ESCAPE) || event.type == SDL_QUIT)
				quit = 1;
			events_handler(&event, env);
			gui_handle_events(env, &event, draw);
		}
		kiss_combobox_event(&env->gui->cbb_light, NULL, draw);
		if (*draw == 1)
			draw_all(env);
	}
	SDL_DestroyWindow(env->sdl.window);
	kiss_clean(&env->gui->objarr);
	SDL_Quit();
	exit(0);
}

int				main(int argc, char **argv)
{
	t_env *env;

	if (argc == 2 || argc == 3)
	{
		check_filename(argv[1]);
		env = (t_env *)malloc(sizeof(t_env));
		init_env(env, argv);
		parse_file(argv[1], env);
		init_gui(env);
		adjust_objects(env);
		draw_all(env);
		sdl_loop(env);
	}
	ft_putendl(MSG_USAGE);
	exit(0);
}
