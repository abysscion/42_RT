/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libvec.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 06:45:00 by emayert           #+#    #+#             */
/*   Updated: 2019/03/07 07:00:54 by sb_fox           ###   ########.fr       */
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
