/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sichoi <sichoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:42:46 by sichoi            #+#    #+#             */
/*   Updated: 2022/06/15 17:06:03 by sichoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

void	checkerboard(t_hit_record *rec)
{
	int			black;
	int			white;
	t_point3	is_black;

	black = BLACK;
	white = WHITE;
	is_black.x = abs((int)floor(rec->p.x)) & 1;
	is_black.y = abs((int)floor(rec->p.y)) & 1;
	is_black.z = abs((int)floor(rec->p.z)) & 1;
	if ((int)is_black.x ^ (int)is_black.y ^ (int)is_black.z)
		rec->albedo = color3(0, 0, 0);
	else
		rec->albedo = color3(1, 1, 1);
}

void	apply_texture(t_hit_record *rec)
{
	checkerboard(rec);
}
