/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:29:07 by cschuste          #+#    #+#             */
/*   Updated: 2019/04/04 03:07:58 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void 		button_event(kiss_button *button, SDL_Event *e, int *draw, int *quit)
{
	if (kiss_button_event(button, e, draw))
		*quit = 1;
}

static void	sdl_loop(t_env *env)
{
	SDL_Event	event;
	int			quit;
	int			draw;

	quit = 0;
	while(!quit)
	{
		SDL_Delay(10);
		while(SDL_PollEvent(&event) != 0)
		{
			if ((event.type == SDL_KEYDOWN &&
				event.key.keysym.sym == SDLK_ESCAPE) || event.type == SDL_QUIT)
				quit = 1;
			else if (event.type == SDL_KEYDOWN)
				sdl_key_press_events(event.key.keysym.sym, env);
			kiss_window_event(&env->gui->rblock, &event, &draw);
			kiss_window_event(&env->gui->lblock, &event, &draw);
			kiss_window_event(&env->gui->bar, &event, &draw);
			button_event(&env->gui->bt_arrup, &event, &draw, &quit);
		}
		if (draw == 0)
			continue;
		/*
		**	Atm there's one issue. draw_rt draws just a rendered picture without
		**		any effects. So it should get smth like flags to draw specific
		**		rendered picture.
		*/
		draw_all(env);
		draw = 0;
	}
	SDL_DestroyWindow(env->sdl.window);
	kiss_clean(&env->gui->objarr);
	SDL_Quit();
	exit(0);
}

int			main(int argc, char **argv)
{
	t_env *env;

	if (argc == 2 || argc == 3)
	{
		env = (t_env *)malloc(sizeof(t_env));
		init_env(env, argv);
		init_gui(env);
		parse_file(argv[1], env);
		adjust_objects(env);
		draw_gui(env);
		render(env);
		sdl_loop(env);
	}
	ft_putendl(MSG_USAGE);
	exit(0);
}
