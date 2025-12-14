#include "../header/minirt.h"
#include "../minilibx-linux/mlx.h"
#include "../header/event.h"
#include <math.h>

int	mouse_hook(int keycode, int x,int y,t_vars *vars)
{
    double zoom;

    (void)x;
    (void)y;
    zoom = vars->scene->camera.orig.z;
    if (keycode == ZOOM_IN)
	{
        zoom = 5;
        vars->scene->camera = move_camera(vars->scene->camera,zoom,0.0,0.0);
    }
	else if (keycode == ZOOM_OUT)
    {
        zoom = -5;
		vars->scene->camera = move_camera(vars->scene->camera,zoom,0.0,0.0);
    }
    render_scene(vars);
	return (0);
}