/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sichoi <sichoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:36:24 by sichoi            #+#    #+#             */
/*   Updated: 2022/06/17 00:45:11 by sichoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include "trace.h"

void	get_sphere_uv(t_hit_record *rec)
{
	double	theta;
	double	phi;

	set_uv_map(rec->normal, &rec->u_vec, &rec->v_vec);
	theta = acos(-1 * rec->normal.y);
	phi = atan2(-1 * rec->normal.z, rec->normal.x) + M_PI;
	rec->u = phi * M_1_PI * 0.5;
	rec->v = theta * M_1_PI;
}

void	cutting_sphere(double *t, t_vec3 h[], t_point3 center)
{
	if (t[0] != INFINITY && vdot(vec3(0, 1, 0), vminus(h[0], center)) < 0)
		t[0] = INFINITY;
	if (t[1] != INFINITY && vdot(vec3(0, 1, 0), vminus(h[1], center)) < 0)
		t[1] = INFINITY;
}

t_bool	hit_sphere(t_obj *obj, t_ray *ray, t_hit_record *rec)
{
	t_vec3		oc; // 구의 중심 벡터.
	t_sphere	*sp;
	t_discrim	d;
	double		root;
	double		t[2];
	t_point3	h[2];

	sp = (t_sphere *)obj->element;
	oc = vminus(ray->orig, sp->center);
	d.a = vlength2(ray->dir);
	d.half_b = vdot(oc, ray->dir);
	d.c = vlength2(oc) - sp->radius2;
	d.discriminant = d.half_b * d.half_b - d.a * d.c;
	if (d.discriminant < EPSILON)
		return (FALSE);
	d.sqrt_d = sqrt(d.discriminant);
	t[0] = (-d.half_b - d.sqrt_d) / d.a;
	t[1] = (-d.half_b + d.sqrt_d) / d.a;
	if (t[0] < rec->t_min || t[0] > rec->t_max)
		t[0] = INFINITY;
	if (t[1] < rec->t_min || t[1] > rec->t_max)
		t[1] = INFINITY;
	if (t[0] == INFINITY && t[1] == INFINITY)
		return (FALSE);
	h[0] = ray_at(ray, t[0]);
	h[1] = ray_at(ray, t[1]);
	if (sp->flag == HALF)
	{
		cutting_sphere(t, h, sp->center);
		if (t[0] == INFINITY && t[1] == INFINITY)
		return (FALSE);
	}
	root = t[0];
	if (t[1] < root)
		root = t[1];
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vunit(vdivide(vminus(rec->p, sp->center), sp->radius));
	// rec->albedo = obj->albedo;
	rec->texture = sp->texture;
	// rec->obj = obj;
	set_face_normal(ray, rec);
	get_sphere_uv(rec);
	hit_color_select(rec, obj);
	return (TRUE);
}
