/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sichoi <sichoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 18:28:25 by sichoi            #+#    #+#             */
/*   Updated: 2022/06/13 20:37:28 by sichoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "trace.h"

// double	hit_cone_side(t_cone *co, t_ray *ray, t_hit_record *rec)
// {
// 	t_discrim	d;
// 	t_vec3		po;
// 	double		root;
// 	t_vec3		h;
// 	t_vec3		ph;
// 	t_vec3		to;
// 	t_vec3		pt;
// 	static int	i;

// 	po = vminus(ray->orig, co->p);
// 	co->c1 = vdot(ray->dir, co->n);
// 	co->c2 = vdot(po, co->n);
// 	d.a = vlength2(ray->dir) - co->c1 * co->c1 / co->cos2;
// 	d.half_b = vdot(ray->dir, po) + co->r * co->c1 * co->tan * co->c1 * co->c2 / co->cos2;
// 	d.c = vlength2(po) + 2 * co->r * co->c2 * co->tan - co->c2 * co->c2 / co->cos2 - co->r * co->r;
// 	d.discriminant = d.half_b * d.half_b - d.a * d.c;
// 	if (d.discriminant < EPSILON)
// 		return (INFINITY);
// 	d.sqrt_d = sqrt(d.discriminant);
// 	root = validate_root(d, rec);
// 	if (root == INFINITY)
// 		return (INFINITY);
// 	h = ray_at(ray, root);
// 	ph = vminus(h, co->p);
// 	(void)ph;
// 	(void)po;
// 	(void)pt;
// 	to = vminus(ray->orig, co->t);
// 	pt = vflip(vplus(to, vflip(po)));
// 	if (i == 0)
// 	{
// 		printf("p: %lf %lf %lf\n", co->p.x, co->p.y, co->p.z);
// 		printf("pt: %lf %lf %lf\n", pt.x, pt.y, pt.z);
// 		printf("co->n: %lf %lf %lf\n", co->n.x, co->n.y, co->n.z);
// 		++i;
// 	}
// 	(void)i;
// 	if (vdot(co->n, ph) < 0)
// 	{
// 		// printf("ph: %lf %lf %lf, result: %lf\n", ph.x, ph.y, ph.z, vdot(co->n, ph));
// 		return (INFINITY);
// 	}
// 	if (vdot(co->n, vplus(vminus(ray->orig, pt), vmult(ray->dir, root))) > 0)
// 		return (INFINITY);
// 	// printf("ph_vec: (%lf, %lf, %lf), ph.n: %lf\n", ph.x, ph.y, ph.z, vdot(co->n, ph));
// 	return (root);
// }

double	hit_cone_side(t_cone *co, t_ray *ray, t_hit_record *rec)
{
	t_discrim	d;
	t_vec3		po;
	double		root;
	t_vec3		h;
	t_vec3		ph;
	t_vec3		to;
	t_vec3		pt;
	static int	i;

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
	root = validate_root(d, rec);
	if (root == INFINITY)
		return (INFINITY);
	h = ray_at(ray, root);
	ph = vminus(h, co->p);
	(void)ph;
	(void)po;
	(void)pt;
	pt = vflip(vplus(to, vflip(po)));
	if (i == 0)
	{
		// printf("p: %lf %lf %lf\n", co->p.x, co->p.y, co->p.z);
		// printf("pt: %lf %lf %lf\n", pt.x, pt.y, pt.z);
		// printf("co->n: %lf %lf %lf\n", co->n.x, co->n.y, co->n.z);
		++i;
	}
	(void)i;
	if (vdot(co->n, ph) < 0)
	{
		return (INFINITY);
	}
	if (vdot(co->n, vplus(vminus(ray->orig, pt), vmult(ray->dir, root))) > 0)
		return (INFINITY);
	// printf("ph_vec: (%lf, %lf, %lf), ph.n: %lf\n", ph.x, ph.y, ph.z, vdot(co->n, ph));
	return (root);
}

double	hit_cone_cap(t_cone *co, t_ray *ray, t_hit_record *rec)
{
	t_vec3	ot;
	t_vec3	pt;
	double	denom;
	double	root;

	denom = vdot(ray->dir, co->n);
	if (denom == 0)
		return (INFINITY);
	pt = vminus(co->t, co->p);
	ot = vminus(pt, ray->orig);
	root = vdot(pt, co->n) / denom;
	if (vlength2(vminus(ray_at(ray, root), pt)) > co->r * co->r)
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
	cap_t = INFINITY;
	if (side_t == INFINITY && cap_t == INFINITY)
		return (FALSE);
	if (side_t < cap_t)
	{
		rec->t = side_t;
		rec->p = ray_at(ray, side_t);
		// rec->normal = co->n;
		cone_side_normal(co, &rec);
	}
	else
	{
		rec->t = cap_t;
		rec->p = ray_at(ray, cap_t);
		rec->normal = co->n;
	}
	rec->albedo = obj->albedo;
	return (TRUE);
}
