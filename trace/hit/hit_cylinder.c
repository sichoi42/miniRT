/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sichoi <sichoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:36:12 by sichoi            #+#    #+#             */
/*   Updated: 2022/06/17 13:35:28 by sichoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "trace.h"

void	get_cylinder_uv(t_hit_record *rec, t_cylinder *cy)
{
	double	theta;
	double	height;
	t_vec3	ph;

	set_uv_map(cy->normal, &rec->u_vec, &rec->v_vec);
	ph = vminus(rec->p, cy->p);
	theta = atan2(-1 * vdot(ph, rec->v_vec), vdot(ph, rec->u_vec)) + M_PI;
	height = vdot(ph, cy->normal);
	rec->u = theta * M_1_PI * 0.5;
	rec->v = ft_fmod_abs(fmod(height, 1), 1);
}

double	hit_cylinder_side(t_cylinder *cy, t_ray *ray, t_hit_record *rec)
{
	t_discrim	d;
	double		root;
	double		t[2];
	t_vec3		po;
	t_point3	h[2];

	po = vminus(ray->orig, cy->p);
	d.a = vlength2(vcross(ray->dir, cy->normal));
	d.half_b = vdot(vcross(ray->dir, cy->normal), vcross(po, cy->normal));
	d.c = vlength2(vcross(po, cy->normal)) - cy->radius * cy->radius;
	d.discriminant = d.half_b * d.half_b - d.a * d.c;
	if (d.discriminant < EPSILON)
		return (INFINITY);
	d.sqrt_d = sqrt(d.discriminant);
	t[0] = (-d.half_b - d.sqrt_d) / d.a;
	t[1]  = (-d.half_b + d.sqrt_d) / d.a;
	if (t[0] < rec->t_min || t[0] > rec->t_max)
		t[0] = INFINITY;
	if (t[1] < rec->t_min || t[1] > rec->t_max)
		t[1] = INFINITY;
	if (t[0] == INFINITY && t[1] == INFINITY)
		return (INFINITY);
	h[0] = ray_at(ray, t[0]);
	h[1] = ray_at(ray, t[1]);
	if (vdot(cy->normal, vminus(h[0], cy->tc)) > 0)
		t[0] = INFINITY;
	if (vdot(cy->normal, vminus(h[0], cy->bc)) < 0)
		t[0] = INFINITY;
	if (vdot(cy->normal, vminus(h[1], cy->tc)) > 0)
		t[1] = INFINITY;
	if (vdot(cy->normal, vminus(h[1], cy->bc)) < 0)
		t[1] = INFINITY;
	if (t[0] == INFINITY && t[1] == INFINITY)
		return (INFINITY);
	root = t[0];
	if (t[1] < root)
		root = t[1];
	return (root);
}

double hit_cylinder_cap(t_cylinder *cy, t_ray *ray, t_hit_record *rec)
{
	t_vec3	ot;
	t_vec3	ob;
	double	denom;
	double	tt;
	double	bt;

	denom = vdot(ray->dir, cy->normal);
	if (denom == 0)
		return (INFINITY);
	ot = vminus(cy->tc, ray->orig);
	tt = vdot(ot, cy->normal) / denom;
	if (vlength2(vminus(ray_at(ray, tt), cy->tc)) > cy->radius * cy->radius)
		tt = INFINITY;
	ob = vminus(cy->bc, ray->orig);
	bt = vdot(ob, cy->normal) / denom;
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
	cap_t = INFINITY;
	if (cy->flag != CY_NO_CAP)
		cap_t = hit_cylinder_cap(cy, ray, rec);
	if (side_t == INFINITY && cap_t == INFINITY)
		return (FALSE);
	if (side_t < cap_t)
	{
		rec->t = side_t;
		rec->p = ray_at(ray, side_t);
		ph = vminus(rec->p, cy->p);
		rec->normal = vunit(vminus(ph, vmult(cy->normal, vdot(cy->normal, ph))));
		set_face_normal(ray, rec);
		get_cylinder_uv(rec, cy);
	}
	else
	{
		rec->t = cap_t;
		rec->p = ray_at(ray, cap_t);
		rec->normal = cy->normal;
		set_face_normal(ray, rec);
		get_plane_uv(rec);
	}
	// rec->albedo = obj->albedo;
	rec->texture = cy->texture;
	// get_cylinder_uv(rec, cy);
	hit_color_select(rec, obj);
	// rec->obj = obj;
	return (TRUE);
}
