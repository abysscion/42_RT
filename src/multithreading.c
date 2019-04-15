/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:49:07 by cschuste          #+#    #+#             */
/*   Updated: 2019/04/15 15:15:16 by cschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	void	check_flags(t_env *env)
{
	env->flags.aa ? anti_aliasing(env) : NULL;
	env->flags.blur ? blur(env) : NULL;
	env->flags.sepia ? sepia(env) : NULL;
	env->flags.need_render = 0;
}

static	void	create_image(t_env *e, SDL_Thread **thread, t_env *copy)
{
	int i;
	int j;
	int raw;

	i = -1;
	while (++i < THREADS)
	{
		SDL_WaitThread(thread[i], NULL);
		raw = copy[i].quarter;
		while (raw < WIN_H)
		{
			j = -1;
			while (++j < WIN_W)
				e->sdl.image[j + raw * WIN_W] = copy[i].sdl.image[j +
					raw * WIN_W];
			raw += THREADS;
		}
	}
}

void			create_and_run(t_env *e)
{
	t_env		copy[THREADS];
	SDL_Thread	**thread;
	int			i;

	i = -1;
	while (++i < THREADS)
	{
		ft_memmove(&(copy[i]), e, sizeof(t_env));
		copy[i].quarter = i;
	}
	thread = (SDL_Thread **)malloc(sizeof(SDL_Thread *) * THREADS);
	i = -1;
	while (++i < THREADS)
		thread[i] = SDL_CreateThread(render, "abc", (void *)&copy[i]);
	i = -1;
	create_image(e, thread, &copy[0]);
}

void			check_stereo(t_env *e)
{
	if (e->flags.stereo == 0)
		create_and_run(e);
	else
		stereoscopy(e);
	check_flags(e);
}
