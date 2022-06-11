/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sichoi <sichoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:36:12 by sichoi            #+#    #+#             */
/*   Updated: 2022/06/11 17:33:40 by sichoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "util.h"
#include "trace.h"

t_bool	cylinder_limit(t_cylinder *cy, t_point3 hit_p, double height)
{
	double	limit;

	limit = sqrt(cy->radius * cy->radius + height * height);
	if (vlength(vminus(hit_p, cy->p)) > limit)
		return (FALSE);
	return (TRUE);
}

double	hit_cylinder_side(t_cylinder *cy, t_ray *ray, t_hit_record *rec)
{
	double		a;
	double		half_b;
	double		c;
	double		discriminant;
	double		sqrt_d;
	double		root;
	t_vec3		po;
	t_point3	h;

	po = vminus(ray->orig, cy->p);
	a = vlength2(vcross(ray->dir, cy->normal));
	half_b = vdot(vcross(ray->dir, cy->normal), vcross(po, cy->normal));
	c = vlength2(vcross(po, cy->normal)) - cy->radius * cy->radius;
	discriminant = half_b * half_b - a * c;
	if (discriminant < EPSILON)
		return (INFINITY);
	sqrt_d = sqrt(discriminant);
	root = (-half_b - sqrt_d) / a;
	if (root < rec->t_min || root > rec->t_max)
	{
		root = (-half_b + sqrt_d) / a;
		if (root < rec->t_min || root > rec->t_max)
			return (INFINITY);
	}
	h = ray_at(ray, root);
	if (vdot(cy->normal, vminus(h, cy->tc)) > 0)
		return (INFINITY);
	if (vdot(cy->normal, vminus(h, cy->bc)) < 0)
		return (INFINITY);
	return (root);
}

double hit_cylinder_cap(t_cylinder *cy, t_ray *ray, t_hit_record *rec)
{
	t_vec3	tv;
	t_vec3	bv;
	double	denom;
	double	tt;
	double	bt;

	denom = vdot(ray->dir, cy->normal);
	if (denom == 0)
		return (INFINITY);
	tv = vminus(cy->tc, ray->orig);
	tt = vdot(tv, cy->normal) / denom;
	if (vlength2(vminus(ray_at(ray, tt), cy->tc)) > cy->radius * cy->radius)
		tt = INFINITY;
	bv = vminus(cy->bc, ray->orig);
	bt = vdot(bv, cy->normal) / denom;
	if (vlength2(vminus(ray_at(ray, bt), cy->bc)) > cy->radius * cy->radius)
		bt = INFINITY;
	if (tt < rec->t_min || tt > rec->t_max)
		tt = INFINITY;
	if (bt < rec->t_min || bt > rec->t_max)
		bt = INFINITY;
	if (tt < bt)
		return (tt);
	return (bt);
}

t_bool	hit_cylinder(t_obj *obj, t_ray *ray, t_hit_record * rec)
{
	t_cylinder	*cy;
	double		side_t;
	double		cap_t;
	t_vec3		ph;

	cy = (t_cylinder *)obj->element;
	side_t = hit_cylinder_side(cy, ray, rec);
	cap_t = hit_cylinder_cap(cy, ray, rec);
	if (side_t == INFINITY && cap_t == INFINITY)
		return (FALSE);
	if (side_t < cap_t)
	{
		rec->t = side_t;
		rec->p = ray_at(ray, side_t);
		ph = vminus(rec->p, cy->p);
		rec->normal = vunit(vminus(ph, vmult(cy->normal, vdot(cy->normal, ph))));
	}
	else
	{
		rec->t = cap_t;
		rec->p = ray_at(ray, cap_t);
		rec->normal = cy->normal;
	}
	set_face_normal(ray, rec);
	return (TRUE);
}
