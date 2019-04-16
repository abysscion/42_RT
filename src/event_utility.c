/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 09:30:02 by sb_fox            #+#    #+#             */
/*   Updated: 2019/04/15 16:39:31 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	void	rotation_keys(int key, t_env *e)
{
	if (key == SDLK_KP_4 || key == SDLK_KP_2 ||
		key == SDLK_KP_6 || key == SDLK_KP_8)
		e->flags.need_render = 1;
	else
		return ;
	if (key == SDLK_KP_4)
		e->cam.rotation.y -= ROT_STEP;
	else if (key == SDLK_KP_6)
		e->cam.rotation.y += ROT_STEP;
	else if (key == SDLK_KP_2)
		e->cam.rotation.x += ROT_STEP;
	else if (key == SDLK_KP_8)
		e->cam.rotation.x -= ROT_STEP;
	e->gui->need_update_info = 1;
	draw_all(e);
}

static	void	movement_keys(int key, t_env *e)
{
	if (key == SDLK_UP || key == SDLK_DOWN || key == SDLK_RIGHT ||
		key == SDLK_LEFT || key == SDLK_RSHIFT || key == SDLK_RCTRL)
		e->flags.need_render = 1;
	else
		return ;
	if (key == SDLK_RSHIFT){
		e->cam.position = vecsum(e->cam.position,
			vec_rotate(e->cam.rotation, (t_v){0, 1, 0}));
		printf("up\n");}
	else if (key == SDLK_RCTRL){
		e->cam.position = vecsub(e->cam.position,
			vec_rotate(e->cam.rotation, (t_v){0, 1, 0}));
			printf("down\n");}
	else if (key == SDLK_LEFT)
	{	e->cam.position = vecsub(e->cam.position,
			vec_rotate(e->cam.rotation, (t_v){1, 0, 0}));
			printf("left\n");}
	else if (key == SDLK_RIGHT) {
		e->cam.position = vecsum(e->cam.position,
			vec_rotate(e->cam.rotation, (t_v){1, 0, 0}));
			printf("right\n");}
	else if (key == SDLK_UP){
		e->cam.position = vecsum(e->cam.position,
			vec_rotate(e->cam.rotation, (t_v){0, 0, 1}));
			printf("forward\n");}
	else if (key == SDLK_DOWN) {
		e->cam.position = vecsub(e->cam.position,
			vec_rotate(e->cam.rotation, (t_v){0, 0, 1}));
			printf("backwards\n");}
	e->gui->need_update_info = 1;
	draw_all(e);
}

void			sdl_key_press_events(SDL_Event *event, t_env *env)
{
	int			key;

	key = event->key.keysym.sym;
	if (key == SDLK_s)
		save_image(env->sdl.image, 0);
	else if (key == SDLK_f)
		printf("Objs: [%d]\nSurfs: [%d]\nLights: [%d]\n",
						numOfObjs(env), numOfSurfs(env), numOfLights(env));
	else if (key == SDLK_r)
	{
		env->cam.position = (t_v) {0, 0, -10};
		env->cam.rotation = (t_v) {0, 0, 0};
		env->flags.need_render = 1;
		env->gui->need_update_info = 1;
		draw_all(env);
	}
	else
	{
		movement_keys(key, env);
		rotation_keys(key, env);
	}
	if (key == SDLK_RETURN)
	{
		env->flags.need_render = 1;
	}
}

/*									temp shit
	// t_lst	*objects;
	// t_lst	*objsurfs;
	// t_surf	*target;

	// objects = env->objects;
	// objsurfs = ((t_obj *) objects->obj)->surfaces;
	// target = (t_surf *) objsurfs->obj;
	// ((t_surf*)((t_lst *)((t_obj *)e->objects->obj)->surfaces)->obj)->color.r -= 50;

	// kiss_array_appendstring(&env->gui->tbx_obj_arr, 0,
	// 			"1st surf green value: ", ft_itoa(target->color.g));

	// kiss_array_assign(&env->gui->tbx_obj_arr, 0, 0,
											// ft_strjoin("", "La cameria"));

	// printf("data [%s]", (char *)kiss_array_data(&env->gui->tbx_obj_arr, 3));
*/
