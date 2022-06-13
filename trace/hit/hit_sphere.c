/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sichoi <sichoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:36:24 by sichoi            #+#    #+#             */
/*   Updated: 2022/06/11 18:05:27 by sichoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include "trace.h"

t_bool	hit_sphere(t_obj *obj, t_ray *ray, t_hit_record *rec)
{
	t_vec3		oc; // 구의 중심 벡터.
	t_sphere	*sp;
	t_discrim	d;
	double		root;

	sp = (t_sphere *)obj->element;
	oc = vminus(ray->orig, sp->center);
	d.a = vlength2(ray->dir);
	d.half_b = vdot(oc, ray->dir);
	d.c = vlength2(oc) - sp->radius2;
	d.discriminant = d.half_b * d.half_b - d.a * d.c;
	if (d.discriminant < EPSILON)
		return (FALSE);
	d.sqrt_d = sqrt(d.discriminant);
	root = (-d.half_b - d.sqrt_d) / d.a;
	if (root < rec->t_min || root > rec->t_max)
	{
		root = (-d.half_b + d.sqrt_d) / d.a;
		if (root < rec->t_min || root > rec->t_max)
			return (FALSE);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius);
	rec->albedo = obj->albedo;
	set_face_normal(ray, rec);
	return (TRUE);
}
