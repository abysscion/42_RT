/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_write_surface.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 20:09:40 by eloren-l          #+#    #+#             */
/*   Updated: 2019/04/13 17:41:24 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parse_surface(int fd, t_lst *list, t_surf *surf)
{
	char	*line;
	char	**split;

	get_next_line(fd, &line);
	split = ft_strsplit(line, '\t');
	open_check(fd, &split, &line);
	while (1)
	{
		if (close_check(&split, &line))
			break ;
		if (strcmp(split[0], "type") == 0)
		{
			list->type = surface_type_check(fd, &split, &line);
			surf->type = list->type;
			continue;
		}
		if (strcmp(split[0], "texture") == 0)
			surf->texture = IMG_Load(split[2]);
		write_field(fd, &split, &line, surf);
	}
}

static void	init_surface(t_surf *surf)
{
	surf->color = (t_clr){255, 255, 255};
	surf->limits.max_height = +INFINITY;
	surf->limits.min_height = -INFINITY;
	surf->limits.max_width = +INFINITY;
	surf->limits.min_width = -INFINITY;
	surf->orientation = (t_v){0, 0, 0};
	surf->position = (t_v){0, 0, 0};
	surf->orientation_init = (t_v){0, 0, 0};
	surf->position_init = (t_v){0, 0, 0};
	surf->radius = 1;
	surf->reflect = 0;
	surf->specular = 0;
	surf->texture = NULL;
	surf->transp = 0;
	surf->type = 0;
}

void		init_object(t_obj *obj)
{
	obj->surfaces = NULL;
	obj->offset = (t_v){0, 0, 0};
	obj->rotation = (t_v){0, 0, 0};
}

void		add_surface(int fd, t_obj *object)
{
	t_lst	*current;

	if (object->surfaces == NULL)
	{
		object->surfaces = list_create();
		current = object->surfaces;
	}
	else
		current = list_add(object->surfaces);
	current->obj = (t_surf *)malloc(sizeof(t_surf));
	current->type = 0;
	init_surface(current->obj);
	parse_surface(fd, current, current->obj);
}
