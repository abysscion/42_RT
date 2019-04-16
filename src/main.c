/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:29:07 by cschuste          #+#    #+#             */
/*   Updated: 2019/04/16 19:23:50 by sb_fox           ###   ########.fr       */
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
	{
		if (e->gui->selected_object == (t_cam *)&e->cam)
			e->gui->win_info.visible ^= 1;
		else
		{
			e->gui->selected_object = (t_cam *)&e->cam;
			e->gui->selected_object_type = GUI_SELECTED_TYPE_CAM;
			if (e->gui->win_info.visible == 0)
				e->gui->win_info.visible = 1;
		}
		e->gui->need_update_info = 1;
	*draw = 1;
	}
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
	*draw = 1;
	}
}

/*
**	Called when text field on right info box is being clicked.
*/

static	void	ent_event(kiss_entry *ent, SDL_Event *ev, int *draw,
							t_env *e, double *value)
{
	if (kiss_entry_event(ent, ev, draw))
	{
		*value = atof(&ent->text[0]);
		adjust_objects(e);
		e->gui->need_update_info = 1;
		*draw = 1;
	}
}

t_light	*get_light_pointer_to_light(t_env *e, int index)
{
	t_lst	*tmp;

	tmp = e->lights;
	while (e->lights)
		if (tmp->id == index)
			return ((t_light *)tmp->obj);
		else
			tmp = tmp->next;
	return (NULL);
}

t_lst	*get_lst_pointer_to_light(t_env *e, int index)
{
	t_lst	*tmp;

	tmp = e->lights;
	while (e->lights)
		if (tmp->id == index)
			return (tmp);
		else
			tmp = tmp->next;
	return (NULL);
}

/*
**	Called when combobox is being interacted.
*/

static	void	cbb_event(kiss_combobox *cbb, SDL_Event *ev, int *draw, t_env *e)
{
	t_light	*light;
	int		index;

	if (kiss_combobox_event(cbb, ev, draw))
	{
		index = ft_atoi(&cbb->entry.text[9]);
		light = get_light_pointer_to_light(e, index);
		if (e->gui->selected_object == (t_light *)light)
			e->gui->win_info.visible ^= 1;
		else
		{
			e->gui->selected_object_type = GUI_SELECTED_TYPE_LIGHT;
			e->gui->selected_object = light;
			if (e->gui->win_info.visible == 0)
				e->gui->win_info.visible = 1;
		}
		e->gui->need_update_info = 1;
		*draw = 1;
	}
}

/*
**	Takes int code of axis to return proper pointer to value of selected object.
**	10 = position.x		11 = position.y		12 = position.z
**	20 = rotation.x		21 = rotation.y		22 = rotation.z
*/

double		*get_pointer_to_obj_value(t_env *e, int axis_code)
{
	double	*value;
	void	*ptobj;

	value = NULL;
	ptobj = e->gui->selected_object;
	if (e->gui->selected_object_type == GUI_SELECTED_TYPE_OBJ)
	{
		value = axis_code == 10 ? &(((t_obj *)ptobj)->position.x) : value;
		value = axis_code == 11 ? &(((t_obj *)ptobj)->position.y) : value;
		value = axis_code == 12 ? &(((t_obj *)ptobj)->position.z) : value;
		value = axis_code == 20 ? &(((t_obj *)ptobj)->rotation.x) : value;
		value = axis_code == 21 ? &(((t_obj *)ptobj)->rotation.y) : value;
		value = axis_code == 22 ? &(((t_obj *)ptobj)->rotation.z) : value;
	}
	else if (e->gui->selected_object_type == GUI_SELECTED_TYPE_LIGHT)
	{
		value = axis_code == 10 ? &(((t_light *)ptobj)->position.x) : value;
		value = axis_code == 11 ? &(((t_light *)ptobj)->position.y) : value;
		value = axis_code == 12 ? &(((t_light *)ptobj)->position.z) : value;
	}

	else if (e->gui->selected_object_type == GUI_SELECTED_TYPE_CAM)
	{
		value = axis_code == 10 ? &(((t_cam *)ptobj)->position.x) : value;
		value = axis_code == 11 ? &(((t_cam *)ptobj)->position.y) : value;
		value = axis_code == 12 ? &(((t_cam *)ptobj)->position.z) : value;
		value = axis_code == 20 ? &(((t_cam *)ptobj)->rotation.x) : value;
		value = axis_code == 21 ? &(((t_cam *)ptobj)->rotation.y) : value;
		value = axis_code == 22 ? &(((t_cam *)ptobj)->rotation.z) : value;
	}
	return (value);
}

static	void	sdl_loop(t_env *env)
{
	SDL_Event	event;
	int			quit;
	int			*draw;
	int			i;

	quit = 0;
	draw = &env->gui->need_redraw;
	while (!quit)
	{
		SDL_Delay(10);
		while (SDL_PollEvent(&event) != 0)
		{
			i = -1;
			if ((event.type == SDL_KEYDOWN &&
				event.key.keysym.sym == SDLK_ESCAPE) || event.type == SDL_QUIT)
				quit = 1;
			events_handler(&event, env);
			while (++i < env->gui->eff_num)
				sbt_event(&env->gui->sbt_eff_arr[i], &event, draw, env);
			tbx_obj_event(&env->gui->tbx_obj, &event, draw, env);
			ent_event(&env->gui->ent_pos_x, &event, draw, env,
											get_pointer_to_obj_value(env, 10));
			ent_event(&env->gui->ent_pos_y, &event, draw, env,
											get_pointer_to_obj_value(env, 11));
			ent_event(&env->gui->ent_pos_z, &event, draw, env,
											get_pointer_to_obj_value(env, 12));
			ent_event(&env->gui->ent_rot_x, &event, draw, env,
											get_pointer_to_obj_value(env, 20));
			ent_event(&env->gui->ent_rot_y, &event, draw, env,
											get_pointer_to_obj_value(env, 21));
			ent_event(&env->gui->ent_rot_z, &event, draw, env,
											get_pointer_to_obj_value(env, 22));
			cbb_event(&env->gui->cbb_light, &event, draw, env);
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
