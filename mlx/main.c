#include "scene.h"
#include "trace.h"
#include "print.h"
#include "mlx.h"

t_scene	*scene_init(t_scene *scene)
{
	t_obj		*objs;
	t_obj		*lights;
	double		ka;

	scene->canvas = canvas(1600, 900);
	scene->camera = camera(&scene->canvas, point3(0, 0, 0));
	objs = NULL;
	obj_add(&objs, object(SP, sphere(point3(-2, 0, -5), 2), color3(0.5, 0, 0)));
	obj_add(&objs, object(SP, sphere(point3(2, 0, -5), 2), color3(0, 0.5, 0)));
	obj_add(&objs, object(PL, plane(point3(0, -2, 0), vec3(0, 1, 0)), color3(0, 0.5, 0.5)));
	// obj_add(&objs, object(SP, sphere(point3(0, -1000, 0), 995), color3(1, 1, 1)));
	scene->objs = objs;
	lights = object(POINT_LIGHT, point_light(point3(-3, 10, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0));
	scene->light = lights;
	ka = 0.1;
	scene->ambient = vmult(color3(1, 1, 1), ka);
	return (scene);
}

void	init_mlx(t_mlx *mlx, t_scene *scene)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, scene->canvas.width, scene->canvas.height, "miniRT");
	mlx->img = mlx_new_image(mlx->mlx_ptr, scene->canvas.width, scene->canvas.height);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	scene->mlx = mlx;
}

int	main(void)
{
	int			i, j;
	double		u, v;
	t_color3	pixel_color;
	t_scene		scene;
	t_mlx		mlx;

	scene_init(&scene);
	init_mlx(&mlx, &scene);
	j = 0;
	while (j < scene.canvas.height)
	{
		i = 0;
		while (i < scene.canvas.width)
		{
			u = (double)i / (scene.canvas.width - 1);
			v = (double)j / (scene.canvas.height - 1);
			//ray from camera origin to pixel
			scene.ray = ray_primary(&scene.camera, u, v);
			pixel_color = ray_color(&scene);
			ft_mlx_pixel_put(&scene, &pixel_color, i, scene.canvas.height - 1 - j);
			++i;
		}
		++j;
	}
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img, 0, 0);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
