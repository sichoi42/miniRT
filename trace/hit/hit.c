#include "trace.h"

t_bool		hit_obj(t_obj *obj, t_ray *ray, t_hit_record *rec)
{
	t_bool	hit_result;

	hit_result = FALSE;
	if (obj->type == SP)
		hit_result = hit_sphere(obj, ray, rec);
	else if (obj->type == PL)
		hit_result = hit_plane(obj, ray, rec);
	else if (obj->type == CY)
		hit_result = hit_cylinder(obj, ray, rec);
	return (hit_result);
}

t_bool		hit(t_obj *obj, t_ray *ray, t_hit_record *rec)
{
	t_bool			is_hit;
	t_hit_record	temp_rec;

	temp_rec = *rec; // t_min, t_max 초기화.
	is_hit = FALSE;
	while (obj)
	{
		if (hit_obj(obj, ray, &temp_rec))
		{
			is_hit = TRUE;
			temp_rec.t_max = temp_rec.t;
			*rec = temp_rec;
		}
		obj = obj->next;
	}
	return (is_hit);
}
