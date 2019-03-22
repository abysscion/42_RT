/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:38:08 by eloren-l          #+#    #+#             */
/*   Updated: 2019/03/22 17:15:14 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parse_surface(char **params, t_lst *lst, t_surf *surf)
{
	char		**split;

	surf->radius = ft_atod(params[4]);
	surf->specular = ft_atod(params[5]);
	surf->reflect = ft_atod(params[6]);
	surf->transp = ft_atod(params[7]);
	split = ft_strsplit(params[1], ',');
	surf->color = (t_clr){ft_atoi(split[0]),
		ft_atoi(split[1]), ft_atoi(split[2])};
	free_words(split);
	split = ft_strsplit(params[2], ',');
	surf->position = (t_v){ft_atod(split[0]),
		ft_atod(split[1]), ft_atod(split[2])};
	free_words(split);
	split = ft_strsplit(params[3], ',');
	surf->orientation = (t_v){ft_atod(split[0]),
		ft_atod(split[1]), ft_atod(split[2])};
	surf->orientation = vecnorm(surf->orientation);
	free_words(split);
	set_surf_type(params[0], lst);
	if (strcmp(params[8], "none"))
	{
		surf->texture = IMG_Load(params[8]);
		calc_basis(surf);
	}
	else
		surf->texture = NULL;
	free_words(params);
}
static void	parse_light(char **params, t_lst *lst, t_light *light)
{
	char	**split;

	lst->type = ft_atoi(params[3]);
	split = ft_strsplit(params[1], ',');
	light->position = (t_v){ft_atod(split[0]),
		ft_atod(split[1]), ft_atod(split[2])};
	light->intensity = ft_atod(params[2]);
	free_words(split);
	free_words(params);
}

static void	parse_cam(char **params, t_env *env)
{
	char	**split;

	split = ft_strsplit(params[1], ',');
	env->cam.position = (t_v){ft_atod(split[0]),
		ft_atod(split[1]), ft_atod(split[2])};
	free_words(split);
	split = ft_strsplit(params[2], ',');
	env->cam.rotation = (t_v){ft_atod(split[0]),
		ft_atod(split[1]), ft_atod(split[2])};
	free_words(split);
	free(params);
}

static void	select_object(t_env *env, char **params)
{
	t_lst *current;

	if (ft_strcmp(params[0], "camera") == 0)
		parse_cam(params, env);
	else if (ft_strcmp(params[0], "light") == 0)
	{
		if (env->lights->type == -2)
			current = env->lights;
		else
			current = list_add(env->lights);
		current->obj = (t_light *)malloc(sizeof(t_light));

		parse_light(params, current, current->obj);
	}
	else
	{	
		if (env->surfaces->type == -2)
			current = env->surfaces;
		else
			current = list_add(env->surfaces);
		current->obj = (t_surf *)malloc(sizeof(t_surf));	
		parse_surface(params, current, current->obj);
	}
}

void		parse_file(char *name, t_env *env)
{
	int		fd;
	char	*line;
	char	**split;

	parser_validation(name);
	env->surfaces = list_create();
	env->lights = list_create();
	fd = open(name, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		split = ft_strsplit(line, '\t');
		select_object(env, split);
		free(line);
	}
}
