#include "../header/minirt.h"
#include "../minilibx-linux/mlx.h"
#include "../header/event.h"
#include <math.h>

t_camera	rotation_x(	t_camera camera, double theta)
{
	double	radian;
	t_vec old_dir;

	radian = theta * M_PI / 180;
	old_dir = camera.dir;
	camera.dir.x = old_dir.x;
	camera.dir.y = (old_dir.y * cos(radian) - old_dir.z * sin(radian));
	camera.dir.z = (old_dir.y * sin(radian) + old_dir.z * cos(radian));
	camera.dir = vunit(camera.dir);	
	camera = update_camera(camera);
	return camera;
}
t_camera	rotation_y(t_camera camera, double theta)
{
	double	radian;
	t_vec old_dir;

	radian = theta * M_PI / 180;
	old_dir = camera.dir;
	camera.dir.x = (old_dir.x * cos(radian) + old_dir.z * sin(radian));
	camera.dir.y = old_dir.y;
	camera.dir.z = -old_dir.x * sin(radian) + old_dir.z * cos(radian);
	camera.dir = vunit(camera.dir);
	camera = update_camera(camera);
	return camera;
}

void	rotation_z(t_vec *pos, double theta)
{
	double	radian;
	int		temp_x;
	int		temp_y;

	radian = theta * M_PI / 180;
	temp_x = pos->x;
	temp_y = pos->y;
	pos->x = (temp_x * cos(radian) - temp_y * sin(radian));
	pos->y = (temp_x * sin(radian) + temp_y * cos(radian));
	pos->z = pos->z;
}