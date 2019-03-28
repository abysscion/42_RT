/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_write_surface.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 20:09:40 by eloren-l          #+#    #+#             */
/*   Updated: 2019/03/28 20:55:23 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parse_surface(int fd, t_lst *list, t_surf *surf)
{

}

void		add_surface(int fd, t_obj *obj)
{
	t_lst	*current;

	if (obj->surfaces->type == -2)
		current = obj->surfaces;
	else
		current = list_add(obj->surfaces);
	current->obj = (t_surf *)malloc(sizeof(t_surf));
	parse_surface(fd, current, current->obj);
}