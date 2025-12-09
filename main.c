#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "header/object.h"
#include "header/minirt.h"
#include "minilibx-linux/mlx.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
void	render_scene(t_vars *vars)
{
	int	i;
    int	j;

	i = 0;
	while (i < vars->height)
	{
		j = 0;
		while (j < vars->width)
		{
			my_mlx_pixel_put(&vars->image, j, i, 0x000000);
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
        printf_error("Parsing Failed or Scene is NULL\n");
    render_scene(&vars); // 점 찍기
    mlx_key_hook(vars.win, key_hook, &vars); // 일단 esc만 구현
    mlx_loop(vars.mlx);    
    // print_scene(scene); //파싱한 값 보는거
    return 0;
}