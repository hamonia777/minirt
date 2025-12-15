#include "../header/minirt.h"
#include "../minilibx-linux/mlx.h"
#include "../header/event.h"
#include <math.h>

int mouse_down(int button, int x, int y, t_vars *vars)
{
    double zoom;

    if (button == 1) 
    {
        vars->x = x;
        vars->y = y;        
        vars->is_drag = 1;
        vars->sensitivity = 0;
    }
    zoom = vars->scene->camera.orig.z;
    if (button == ZOOM_IN)
	{
        zoom = 3;
        vars->scene->camera = move_camera(vars->scene->camera,zoom,0.0,0.0);
        render_scene(vars);
    }
	else if (button == ZOOM_OUT)
    {
        zoom = -3;
		vars->scene->camera = move_camera(vars->scene->camera,zoom,0.0,0.0);
        render_scene(vars);
    }
    return (0);
}

int mouse_up(int button, int x, int y, t_vars *vars)
{
    if (button == 1)
    {
        vars->is_drag = 0;
        vars->sensitivity = 0;
    }
    return (0);
}
int mouse_move(int x, int y, t_vars *vars)
{
    if (vars->is_drag == 1 && vars->sensitivity == 5)
    {
        if(vars->x - x > 0)
        {
            vars->x = x;
            vars->scene->camera = rotation_y(vars->scene->camera,1);		
        }
        if(vars->x - x < 0)
        {
            vars->x = x;
    		vars->scene->camera = rotation_y(vars->scene->camera,-1);
        }        
        if(vars->y - y < 0) 
        {
            vars->y = y;
            vars->scene->camera = rotation_x(vars->scene->camera,1);
        }
        else if(vars->y - y > 0)
        {
            vars->y = y;     
    		vars->scene->camera = rotation_x(vars->scene->camera,-1);		            
        }
        vars->sensitivity = 0;
    }
    vars->sensitivity++;    
    render_scene(vars);
    return (0);
}