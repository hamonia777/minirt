#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "header/object.h"
#include "header/minirt.h"
#include "minilibx-linux/mlx.h"
#include <math.h>
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

typedef struct s_ray
{
	t_point orig;
	t_vec dir;
} t_ray;

t_ray new_ray(t_camera camera, double u, double v)
{
	t_ray ray;
	t_vec tmp;

	ray.orig = camera.orig;
	tmp = vplus(camera.left_bottom, vec(camera.viewport_width * u, camera.viewport_height * v, 0));
	ray.dir = vminus(tmp,ray.orig);
	ray.dir = vunit(ray.dir);
	return ray;
}

int hit_sphere(t_ray ray, t_sphere *sp)
{
    t_vec oc;
    double a, half_b, c, discriminant, t;
    
    oc = vminus(ray.orig, sp->center);
    a = vlength2(ray.dir);
    half_b = vdot(ray.dir, oc);
    c = vlength2(oc) - (sp->diameter/2.0) * (sp->diameter/2.0);
    discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
        return 0;
    t = (-half_b - sqrt(discriminant)) / a;
    if (t > 0)
        return 1;
    
    return 0;
}

int ray_color(t_vars *vars, t_ray ray)
{
    t_object *obj; 
    int obj_count = 0;

    obj = vars->scene->object;
    
    while (obj)
    {
        obj_count++;
        if (obj->type == SPHERE)
        {
            if (obj->elements != NULL)
            {
                if(hit_sphere(ray, (t_sphere *)obj->elements))
                    return 0xEC0BEE;					
            }
        }
        
        obj = obj->next;
    }
    
    return 0x000000;
}

void	render_scene(t_vars *vars)
{
	int	i;
    int	j;
	t_ray ray;
	double u;
    double v;
	// t_color color;

	i = 0;
	while (i < vars->height)
	{
		j = 0;
		while (j < vars->width)
		{
			u = (double)j / (vars->width - 1);
    		v = (double)i / (vars->height - 1); 
			write(1,"1",1);
			ray = new_ray(vars->scene->camera, u, v);
			// color = ray_color(vars, ray);
			write(1,"2",1);			
			my_mlx_pixel_put(&vars->image, j, i, ray_color(vars, ray));
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->image.img, 0, 0);
}

int main(int argc,char **argv)
{
    t_vars vars;
    vars = vars_init();
    if(argc == 2 && ft_strlen(argv[1]) > 3)
        vars.scene = read_value(argv);
    else
	{
        printf_error("Parsing Failed or Scene is NULL\n");
	}
	render_scene(&vars); // 점 찍기
    mlx_key_hook(vars.win, key_hook, &vars); // 일단 esc만 구현
    mlx_loop(vars.mlx);    
    // print_scene(vars.scene); //파싱한 값 보는거

	return 0;
}