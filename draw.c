#include "scene.h"
#include "trace.h"
#include "print.h"
#include "parsing.h"
#include "mlx.h"
#include <stdio.h>

t_obj	*adding_objects(t_in_object *in_obj, t_obj **light)
{
	t_obj	*objs;
	t_obj	*new;
	int		i;

	objs = NULL;
	new = NULL;
	// SPHERE
	if (in_obj->sp_size > 0)
	{
		i = -1;
		while (++i < in_obj->sp_size)
		{
			new = object(SP, sphere(in_obj->sp[i].org, in_obj->sp[i].r), in_obj->sp[i].rgb);
			printf("%lf\n", in_obj->sp[i].r);
			obj_add(&objs, new);
		}
	}
	// PLANE
	if (in_obj->pl_size > 0)
	{
		i = -1;
		while (++i < in_obj->pl_size)
		{
			new = object(PL, plane(in_obj->pl[i].org, in_obj->pl[i].org_vec), in_obj->pl[i].rgb);
			obj_add(&objs, new);
		}
	}
	// CYLINDER
	// if (in_obj->cy > 0)
	// {
	// 	i = -1;
	// 	while (++i < in_obj->cy_size)
	// 	{
	// 		new = object(PL, plane(in_obj->pl[i].org, in_obj->pl[i].org_vec), in_obj->pl[i].rgb);
	// 		obj_add(&objs, new);
	// 	}
	// }
	// obj_add(&objs, object(SP, sphere(point3(-2, 0, -5), 2), color3(0.5, 0, 0)));
	// obj_add(&objs, object(SP, sphere(point3(2, 0, -5), 2), color3(0, 0.5, 0)));
	// obj_add(&objs, object(PL, plane(point3(0, -2, 0), vec3(0, 1, 0)), color3(0, 0.5, 0.5)));

	// LIGHT
	// *light = object(POINT_LIGHT, point_light(point3(-3, 10, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0));
	if (in_obj->l_size > 0)
	{
		i = -1;
		while (++i < in_obj->l_size)
		{
			*light = object(POINT_LIGHT, point_light(in_obj->l->org, in_obj->l->rgb, in_obj->l->ratio), color3(0, 0, 0));
		}
	}
	return (objs);
}

t_scene	*scene_init(t_scene *scene, t_in_object *in_obj)
{
	scene->canvas = canvas(1600, 900);
	scene->ambient = vmult(in_obj->a->rgb, in_obj->a->ratio);
	scene->camera = camera(&scene->canvas, in_obj->c->org);
	// scene->camera = camera(&scene->canvas, point3(0, 0, 0));
	scene->objs = adding_objects(in_obj, &scene->light);

	t_obj *obj;
	obj = scene->objs;
	while (obj)
	{
		if (obj->type == SP)
		{
			// t_point3 center = ((t_sphere *)obj->element)->center;
			// printf("%lf, %lf, %lf\n", center.x, center.y, center.z);
			// printf("%lf\n", ((t_sphere *)obj->element)->radius);
			// printf("--------------\n");
		}
		obj = obj->next;
	}
	// ka = 0.1;
	// scene->ambient = vmult(color3(1, 1, 1), ka);
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

void	draw(t_in_object *in_obj)
{
	int			i, j;
	double		u, v;
	t_color3	pixel_color;
	t_scene		scene;
	t_mlx		mlx;

	scene_init(&scene, in_obj);
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
}
