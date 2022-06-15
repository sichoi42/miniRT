/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sichoi <sichoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:55:35 by sichoi            #+#    #+#             */
/*   Updated: 2022/06/15 23:54:08 by sichoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "structures.h"
# include "parsing.h"
# include "scene.h"
# include "mlx.h"

t_obj	*adding_objects(t_in_object *in_obj, t_obj **light);
void	add_sphere(t_obj **objs, t_in_object *in_obj);
void	add_plane(t_obj **objs, t_in_object *in_obj);
void	add_cylinder(t_obj **objs, t_in_object *in_obj);
void	add_cone(t_obj **objs, t_in_object *in_obj);
void	add_light(t_obj **objs, t_in_object *in_obj);
void	init_scene(t_scene *scene, t_in_object *in_obj);
void	init_mlx(t_mlx *mlx, t_scene *scene);

#endif
