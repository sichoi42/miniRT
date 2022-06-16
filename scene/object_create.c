#include "structures.h"
#include "parsing.h"
#include "utils.h"
#include "init.h"
#include <stdlib.h>

t_obj	*object(t_obj_type type, void *element, t_color3 albedo)
{
	t_obj	*new;

	new = malloc(sizeof(t_obj));
	if (new == NULL)
		exit(1);
	new->type = type;
	new->element = element;
	new->albedo = albedo;
	new->next = NULL;
	return (new);
}

t_sphere	*sphere(t_in_sphere *in_sp, void *mlx_ptr)
{
	t_sphere	*sp;

	sp = malloc(sizeof(t_sphere));
	if (sp == NULL)
		exit(1);
	sp->center = in_sp->org;
	sp->radius = in_sp->r;
	sp->radius2 = sp->radius * sp->radius;
	sp->flag = in_sp->flag;
	sp->texture = in_sp->texture;
	sp->bumpmap = malloc(sizeof(t_bumpmap));
	if (sp->bumpmap == NULL)
		exit(1);
	sp->bumpmap->texture_img = get_xpm_img("./rt/block.xpm", mlx_ptr);
	sp->bumpmap->bump_img = get_xpm_img("./rt/block_normal.xpm", mlx_ptr);
	return (sp);
}

t_plane	*plane(t_in_plane *in_pl, void *mlx_ptr)
{
	t_plane	*pl;

	pl = malloc(sizeof(t_plane));
	if (pl == NULL)
		exit(1);
	pl->p = in_pl->org;
	pl->normal = vunit(in_pl->org_vec);
	pl->texture = in_pl->texture;
	pl->bumpmap = malloc(sizeof(t_bumpmap));
	if (pl->bumpmap == NULL)
		exit(1);
	pl->bumpmap->texture_img = get_xpm_img("./rt/block.xpm", mlx_ptr);
	pl->bumpmap->bump_img = get_xpm_img("./rt/block_normal.xpm", mlx_ptr);
	return (pl);
}

t_cylinder	*cylinder(t_in_cylinder *in_cy, void *mlx_ptr)
{
	t_cylinder	*cy;

	cy = malloc(sizeof(t_cylinder));
	if (cy == NULL)
		exit(1);
	cy->p = in_cy->org;
	cy->normal = vunit(in_cy->org_vec);
	cy->radius = in_cy->r;
	cy->height = in_cy->h;
	cy->tc = vplus(cy->p, vmult(cy->normal, cy->height / 2));
	cy->bc = vplus(cy->p, vmult(cy->normal, -(cy->height) / 2));
	cy->flag = in_cy->flag;
	cy->texture = in_cy->texture;
	cy->bumpmap = malloc(sizeof(t_bumpmap));
	if (cy->bumpmap == NULL)
		exit(1);
	cy->bumpmap->texture_img = get_xpm_img("./rt/block.xpm", mlx_ptr);
	cy->bumpmap->bump_img = get_xpm_img("./rt/block_normal.xpm", mlx_ptr);
	return (cy);
}
// p, n, degree, h
t_cone	*cone(t_in_cone *in_co, void *mlx_ptr)
{
	t_cone	*co;

	co = malloc(sizeof(t_cone));
	if (co == NULL)
		exit(1);
	co->a = degree_to_radian(in_co->a);
	co->cos = cos(co->a);
	co->sin = sin(co->a);
	co->cos2 = co->cos * co->cos;
	co->sin2 = 1 - co->cos2;
	co->tan = co->sin / co->cos;
	co->tan2 = co->tan * co->tan;
	co->h = in_co->h;
	co->r = co->h * co->tan;
	co->p = in_co->org;
	co->n = vunit(in_co->org_vec);
	co->flip_n = vflip(co->n);
	co->t = vplus(co->p, vmult(co->n, co->h));
	co->texture = in_co->texture;
	co->bumpmap = malloc(sizeof(t_bumpmap));
	if (co->bumpmap == NULL)
		exit(1);
	co->bumpmap->texture_img = get_xpm_img("./rt/block.xpm", mlx_ptr);
	co->bumpmap->bump_img = get_xpm_img("./rt/block_normal.xpm", mlx_ptr);
	return (co);
}
// orig, color, ratio
t_light	*point_light(t_in_light *in_light)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (light == NULL)
		exit(1);
	light->orig = in_light->org;
	light->light_color = in_light->rgb;
	light->bright_ratio = in_light->ratio;
	return (light);
}
