/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sichoi <sichoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:42:46 by sichoi            #+#    #+#             */
/*   Updated: 2022/06/16 21:22:49 by sichoi           ###   ########.fr       */
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
	*v = vunit(vcross(n, vec3(1, 0, 0)));
	if (is_same_vec(*v, vec3(0, 0, 0)))
		*v = vunit(vcross(n, vec3(0, 0, 1)));
	*u = vunit(vcross(*v, n));
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
		rec->u_vec.x * rec->p.x + rec->v_vec.x * rec->p.y + rec->normal.x * rec->p.z,
		rec->u_vec.y * rec->p.x + rec->v_vec.y * rec->p.y + rec->normal.y * rec->p.z,
		rec->u_vec.z * rec->p.x + rec->v_vec.z * rec->p.y + rec->normal.z * rec->p.z
		));
}

void	bump_mapping(t_hit_record *rec)
{
	t_obj_type	type;
	void		*obj;
	t_bumpmap	*bmp;

	type = rec->obj->type;
	if (type == SP)
	{
		obj = rec->obj->element;
		bmp = ((t_sphere *)obj)->bumpmap;
	}
	else if (type == PL)
	{
		obj = rec->obj->element;
		bmp = ((t_plane *)obj)->bumpmap;
	}
	else if (type == CY)
	{
		obj = rec->obj->element;
		bmp = ((t_cylinder *)obj)->bumpmap;
	}
	else
	{
		obj = rec->obj->element;
		bmp = ((t_sphere *)obj)->bumpmap;
	}
	rec->albedo = mapping_texture_img(rec->u, rec->v, bmp->texture_img);
	rec->normal = mapping_bump_img(rec, bmp->bump_img);
}

void	apply_texture(t_hit_record *rec)
{
	if (rec->texture == CHECKERBOARD)
		bump_mapping(rec);
		// checkerboard(rec);
	// else if (rec->texture == BUMP_MAP)
	// 	bump_mapping(rec);
}
