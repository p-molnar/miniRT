/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer_util.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 15:55:08 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/27 17:41:34 by pmolnar       ########   odam.nl         */
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

	if ((float)obj.inc_p.z == (float)obj.el->cap[0].pos.z)
		obj_norm = obj.el->cap[0].n_vec;
	else if ((float)obj.inc_p.z == (float)obj.el->cap[1].pos.z)
		obj_norm = obj.el->cap[1].n_vec;
	else
		obj_norm = create_dir_vec((t_coord3){{0, 0, obj.inc_p.z}}, obj.inc_p);
	obj_norm_mx = multiply_mx(obj.el->rotation, coord_to_mx(obj_norm.dir, 4, 1,
				1));
	return (create_vec(obj_norm_mx.m[X], obj_norm_mx.m[Y], obj_norm_mx.m[Z]));
}

t_vec3	get_obj_norm(t_scn_el cam, t_coord3 inc_p, t_hit_obj obj)
{
	t_vec3		obj_norm;
	long double	agl;

	if (obj.el->type == F_CYLINDER)
		obj_norm = get_cylinder_norm(obj);
	else if (obj.el->type == F_SPHERE)
		obj_norm = create_dir_vec(obj.el->pos, inc_p);
	else if (obj.el->type == F_PLANE)
	{
		agl = get_agl_between(obj.el->n_vec, cam.n_vec);
		obj_norm = coord_to_vec(obj.el->n_vec.dir);
		if (obj_norm.dir.x)
			obj_norm.dir.x = obj_norm.dir.x - (2 * obj_norm.dir.x
					* (agl > M_PI || agl < 0));
		if (obj_norm.dir.y)
			obj_norm.dir.y = obj_norm.dir.y - (2 * obj_norm.dir.y
					* (agl > M_PI || agl < 0));
		if (obj_norm.dir.z)
			obj_norm.dir.z = obj_norm.dir.z - (2 * obj_norm.dir.z
					* (agl > M_PI || agl < 0));
	}
	normalize(&obj_norm);
	return (obj_norm);
}

t_coord3	get_incident_point(t_ray ray, t_hit_obj obj)
{
	t_coord3	inc_p;
	t_mx		inc_p_mx;

	if (obj.el->type == F_CYLINDER)
	{
		inc_p_mx = coord_to_mx(obj.inc_p, 4, 1, 1);
		inc_p_mx = multiply_mx(obj.el->rotation, inc_p_mx);
		inc_p_mx = multiply_mx(obj.el->translation, inc_p_mx);
		inc_p = create_coord(inc_p_mx.m[X], inc_p_mx.m[Y], inc_p_mx.m[Z]);
	}
	else
		inc_p = offset(ray.origin, scale(obj.dist, ray.dir));
	return (inc_p);
}

t_hit_obj	intersect(t_ray ray, t_scn_el **el, t_range range)
{
	t_hit_obj	obj;
	long double	t;
	int			i;

	obj.el = NULL;
	obj.dist = INF;
	i = 0;
	while (el && el[i])
	{
		if (el[i]->type == F_SPHERE)
			t = get_sphere_intersections(ray, el[i]);
		else if (el[i]->type == F_CYLINDER)
			t = get_cylinder_intersection(ray, el[i], &obj.inc_p);
		else if (el[i]->type == F_PLANE)
			t = get_plane_intersection(ray, el[i]);
		if (is_in_range_f(t, range.min, range.max) && t < obj.dist)
		{
			obj.dist = t;
			obj.el = el[i];
		}
		i++;
	}
	return (obj);
}
