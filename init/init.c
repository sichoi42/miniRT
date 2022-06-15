/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sichoi <sichoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:21:29 by sichoi            #+#    #+#             */
/*   Updated: 2022/06/16 00:21:41 by sichoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

t_obj	*adding_objects(t_in_object *in_obj, t_obj **light)
{
	t_obj	*objs;

	objs = NULL;
	// SPHERE
	if (in_obj->sp_size > 0)
		add_sphere(&objs, in_obj);
	// PLANE
	if (in_obj->pl_size > 0)
		add_plane(&objs, in_obj);
	// CYLINDER
	if (in_obj->cy_size > 0)
		add_cylinder(&objs, in_obj);
	// CONE
	if (in_obj->co_size > 0)
		add_cone(&objs, in_obj);
	// LIGHT
	if (in_obj->l_size > 0)
		add_light(light, in_obj);
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
	free(o->co);
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
