/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer_util.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 15:55:08 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/31 12:23:02 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>

t_vec3	get_cylinder_norm(t_hit_obj obj)
{
	t_vec3	obj_norm;
	t_mx	obj_norm_mx;

	if ((float)obj.inc_p_raw.z == (float)obj.attr->cap[0].pos.z)
		obj_norm = obj.attr->cap[0].n_vec;
	else if ((float)obj.inc_p_raw.z == (float)obj.attr->cap[1].pos.z)
		obj_norm = obj.attr->cap[1].n_vec;
	else
		obj_norm = create_dir_vec((t_coord3){{0, 0, obj.inc_p_raw.z}},
				obj.inc_p_raw);
	obj_norm_mx = multiply_mx(obj.attr->rotation, coord_to_mx(obj_norm.dir, 4,
				1, 1));
	return (create_vec(obj_norm_mx.m[X], obj_norm_mx.m[Y], obj_norm_mx.m[Z]));
}

void	get_surface_norm(t_scn_el cam, t_hit_obj *hit_obj)
{
	t_vec3		obj_norm;
	long double	agl;

	if (hit_obj->attr->type == F_CYLINDER)
		obj_norm = get_cylinder_norm(*hit_obj);
	else if (hit_obj->attr->type == F_SPHERE)
		obj_norm = create_dir_vec(hit_obj->attr->pos, hit_obj->inc_p);
	else if (hit_obj->attr->type == F_PLANE)
	{
		agl = get_agl_between(hit_obj->attr->n_vec, cam.n_vec);
		obj_norm = coord_to_vec(hit_obj->attr->n_vec.dir);
		if (obj_norm.dir.x)
			obj_norm.dir.x = obj_norm.dir.x - (2 * obj_norm.dir.x * (agl > M_PI
						|| agl < 0));
		if (obj_norm.dir.y)
			obj_norm.dir.y = obj_norm.dir.y - (2 * obj_norm.dir.y * (agl > M_PI
						|| agl < 0));
		if (obj_norm.dir.z)
			obj_norm.dir.z = obj_norm.dir.z - (2 * obj_norm.dir.z * (agl > M_PI
						|| agl < 0));
	}
	normalize(&obj_norm);
	ft_memcpy(&hit_obj->norm, &obj_norm, sizeof(t_vec3));
}

void	get_incident_point(t_ray ray, t_hit_obj *hit_obj)
{
	t_mx		inc_p_mx;
	t_coord3	inc_p;

	if (hit_obj->attr->type == F_CYLINDER)
	{
		inc_p_mx = coord_to_mx(hit_obj->inc_p_raw, 4, 1, 1);
		inc_p_mx = multiply_mx(hit_obj->attr->rotation, inc_p_mx);
		inc_p_mx = multiply_mx(hit_obj->attr->translation, inc_p_mx);
		inc_p = create_coord(inc_p_mx.m[X], inc_p_mx.m[Y], inc_p_mx.m[Z]);
	}
	else
		inc_p = offset(ray.origin, scale(hit_obj->dist, ray.dir));
	ft_memcpy(&hit_obj->inc_p, &inc_p, sizeof(t_coord3));
}
