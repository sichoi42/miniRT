#include "trace.h"

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	//-(-v + 2 * dot(v, n) * n)
	return (vminus(v, vmult(n, vdot(v, n) * 2)));
}

t_bool	in_shadow(t_obj *obj, t_ray light_ray, double light_len)
{
	t_hit_record	rec;

	rec.t_min = 0;
	rec.t_max = light_len;
	if (hit(obj, &light_ray, &rec))
		return (TRUE);
	return (FALSE);
}

// diffuse를 통해 교점에 도달한 빛의 양 계산.
t_color3	get_point_light(t_scene *scene, t_light *light)
{
	t_color3	diffuse;
	t_vec3		light_dir;
	double		kd; // diffuse의 강도
	t_color3	specular;
	t_vec3		view_dir;
	t_vec3		reflect_dir;
	double		spec;
	double		ksn;
	double		ks;
	double		brightness;
	double		light_len;
	t_ray		light_ray;

	light_dir = vminus(light->orig, scene->rec.p); // 교점에서 광원으로(po vector)
	light_len = vlength(light_dir);
	light_ray = ray(vplus(scene->rec.p, vmult(scene->rec.normal, EPSILON)), light_dir);
	if (in_shadow(scene->objs, light_ray, light_len))
		return (color3(0, 0, 0));
	light_dir = vunit(light_dir);
	kd = fmax(vdot(light_dir, scene->rec.normal), 0.0);
	diffuse = vmult(light->light_color, kd);
	view_dir = vunit(vmult(scene->ray.dir, -1));
	reflect_dir = reflect(vmult(light_dir, -1), scene->rec.normal);
	ksn = 64; // shininess value, 이 값이 작을수록 주변으로 퍼짐.
	ks = 0.5; // specular strength, 이 값이 1에 가까울수록 specular로 인한 효과가 커짐.
	spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
	specular = vmult(light->light_color, ks * spec);
	brightness = light->bright_ratio * LUMEN;
	return (vmult(vplus(diffuse, specular), brightness));
}

t_color3	phong_lighting(t_scene *scene)
{
	t_color3	light_color;
	t_obj		*lights;

	light_color = color3(0, 0, 0);
	lights = scene->light;
	while (lights) // 모든 광원에서 나오는 빛의 diffuse와 specular를 더함.
	{
		if (lights->type == POINT_LIGHT)
			light_color = vplus(light_color, get_point_light(scene, lights->element));
		lights = lights->next;
	}
	light_color = vplus(light_color, scene->ambient);
	// 모든 광원에 의한 빛의 양에 오브젝트의 반사율을 곱하고, 1, 1, 1을 넘으면 1, 1, 1로 반환.
	return (vmin(vmult_(light_color, scene->rec.albedo), color3(1, 1, 1)));
}
