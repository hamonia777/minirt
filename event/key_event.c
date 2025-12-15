#include "../header/minirt.h"
#include "../minilibx-linux/mlx.h"
#include <math.h>
#include "../header/event.h"

t_camera update_camera(t_camera camera)
{
    double aspect_ratio;
    double viewport_height;
    double theta;
    t_vec vup, w, u, v;
    
    theta = camera.fov * M_PI / 180.0;
    viewport_height = 2.0 * tan(theta / 2.0);
    aspect_ratio = 4.0 / 3.0;
    vup = vec3(0, 1, 0);
    camera.viewport_h = viewport_height;
    camera.viewport_w = viewport_height * aspect_ratio;	
    w = vunit(vmult(camera.dir, -1));
    u = vunit(vcross(vup, w)); 
    v = vcross(w, u); 
    camera.horizontal = vmult(u, camera.viewport_w);
    camera.vertical = vmult(v, camera.viewport_h);
    camera.left_bottom = vminus(vminus(vminus(camera.orig, 
                                    vdivide(camera.horizontal, 2)),
                                    vdivide(camera.vertical, 2)),
                             vmult(camera.dir, camera.focal_len));
    
    return camera;
}

t_camera move_camera(t_camera camera,double forward, double right, double up)
{
    t_vec vup, w, u, v;
    t_vec movement;
    
    // 카메라의 로컬 좌표축 계산
    vup = vec3(0, 1, 0);
    w = vunit(vmult(camera.dir, -1));  // 뒤 방향
    u = vunit(vcross(vup, w));          // 오른쪽 방향
    v = vcross(w, u);                   // 위 방향
    
    // 이동 벡터 계산: forward * 앞 + right * 오른쪽 + up * 위
    movement = vec3(0, 0, 0);
    movement = vplus(movement, vmult(vmult(w, -1), forward));  // 앞 = -w
    movement = vplus(movement, vmult(u, right));
    movement = vplus(movement, vmult(v, up));
    
    camera.orig = vplus(camera.orig, movement);
    camera = update_camera(camera);
    return camera;
}
int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else if (keycode == KEY_A)
		vars->scene->camera = move_camera(vars->scene->camera,0.0,-3.0,0.0);
	else if (keycode == KEY_D)
		vars->scene->camera = move_camera(vars->scene->camera,0.0,3.0,0.0);
	else if (keycode == KEY_W)
		vars->scene->camera = move_camera(vars->scene->camera,0.0,0.0,3.0);
	else if (keycode == KEY_S)
		vars->scene->camera = move_camera(vars->scene->camera,0.0,0.0,-3.0);						
	render_scene(vars);
	return (0);
}