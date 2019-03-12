/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:22:32 by eloren-l          #+#    #+#             */
/*   Updated: 2019/03/11 18:06:33 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		check_param_num(char **param, int i, char *name)
{
	int		j;

	j = 0;
	while (*param)
	{
		param++;
		j++;
	}
	if (i == j)
		return ;
	ft_putstr("Wrong ");
	ft_putstr(name);
	ft_putstr(" arguments. Exiting.\n");
	exit(0);
}

void		check_floats(char **param, int i, char *name)
{
	char	**num;
	int		j;

	j = 0;
	while (j < i)
	{
		num = ft_strsplit(param[j++], '.');
		check_param_num(num, 2, name);
		free_words(num);
	}
}

void		free_words(char **words)
{
	int		i;

	i = 0;
	while (words[i])
		free(words[i++]);
	free(words);
}

void		set_surf_type(char *surf, t_lst *lst)
{
	if (ft_strcmp(surf, "sphere") == 0)
		lst->type = T_SPHERE;
	else if (ft_strcmp(surf, "plane") == 0)
		lst->type = T_PLANE;
	else if (ft_strcmp(surf, "cylinder") == 0)
		lst->type = T_CYLINDER;
	else if (ft_strcmp(surf, "cone") == 0)
		lst->type = T_CONE;
}