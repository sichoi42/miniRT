#include "trace.h"

t_ray	ray(t_point3 orig, t_vec3 dir)
{
	t_ray	ray;

	ray.orig = orig;
	ray.dir = vunit(dir);
	return (ray);
}

t_point3	ray_at(t_ray *ray, double t)
{
	t_point3	at;

	at = vplus(ray->orig, vmult(ray->dir, t));
	return (at);
}

t_ray	ray_primary(t_camera *cam, double u, double v)
{
	t_ray	ray;

	ray.orig = cam->orig;
	// left_bottom + u * horizontal + v * vertical - origin 의 단위 벡터.
	ray.dir = vunit(vminus(vplus(vplus(cam->left_bottom, vmult(cam->horizontal, u)), vmult(cam->vertical, v)), cam->orig));
	return (ray);
}

t_hit_record	record_init(void)
{
	t_hit_record	rec;

	rec.t_min = EPSILON;
	rec.t_max = INFINITY;
	return (rec);
}

t_color3	ray_color(t_scene *scene)
{
	double			t;

	scene->rec = record_init();
	if (hit(scene->objs, &scene->ray, &scene->rec))
		return (phong_lighting(scene));
		// return (vmult(vplus(scene->rec.normal, color3(1, 1, 1)), 0.5));
	t = 0.5 * (scene->ray.dir.y + 1.0);
	// (1-t) * 흰색 + t * 하늘색
	(void)t;
	return (color3(0, 0, 0));
	// return (vplus(vmult(color3(1, 1, 1), 1.0 - t), vmult(color3(0.5, 0.7, 1.0), t)));
}
