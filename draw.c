#include "init.h"
#include "trace.h"
#include "print.h"

void	draw_loop(t_scene *scene)
{
	int			i;
	int			j;
	double		u;
	double		v;
	t_color3	pixel_color;

	j = 0;
	while (j < scene->canvas.height)
	{
		i = 0;
		while (i < scene->canvas.width)
		{
			u = (double)i / (scene->canvas.width - 1);
			v = (double)j / (scene->canvas.height - 1);
			//ray from camera origin to pixel
			scene->ray = ray_primary(&scene->camera, u, v);
			pixel_color = ray_color(scene);
			ft_mlx_pixel_put(scene, &pixel_color, i, scene->canvas.height - 1 - j);
			++i;
		}
		++j;
	}
}

int	key_exit(int param)
{
	exit(param);
	return (0);
}

int	key_esc(int key)
{
	if (key == ESC)
		key_exit(0);
	return (0);
}

void	draw(t_in_object *in_obj)
{
	t_scene		scene;
	t_mlx		mlx;

	init(&scene, &mlx, in_obj);
	draw_loop(&scene);
	mlx_put_image_to_window(scene.mlx->mlx_ptr, scene.mlx->win_ptr, scene.mlx->img.img, 0, 0);
	mlx_hook(scene.mlx->win_ptr, KEYPRESS, 0, key_esc, NULL);
	mlx_hook(scene.mlx->win_ptr, DESTROY, 0, key_exit, NULL);
	mlx_loop(mlx.mlx_ptr);
}
