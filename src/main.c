/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:29:07 by cschuste          #+#    #+#             */
/*   Updated: 2019/04/11 10:34:21 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	Called when button is being pressed.
*/

void 			button_event(kiss_button *button, SDL_Event *e, int *draw, int *quit)
{
	if (kiss_button_event(button, e, draw))
	{
		printf("button pressed\n");
		*quit = 1;
	}
}

/*
**	Called when text entry in objects box is being clicked.
*/

static	void	tbx_obj_event(kiss_textbox *tbx, SDL_Event *ev, int *draw, t_env *e)
{
	if (kiss_textbox_event(tbx, ev, draw))
		e->gui->win_info.visible ^= 1;
	*draw = 1;
}

/*
**	Called when checkbox is being clicked.
*/

static	void	sbt_event(kiss_selectbutton *sbt, SDL_Event *ev, int *draw, t_env *e)
{
	int	i;
	int	sum;
	int	last_index;

	i = -1;
	sum = 0;
	last_index = e->gui->eff_num - 1;
	if (kiss_selectbutton_event(sbt, ev, draw))
	{
		if (sbt == (kiss_selectbutton *)&e->gui->sbt_eff_arr[last_index])
			while(++i < last_index)
				e->gui->sbt_eff_arr[i].selected = 0;
		sbt->selected ^= 0;
		i = -1;
		while (++i < last_index)
			if (e->gui->sbt_eff_arr[i].selected == 1)
				++sum;
		e->gui->sbt_eff_arr[last_index].selected = sum > 0 ? 0 : 1;
		e->flags.aa = e->gui->sbt_eff_arr[0].selected == 1 ? 1 : 0;
		e->flags.stereo = e->gui->sbt_eff_arr[1].selected == 1 ? 1 : 0;
		e->flags.sepia = e->gui->sbt_eff_arr[2].selected == 1 ? 1 : 0;
		e->flags.blur = e->gui->sbt_eff_arr[3].selected == 1 ? 1 : 0;
		e->flags.need_render = 1;
	}
	*draw = 1;
}

/*
**	Called when text field on right info box is being clicked.
*/

static	void	ent_event(kiss_entry *ent, SDL_Event *ev, int *draw, t_env *e)
{
	if (kiss_entry_event(ent, ev, draw))
		*draw = 1;
	e->cam.position.x = ft_atoi(&ent->text[0]);
	// e->cam.position.y = ft_atoi(&ent->text[0]);
	// e->cam.position.z = ft_atoi(&ent->text[0]);
}

static	void	sdl_loop(t_env *env)
{
	SDL_Event	event;
	int			quit;
	int			draw;
	int			i;

	quit = 0;
	while (!quit)
	{
		SDL_Delay(10);
		while (SDL_PollEvent(&event) != 0)
		{
			i = -1;
			if ((event.type == SDL_KEYDOWN &&
				event.key.keysym.sym == SDLK_ESCAPE) || event.type == SDL_QUIT)
				quit = 1;
			else if (event.type == SDL_KEYDOWN)
				sdl_key_press_events(&event, env);
			while (++i < env->gui->eff_num)
				sbt_event(&env->gui->sbt_eff_arr[i], &event, &draw, env);
			tbx_obj_event(&env->gui->tbx_obj, &event, &draw, env);
			//	ill fix it later, probly will wrap it in array
			ent_event(&env->gui->ent_pos_x, &event, &draw, env);
			// ent_event(&env->gui->ent_pos_y, &event, &draw, env);
			// ent_event(&env->gui->ent_pos_z, &event, &draw, env);
			// ent_event(&env->gui->ent_rot_x, &event, &draw, env);
			// ent_event(&env->gui->ent_rot_y, &event, &draw, env);
			// ent_event(&env->gui->ent_rot_z, &event, &draw, env);
			//=====================================================
			button_event(&env->gui->bt_arrup, &event, &draw, &quit);
		}
		if (draw == 0)
			continue;
		draw_all(env);
		draw = 0;
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
		init_gui(env);
		parse_file(argv[1], env);
		adjust_objects(env);
		draw_all(env);
		sdl_loop(env);
	}
	ft_putendl(MSG_USAGE);
	exit(0);
}
