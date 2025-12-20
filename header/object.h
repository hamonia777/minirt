/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwpark <jinwpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 14:16:50 by jinwpark          #+#    #+#             */
/*   Updated: 2025/12/21 01:11:24 by jinwpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "../libft/libft.h"
# include "vector.h"
# include <stdio.h>
# include <stdlib.h>

typedef int					t_bool;
typedef struct s_object		t_object;
typedef struct s_hit_record	t_hit_record;

# define FALSE 0
# define TRUE 1
# define FALSE 0
# define TRUE 1
# define LIGHT_POINT 1
# define EPSILON 1e-6
# define LUMEN 3

typedef enum s_object_type
{
	PLANE,
	CYLINDER,
	SPHERE
}							t_object_type;

typedef struct s_ray
{
	t_point					orig;
	t_vec					dir;
}							t_ray;

typedef struct s_object
{
	t_object_type			type;
	void					*elements;
	struct s_object			*next;
	t_color					albedo;

}							t_object;

typedef struct s_camera
{
	t_point					orig;
	t_vec					dir;
	double					fov;
	double					viewport_h;
	double					viewport_w;
	t_vec					horizontal;
	t_vec					vertical;
	double					focal_len;
	t_point					left_bottom;
}							t_camera;

typedef struct s_light
{
	t_point					orig;
	double					brightness;
	t_color					color;
}							t_light;

typedef struct s_ambient
{
	t_color					color;
	double					ambient;
}							t_ambient;

typedef struct s_plane
{
	t_point					center;
	t_vec					normal;
	t_color					color;
}							t_plane;

typedef struct s_sphere
{
	t_point					center;
	double					radius;
	double					radius2;
	t_color					color;
}							t_sphere;

typedef struct s_cylinder
{
	t_point					center;
	t_vec					n;
	double					diameter;
	double					radius;
	double					radius2;
	double					height;
	t_color					color;
}							t_cylinder;

struct						s_hit_record
{
	t_point					p;
	t_vec					normal;
	double					tmin;
	double					tmax;
	double					t;
	t_bool					front_face;
	t_color					albedo;
};

typedef struct s_scene
{
	t_camera				camera;
	t_light					light;
	t_ambient				ambient;
	t_object				*object;
	t_ray					ray;
	t_hit_record			rec;
	int cam_count;
	int amb_count;
	int light_count;
}							t_scene;

typedef struct s_coeff
{
	double			a;
	double			half_b;
	double			c;
}					t_coeff;

typedef struct s_root_check
{
	t_object		*cy_obj;
	t_ray			*ray;
	t_hit_record	*rec;
	double			root;
}					t_root_check;

typedef struct s_root_calc
{
	t_object	*cy_obj;
	t_ray		*ray;
	t_hit_record	*rec;
	t_coeff		coeff;
} t_root_calc;


t_vec						parse_vec(char *str);
t_color						parse_color(char *split);
double						ft_atod(char *str);
void						free_split(char **split);
t_scene						*read_value(char **argv);
t_ambient					parse_ambient(char **split);
t_camera					parse_camera(char **split);
t_light						parse_light(char **split);
t_sphere					*parse_sphere(char **split);
t_plane						*parse_plane(char **split);
t_cylinder					*parse_cylinder(char **split);
t_object					*new_object(t_object_type type, void *elements);
void						add_object(t_object **obj, t_object *new_obj);
t_vec						parse_unit_vec(char *split);
void	printf_error(char *msg);
int							split_count(char **split);
double						parse_double(char *str);
void						free_element(t_object *obj);
void						free_object_list(t_object *obj);
void						free_scene(t_scene *scene);
#endif
