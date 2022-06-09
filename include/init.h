/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sichoi <sichoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:55:35 by sichoi            #+#    #+#             */
/*   Updated: 2022/06/09 15:57:09 by sichoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "structures.h"
# include "parsing.h"
# include "scene.h"
# include "mlx.h"

t_obj	*adding_objects(t_in_object *in_obj, t_obj **light);
void	init_scene(t_scene *scene, t_in_object *in_obj);
void	init_mlx(t_mlx *mlx, t_scene *scene);

#endif
