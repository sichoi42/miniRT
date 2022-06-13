#include "scene.h"
#include "parsing.h"

t_camera	camera(t_canvas *canvas, t_in_camera *in_cam)
{
	t_camera	cam;
	double		viewport_height;
	t_vec3		v_up;
	double		theta;
	double		h;

	cam.dir = in_cam->org_vec;
	v_up = vec3(0, 1, 0);
	if (cam.dir.x == 0.0 && cam.dir.y != 0.0 && cam.dir.z == 0)
		v_up = vec3(0, 0, -1);
	theta = degree_to_radian(in_cam->fov);
	h = tan(theta / 2.0);
	viewport_height = 2.0 * h;
	cam.viewport_h = viewport_height;
	cam.viewport_w = viewport_height * canvas->aspect_ratio;
	cam.orig = in_cam->org;
	cam.w = vunit(vflip(cam.dir));
	cam.u = vunit(vcross(v_up, cam.w));
	cam.v = vcross(cam.w, cam.u);
	cam.horizontal = vmult(cam.u, cam.viewport_w);
	cam.vertical = vmult(cam.v, cam.viewport_h);
	// 왼쪽 아래 코너점 좌표, origin - horizontal / 2 - vertical / 2 - vec3(0,0,focal_length)
	cam.left_bottom = vminus(vminus(vminus(cam.orig, vdivide(cam.horizontal, 2)), vdivide(cam.vertical, 2)), cam.w);
	return (cam);
}
