/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:19:57 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/18 14:21:03 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_vec
{
	double		x;
	double		y;
	double		z;
}				t_vec;

typedef t_vec	t_point;
typedef t_vec	t_color;

t_vec			vec3(double x, double y, double z);
t_point			point3(double x, double y, double z);
t_point			color3(double r, double g, double b);
void			vset(t_vec *vec, double x, double y, double z);
double			vlength2(t_vec vec);
double			vlength(t_vec vec);
t_vec			vplus(t_vec vec, t_vec vec2);
t_vec			vplus_(t_vec vec, double x, double y, double z);
t_vec			vminus(t_vec vec, t_vec vec2);
t_vec			vminus_(t_vec vec, double x, double y, double z);
t_vec			vmult(t_vec vec, double t);
t_vec			vmult_(t_vec vec, t_vec vec2);
t_vec			vdivide(t_vec vec, double t);
double			vdot(t_vec vec, t_vec vec2);
t_vec			vcross(t_vec vec, t_vec vec2);
t_vec			vunit(t_vec vec);
t_vec			vmin(t_vec vec1, t_vec vec2);

#endif
