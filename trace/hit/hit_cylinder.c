/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sichoi <sichoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:36:12 by sichoi            #+#    #+#             */
/*   Updated: 2022/06/09 21:41:40 by sichoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "util.h"
#include "trace.h"

t_bool	hit_cylinder_cap(t_obj *obj, t_ray *ray, t_hit_record *rec, double height)
{
	t_cylinder	*cy;
	t_vec3		pc;
	t_vec3		op;
	t_vec3		oc;
	double		root;
	double		len_ray_at_c;

	cy = (t_cylinder *)obj->element;
	pc = vmult(cy->normal, height);
	op = vminus(cy->p, ray->orig);
	oc = vplus(op, pc);
	root = vdot(oc, cy->normal) / vdot(ray->dir, cy->normal);
	len_ray_at_c = vlength(vminus(oc, ray_at(ray, root)));
	if (fabs(len_ray_at_c) > cy->radius)
		return (FALSE);
	if (root < rec->t_min || root > rec->t_max)
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->t_max = rec->t;
	if (height < 0)
		rec->normal = cy->normal;
	else
		rec->normal = vmult(cy->normal, -1);
	// rec->normal = vunit(oc);
	set_face_normal(ray, rec);
	rec->albedo = obj->albedo;
	return (TRUE);
}

t_bool	cylinder_limit(t_cylinder *cy, t_point3 hit_p, double height)
{
	double	limit;

	limit = sqrt(cy->radius * cy->radius + height * height);
	if (vlength(vminus(hit_p, cy->p)) > limit)
		return (FALSE);
	return (TRUE);
}

t_bool	hit_cylinder_side(t_obj *obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;
	double		a;
	double		half_b;
	double		c;
	double		discriminant;
	double		sqrt_d;
	double		root;
	t_bool		in_height_limit;
	t_vec3		po;
	t_vec3		ph;

	cy = (t_cylinder *)obj->element;
	po = vminus(ray->orig, cy->p);
	a = vlength2(vcross(ray->dir, cy->normal));
	half_b = vdot(vcross(ray->dir, cy->normal), vcross(po, cy->normal));
	c = vlength2(vcross(po, cy->normal)) - cy->radius * cy->radius;
	discriminant = half_b * half_b - a * c;
	if (discriminant < EPSILON)
		return (FALSE);
	sqrt_d = sqrt(discriminant);
	root = (-half_b - sqrt_d) / a;
	if (root < rec->t_min || root > rec->t_max)
	{
		root = (-half_b + sqrt_d) / a;
		if (root < rec->t_min || root > rec->t_max)
			return (FALSE);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	in_height_limit = cylinder_limit(cy, rec->p, cy->height / 2);
	if (!in_height_limit)
		return (FALSE);
	ph = vminus(rec->p, cy->p);
	rec->normal = vminus(ph, vmult(cy->normal, vdot(cy->normal, ph)));
	rec->albedo = obj->albedo;
	set_face_normal(ray, rec);
	return (TRUE);
}

t_bool	hit_cylinder(t_obj *obj, t_ray *ray, t_hit_record * rec)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)obj->element;
	if (hit_cylinder_cap(obj, ray, rec, cy->height / 2))
		return (TRUE);
	else if (hit_cylinder_cap(obj, ray, rec, (-cy->height) / 2))
		return (TRUE);
	if (hit_cylinder_side(obj, ray, rec))
		return (TRUE);
	return (FALSE);
}
