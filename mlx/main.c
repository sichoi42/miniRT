#include "scene.h"
#include "trace.h"
#include "print.h"
#include "mlx.h"

t_scene	*scene_init(void)
{
	t_scene		*scene;
	t_obj		*objs;
	t_obj		*lights;
	double		ka;

	scene = malloc(sizeof(t_scene));
	if (scene == NULL)
		exit(1);
	scene->canvas = canvas(400, 300);
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

void	init_mlx(t_scene *scene)
{
	t_image		image;
	void		*mlx_ptr;
	void		*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, scene->canvas.width, scene->canvas.height, "miniRT");
	image.img = mlx_new_image(mlx_ptr, scene->canvas.width, scene->canvas.height);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian);
	scene->mlx.mlx_ptr = mlx_ptr;
	scene->mlx.win_ptr = win_ptr;
	scene->mlx.image = &image;
}

int	main(void)
{
	int			i, j;
	double		u, v;
	t_color3	pixel_color;
	t_scene		*scene;

	scene = scene_init();
	init_mlx(scene);
	j = scene->canvas.height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < scene->canvas.width)
		{
			u = (double)i / (scene->canvas.width - 1);
			v = (double)j / (scene->canvas.height - 1);
			//ray from camera origin to pixel
			scene->ray = ray_primary(&scene->camera, u, v);
			pixel_color = ray_color(scene);
			ft_mlx_pixel_put(scene, &pixel_color, j, i);
			++i;
		}
		--j;
	}
	mlx_put_image_to_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr, scene->mlx.image->img, 0, 0);
	mlx_loop(scene->mlx.mlx_ptr);
	return (0);
}
