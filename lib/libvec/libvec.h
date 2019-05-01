/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libvec.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschuste <cschuste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 20:38:42 by cschuste          #+#    #+#             */
/*   Updated: 2019/04/17 20:38:43 by cschuste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBVEC_H
# define LIBVEC_H

# include <math.h>

typedef	struct		s_vector
{
	double	x;
	double	y;
	double	z;
}					t_v;

double				vecmult_scal(t_v v1, t_v v2);
double				veclen(t_v v);
t_v					vecmult_num(t_v v, double num);
t_v					vecdiv_num(t_v v, double num);
t_v					vecmult_vec(t_v v1, t_v v2);
t_v					vec_rotate(t_v a, t_v vec);
t_v					vecsum(t_v v1, t_v v2);
t_v					vecsub(t_v v1, t_v v2);
t_v					vecnorm(t_v v);

#endif
