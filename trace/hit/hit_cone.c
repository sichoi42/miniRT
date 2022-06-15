/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sichoi <sichoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:28:25 by sichoi            #+#    #+#             */
/*   Updated: 2022/06/15 20:10:08 by sichoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "trace.h"

double	hit_cone_side(t_cone *co, t_ray *ray, t_hit_record *rec)
{
	t_discrim	d;
	t_vec3		po;
	double		root;
	double		t[2];
	t_vec3		h[2];
	t_vec3		ph;
	t_vec3		to;
	t_vec3		pt;

	po = vminus(ray->orig, co->p);
	to = vminus(ray->orig, co->t);
	co->c1 = vdot(ray->dir, co->n);
	co->c2 = vdot(to, co->n);
	d.a = vdot(ray->dir, ray->dir) - (co->c1 * co->c1) / co->cos2;
	d.half_b = vdot(ray->dir, to) - (co->c1 * co->c2) / co->cos2;
	d.c = vdot(to, to) - (co->c2 * co->c2) / co->cos2;
	d.discriminant = d.half_b * d.half_b - d.a * d.c;
	if (d.discriminant < EPSILON)
		return (INFINITY);
	d.sqrt_d = sqrt(d.discriminant);
	t[0] = (-d.half_b - d.sqrt_d) / d.a;
	if (t[0] < rec->t_min || t[0] > rec->t_max)
		t[0] = INFINITY;
	t[1] = (-d.half_b + d.sqrt_d) / d.a;
	if (t[1] < rec->t_min || t[1] > rec->t_max)
		t[1] = INFINITY;
	if (t[0] == INFINITY && t[1] == INFINITY)
		return (INFINITY);
	h[0] = ray_at(ray, t[0]);
	ph = vminus(h[0], co->p);
	pt = vflip(vplus(to, vflip(po)));
	if (vdot(co->n, ph) < 0)
		t[0] = INFINITY;
	if (vlength2(ph) > vlength2(pt))
		t[0] = INFINITY;
	h[1] = ray_at(ray, t[1]);
	ph = vminus(h[1], co->p);
	pt = vflip(vplus(to, vflip(po)));
	if (vdot(co->n, ph) < 0)
		t[1] = INFINITY;
	if (vlength2(ph) > vlength2(pt))
		t[1] = INFINITY;
	if (t[0] == INFINITY && t[1] == INFINITY)
		return (INFINITY);
	root = t[0];
	if (t[1] < root)
		root = t[1];
	return (root);
}

double	hit_cone_cap(t_cone *co, t_ray *ray, t_hit_record *rec)
{
	t_vec3		op;
	t_point3	h;
	t_vec3		hp;
	double		root;
	double		denom;

	denom = vdot(ray->dir, co->n);
	if (denom == 0)
		return (INFINITY);
	op = vminus(co->p, ray->orig);
	root = vdot(op, co->n) / denom;
	h = ray_at(ray, root);
	hp = vminus(co->p, h);
	if (vlength2(hp) > co->r * co->r)
		return (INFINITY);
	if (root < rec->t_min || root > rec->t_max)
		return (INFINITY);
	return (root);
}

void	cone_side_normal(t_cone *co, t_hit_record **rec)
{
	t_vec3		th;
	t_point3	q;
	t_vec3		qh;
	t_vec3		qt;
	double		h_prime;
	double		r_prime;

	th = vminus((*rec)->p, co->t);
	h_prime = vlength(th) * co->cos;
	r_prime = vlength(th) * co->sin;
	q = vplus(co->t, vmult(co->flip_n, h_prime));
	qh = vminus((*rec)->p, q);
	// r_prime * qt + h_prime * qh;
	qt = vmult(co->n, h_prime);
	(*rec)->normal = vunit(vplus(vmult(qt, r_prime), vmult(qh, h_prime)));
}

t_bool	hit_cone(t_obj *obj, t_ray *ray, t_hit_record *rec)
{
	t_cone	*co;
	double	side_t;
	double	cap_t;

	co = (t_cone *)obj->element;
	side_t = hit_cone_side(co, ray, rec);
	cap_t = hit_cone_cap(co, ray, rec);
	// cap_t = INFINITY;
	if (side_t == INFINITY && cap_t == INFINITY)
		return (FALSE);
	if (side_t < cap_t)
	{
		rec->t = side_t;
		rec->p = ray_at(ray, side_t);
		cone_side_normal(co, &rec);
	}
	else
	{
		rec->t = cap_t;
		rec->p = ray_at(ray, cap_t);
		rec->normal = co->n;
	}
	set_face_normal(ray, rec);
	rec->albedo = obj->albedo;
	return (TRUE);
}
