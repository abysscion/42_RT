/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:38:08 by eloren-l          #+#    #+#             */
/*   Updated: 2019/03/28 20:53:55 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void parse_object(int fd, t_lst *lst, t_obj *obj)
{
	char	*line;
	char	**split;
	char	**floats;

	lst->type = T_OBJECT;
	get_next_line(fd, &line);
	split = ft_strsplit(line, '\t');
	open_check(fd, &split, &line);
	while (1)
	{
		if (close_check(fd, &split, &line))
			break ;
		floats = ft_strsplit((*split)[2], ' ');
		if (strcmp((*split)[0], "position") == 0)
			obj->offset = (t_v){ft_atod(floats[0]),
				ft_atod(floats[1]), ft_atod(floats[2])};
		if (strcmp((*split)[0], "orientation") == 0)
			obj->rotation = (t_v){ft_atod(floats[0]),
				ft_atod(floats[1]), ft_atod(floats[2])};
		if (strcmp((*split)[0], "surface") == 0)
			add_surface(fd, obj);
		free_words(floats);
		parse_next(fd, &split, &line);
	}
}

static void	parse_light(int fd, t_lst *lst, t_light *light)
{
	char	*line;
	char	**split;
	char	**floats;

	get_next_line(fd, &line);
	split = ft_strsplit(line, '\t');
	open_check(fd, &split, &line);
	while (1)
	{
		if (close_check(fd, &split, &line))
			break ;
		floats = ft_strsplit((*split)[2], ' ');
		if (strcmp((*split)[0], "position") == 0)
			light->position = (t_v){ft_atod(floats[0]),
				ft_atod(floats[1]), ft_atod(floats[2])};
		if (strcmp((*split)[0], "intensity") == 0)
			light->intensity = ft_atod(floats[0]);
		if (strcmp((*split)[0], "type") == 0)
			lst->type = light_type_check(fd, &split, &line);
		free_words(floats);
		if (strcmp((*split)[0], "type"))
			parse_next(fd, &split, &line);
	}
}

static void	parse_cam(int fd, t_env *env)
{
	char	*line;
	char	**split;
	char	**floats;

	get_next_line(fd, &line);
	split = ft_strsplit(line, '\t');
	open_check(fd, &split, &line);
	while (1)
	{
		if (close_check(fd, &split, &line))
			break ;
		floats = ft_strsplit((*split)[2], ' ');
		if (strcmp((*split)[0], "position") == 0)
			env->cam.position = (t_v){ft_atod(floats[0]),
				ft_atod(floats[1]), ft_atod(floats[2])};
		if (strcmp((*split)[0], "orientation") == 0)
			env->cam.rotation = (t_v){ft_atod(floats[0]),
				ft_atod(floats[1]), ft_atod(floats[2])};
		free_words(floats);
		parse_next(fd, &split, &line);
	}
}

static void	select_object(t_env *env, char **params, int fd)
{
	t_lst *current;

	if (ft_strcmp(params[0], "camera") == 0)
		parse_cam(fd, env);
	else if (ft_strcmp(params[0], "light") == 0)
	{
		if (env->lights->type == -2)
			current = env->lights;
		else
			current = list_add(env->lights);
		current->obj = (t_light *)malloc(sizeof(t_light));
		parse_light(params, current, current->obj);
	}
	else if (ft_strcmp(params[0], "object") == 0)
	{	
		if (env->objects->type == -2)
			current = env->objects;
		else
			current = list_add(env->objects);
		current->obj = (t_lst *)malloc(sizeof(t_lst));	
		parse_object(params, current, current->obj);
	}
}

void		parse_file(char *name, t_env *env)
{
	int		fd;
	char	*line;
	char	**split;

	parser_validation(name);
	env->objects = list_create();
	env->lights = list_create();
	fd = open(name, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		split = ft_strsplit(line, '\t');
		select_object(env, split, fd);
		free(line);
	}
}