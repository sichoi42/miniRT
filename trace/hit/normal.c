#include "trace.h"

void	set_face_normal(t_ray *ray, t_hit_record *rec)
{
	// 광선의 방향벡터와 교점에서의 법선벡터의 내적이 음수라면, 광선은 객체의 앞면에 hit된 것임.
	rec->front_face = (vdot(ray->dir, rec->normal) < 0);
	// 카메라가 객체 안에 있는 형태면 광선의 방향벡터와 교점에서의 법선벡터의 내적이 양수이므로 법선벡터를 반대로 뒤집음.
	if (rec->front_face == FALSE)
		rec->normal = vflip(rec->normal);
}
