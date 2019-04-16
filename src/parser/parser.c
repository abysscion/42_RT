/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:38:08 by eloren-l          #+#    #+#             */
/*   Updated: 2019/04/16 20:16:46 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parse_object(int fd, t_obj *object, char *line)
{
	char	**split;
	char	**floats;

	get_next_line(fd, &line);
	split = ft_strsplit(line, '\t');
	open_check(fd, &split, &line);
	while (1)
	{
		if (close_check(&split, &line))
			break ;
		if (strcmp(split[0], "surface") == 0)
			add_surface(fd, object);
		if (strcmp(split[0], "surface"))
			floats = ft_strsplit(split[2], ' ');
		if (strcmp(split[0], "position") == 0)
			object->position = (t_v){ft_atod(floats[0]),
				ft_atod(floats[1]), ft_atod(floats[2])};
		if (strcmp(split[0], "rotation") == 0)
			object->rotation = (t_v){ft_atod(floats[0]),
				ft_atod(floats[1]), ft_atod(floats[2])};
		if (strcmp(split[0], "surface"))
			free_words(floats);
		parse_next(fd, &split, &line);
	}
}

static void	parse_light(int fd, t_lst *lst, t_light *light, char *line)
{
	char	**split;
	char	**floats;

	get_next_line(fd, &line);
	split = ft_strsplit(line, '\t');
	open_check(fd, &split, &line);
	while (1)
	{
		if (close_check(&split, &line))
			break ;
		floats = ft_strsplit(split[2], ' ');
		if (strcmp(split[0], "position") == 0)
			light->position = (t_v){ft_atod(floats[0]),
				ft_atod(floats[1]), ft_atod(floats[2])};
		if (strcmp(split[0], "intensity") == 0)
			light->intensity = ft_atod(floats[0]);
		if (strcmp(split[0], "type") == 0)
		{
			lst->type = light_type_check(fd, &split, &line);
			free_words(floats);
			continue;
		}
		free_words(floats);
		parse_next(fd, &split, &line);
	}
}

static void	parse_cam(int fd, t_env *env, char *line)
{
	char	**split;
	char	**floats;

	get_next_line(fd, &line);
	split = ft_strsplit(line, '\t');
	open_check(fd, &split, &line);
	while (1)
	{
		if (close_check(&split, &line))
			break ;
		floats = ft_strsplit(split[2], ' ');
		if (strcmp(split[0], "position") == 0)
			env->cam.position = (t_v){ft_atod(floats[0]),
				ft_atod(floats[1]), ft_atod(floats[2])};
		if (strcmp(split[0], "rotation") == 0)
			env->cam.rotation = (t_v){ft_atod(floats[0]),
				ft_atod(floats[1]), ft_atod(floats[2])};
		free_words(floats);
		parse_next(fd, &split, &line);
	}
}

static void	select_object(t_env *env, char **params, int fd)
{
	t_lst		*current;
	static char	*line;

	if (ft_strcmp(params[0], "camera") == 0)
		parse_cam(fd, env, line);
	else if (ft_strcmp(params[0], "light") == 0)
	{
		if (env->lights->type == -2)
			current = env->lights;
		else
			current = list_add(env->lights);
		current->obj = (t_light *)malloc(sizeof(t_light));
		parse_light(fd, current, current->obj, line);
	}
	else if (ft_strcmp(params[0], "object") == 0)
	{
		if (env->objects->type == -2)
			current = env->objects;
		else
			current = list_add(env->objects);
		current->obj = (t_obj *)malloc(sizeof(t_obj));
		init_object(current->obj);
		current->type = T_OBJECT;
		parse_object(fd, current->obj, line);
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
	close(fd);
}
