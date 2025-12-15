#include "header/minirt.h"
#include "minilibx-linux/mlx.h"

t_vars vars_init()
{
    t_vars vars;
    vars.scene = NULL;
    vars.width = 400;
    vars.aspect_ratio = 9.0/16.0;
    vars.height = 300;  
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, vars.width, vars.height, "miniRT");
    vars.image.img = mlx_new_image(vars.mlx, vars.width, vars.height);
    vars.image.addr = mlx_get_data_addr(vars.image.img, &vars.image.bits_per_pixel, &vars.image.line_length, &vars.image.endian);
    vars.x = 0;
    vars.y = 0;
    vars.is_drag = 0;
    return vars;
}