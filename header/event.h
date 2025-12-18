#ifndef EVENT_H
#define EVENT_H

#define ZOOM_IN 4
#define ZOOM_OUT 5
#define KEY_ESC 65307
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_W 119
#define KEY_Q 113
#define KEY_E 101
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_UP 65362
#define KEY_DOWN 65364
#define LEFT_MOUSE 1
#include "object.h"
#include "minirt.h"

t_camera move_camera(t_camera camera,double forward, double right, double up);
t_camera update_camera(t_camera camera);
t_camera	rotation_x(	t_camera camera, double theta);
t_camera	rotation_y(t_camera camera, double theta);
int mouse_move(int x, int y, t_vars *vars);
int mouse_up(int button, int x, int y, t_vars *vars);
int mouse_down(int button, int x, int y, t_vars *vars);
int close_window(t_vars *vars);
#endif