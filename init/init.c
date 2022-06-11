/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sichoi <sichoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:21:29 by sichoi            #+#    #+#             */
/*   Updated: 2022/06/11 16:34:05 by sichoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

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
	if (in_obj->cy > 0)
	{
		i = -1;
		while (++i < in_obj->cy_size)
		{
			new = object(CY, cylinder(in_obj->cy[i].org, in_obj->cy[i].org_vec, in_obj->cy[i].r, in_obj->cy[i].h), in_obj->cy[i].rgb);
			obj_add(&objs, new);
		}
	}
	// LIGHT
	if (in_obj->l_size > 0)
	{
		i = -1;
		while (++i < in_obj->l_size)
		{
			new = object(POINT_LIGHT, point_light(in_obj->l[i].org, in_obj->l[i].rgb, in_obj->l[i].ratio), color3(0, 0, 0));
			obj_add(light, new);
		}
	}
	return (objs);
}

void	free_in_object(t_in_object *o)
{
	free(o->w);
	free(o->a);
	free(o->c);
	free(o->l);
	free(o->sp);
	free(o->pl);
	free(o->cy);
}

void	init_scene(t_scene *scene, t_in_object *in_obj)
{
	if (in_obj->w == NULL)
		scene->canvas = canvas(DEFAULT_WINDOW_W, DEFAULT_WINDOW_H);
	else
		scene->canvas = canvas(in_obj->w->width, in_obj->w->height);
	scene->ambient = vmult(in_obj->a->rgb, in_obj->a->ratio);
	scene->camera = camera(&scene->canvas, in_obj->c);
	scene->light = NULL;
	scene->objs = adding_objects(in_obj, &scene->light);
	free_in_object(in_obj);
}

void	init_mlx(t_mlx *mlx, t_scene *scene)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, scene->canvas.width, scene->canvas.height, "miniRT");
	mlx->img = mlx_new_image(mlx->mlx_ptr, scene->canvas.width, scene->canvas.height);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	scene->mlx = mlx;
}
