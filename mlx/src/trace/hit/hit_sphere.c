#include "structures.h"
#include "utils.h"
#include "trace.h"

t_bool	hit_sphere(t_obj *obj, t_ray *ray, t_hit_record *rec)
{
	t_vec3		oc; // 구의 중심 벡터.
	t_sphere	*sp;
	double		a, c;
	double		half_b;
	double		discriminant;
	double		sqrt_d;
	double		root;

	sp = (t_sphere *)obj->element;
	oc = vminus(ray->orig, sp->center);
	a = vlength2(ray->dir);
	half_b = vdot(oc, ray->dir);
	c = vlength2(oc) - sp->radius2;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
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
	rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius);
	rec->albedo = obj->albedo;
	set_face_normal(ray, rec);
	return (TRUE);
}
