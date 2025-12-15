#include "../header/minirt.h"
#include "../minilibx-linux/mlx.h"
#include "../header/event.h"
#include <math.h>

int mouse_down(int button, int x, int y, t_vars *vars)
{
    double zoom;

    if (button == LEFT_MOUSE) 
    {
        vars->x = x;
        vars->y = y;        
        vars->is_drag = 1;
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
    if (button == LEFT_MOUSE)
    {
        vars->is_drag = 0;
    }
    return (0);
}
int mouse_move(int x, int y, t_vars *vars)
{
    int dx;
    int dy;
    int camera_changed;

    if(vars->is_drag != 1)
        return 0;
    dx = x - vars->x;
    dy = y - vars->y;
    camera_changed = 0;
    if(abs(dx) >= 3)
    {
        if(dx > 0)
            vars->scene->camera = rotation_y(vars->scene->camera,-0.5);		
        else
            vars->scene->camera = rotation_y(vars->scene->camera,0.5);
        camera_changed = 1;
        vars->x = x;
    }
    if(abs(dy) >= 3)
    {
        if(dy > 0)
            vars->scene->camera = rotation_x(vars->scene->camera,0.5);		
        else
            vars->scene->camera = rotation_x(vars->scene->camera,-0.5);
        camera_changed = 1;
        vars->y = y;
    }
    if(camera_changed)
        render_scene(vars);
    return (0);
}