/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sichoi <sichoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:42:46 by sichoi            #+#    #+#             */
/*   Updated: 2022/06/17 14:19:13 by sichoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

void	checkerboard(t_hit_record *rec)
{
	t_point3	is_black;

	is_black.x = abs((int)floor(rec->p.x)) & 1;
	is_black.y = abs((int)floor(rec->p.y)) & 1;
	is_black.z = abs((int)floor(rec->p.z)) & 1;
	if ((int)is_black.x ^ (int)is_black.y ^ (int)is_black.z)
		rec->albedo = color3(0, 0, 0);
	else
		rec->albedo = color3(1, 1, 1);
}

void	set_uv_map(t_vec3 n, t_vec3 *u, t_vec3 *v)
{
	t_vec3	v_up;

	if (is_same_vec(n, vec3(0, 1, 0)))
		v_up = vec3(0, 0, 1);
	else if (is_same_vec(n, vec3(0, -1, 0)))
		v_up = vec3(0, 0, -1);
	else
		v_up = vec3(0, 1, 0);
	*u = vunit(vcross(v_up, n));
	*v = vunit(vcross(n, *u));
}

int	rgb_extract(int mlx_color, t_color_mask type)
{
	return ((mlx_color >> type) & 0xFF);
}

t_color3	pixel_to_color3(int mlx_color)
{
	double	r;
	double	g;
	double	b;

	r = (double)rgb_extract(mlx_color, RED) / 256;
	g = (double)rgb_extract(mlx_color, GREEN) / 256;
	b = (double)rgb_extract(mlx_color, BLUE) / 256;
	return (color3(r, g, b));
}

int	xpm_pixel_get(t_xpm_image *img, int x, int y)
{
	char	*dst;

	x = clamp(x, 0, img->width - 1);
	y = clamp(y, 0, img->height - 1);
	dst = img->img.addr + (y * img->img.line_length + x * (img->img.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

t_color3	mapping_texture_img(double u, double v, t_xpm_image *img)
{
	int		int_u;
	int		int_v;
	int		mlx_color;

	int_u = (int)(u * img->width);
	int_v = (int)((1.0 - v) * img->height);
	mlx_color = xpm_pixel_get(img, int_u, int_v);
	return (pixel_to_color3(mlx_color));
}

t_vec3	mapping_bump_img(t_hit_record *rec, t_xpm_image *img)
{
	int		int_u;
	int		int_v;
	int		mlx_color;
	t_vec3	normal_color;

	int_u = (int)(rec->u * img->width);
	int_v = (int)((1.0 - rec->v) * img->height);
	mlx_color = xpm_pixel_get(img, int_u, int_v);
	normal_color = pixel_to_color3(mlx_color);
	normal_color = vminus(vmult(normal_color, 2), vec3(1, 1, 1));
	return (vec3(
		(rec->u_vec.x * normal_color.x) + (rec->v_vec.x * normal_color.y) + (rec->normal.x * normal_color.z),
		(rec->u_vec.y * normal_color.x) + (rec->v_vec.y * normal_color.y) + (rec->normal.y * normal_color.z),
		(rec->u_vec.z * normal_color.x) + (rec->v_vec.z * normal_color.y) + (rec->normal.z * normal_color.z)
		));
}

void	bump_mapping(t_hit_record *rec, t_obj *obj)
{
	t_obj_type	type;
	// void		*obj;
	t_bumpmap	*bmp;

	type = obj->type;
	if (type == SP)
		bmp = ((t_sphere *)obj->element)->bumpmap;
	else if (type == PL)
		bmp = ((t_plane *)obj->element)->bumpmap;
	else if (type == CY)
		bmp = ((t_cylinder *)obj->element)->bumpmap;
	else
		bmp = ((t_cone *)obj->element)->bumpmap;
	rec->albedo = mapping_texture_img(rec->u, rec->v, bmp->texture_img);
	rec->normal = vunit(mapping_bump_img(rec, bmp->bump_img));
	// printf("(%lf, %lf, %lf) %lf\n", rec->normal.x, rec->normal.y, rec->normal.z, vlength(rec->normal));
}

void	hit_color_select(t_hit_record *rec, t_obj *obj)
{
	if (rec->texture == CHECKERBOARD)
		bump_mapping(rec, obj);
	else
		rec->albedo = obj->albedo;
		// checkerboard(rec);
	// else if (rec->texture == BUMP_MAP)
	// 	bump_mapping(rec);
}
