/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sichoi <sichoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:36:17 by sichoi            #+#    #+#             */
/*   Updated: 2022/06/15 16:29:31 by sichoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include "trace.h"

t_bool	hit_plane(t_obj *obj, t_ray *ray, t_hit_record *rec)
{
	t_plane	*pl;
	t_vec3	op;
	double	denominator;
	double	numerator;

	double	t;

	pl = (t_plane *)obj->element;
	denominator = vdot(pl->normal, ray->dir);
	op = vminus(pl->p, ray->orig);
	numerator = vdot(op, pl->normal);
	if (fabs(denominator) < EPSILON)
		return (FALSE);
	t = numerator / denominator;
	if (t < rec->t_min || t > rec->t_max)
		return (FALSE);
	rec->t = t;
	rec->normal = vunit(pl->normal);
	rec->p = ray_at(ray, t);
	rec->p = vplus(rec->p, vmult(rec->normal, EPSILON));
	rec->albedo = obj->albedo;
	set_face_normal(ray, rec);
	return (TRUE);
}
