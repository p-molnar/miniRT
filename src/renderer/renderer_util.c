/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer_util.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 15:55:08 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/06/15 14:38:48by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

t_vec3	get_incident_point_norm(t_scn_el cam, t_coord3 inc_p, t_closest obj)
{
	t_vec3	obj_norm;
	t_mx	obj_norm_mx;
	t_mx	tmp;

	if (obj.el->type == F_CYLINDER)
	{
		if (((float) obj.inc_p.z > obj.el->cap[0].pos.z && (float) obj.inc_p.z < obj.el->cap[1].pos.z))
			obj_norm = create_dir_vec((t_coord3) {{0, 0, obj.inc_p.z}}, obj.inc_p);
		else
		{
			if (cam.pos.z <= obj.inc_p.z)
				obj_norm = create_vec(0, 0, -1);
			else
				obj_norm = create_vec(0, 0, 1);
		}
		tmp = coord_to_mx(obj_norm.dir, 4, 1, 1);
		obj_norm_mx = multiply_mx(obj.el->rotation, tmp);
		obj_norm = create_vec(obj_norm_mx.m[0], obj_norm_mx.m[1], obj_norm_mx.m[2]);
	}
	else if (obj.el->type == F_SPHERE)
		obj_norm = create_dir_vec(obj.el->pos, inc_p);
	else if (obj.el->type == F_PLANE)
		obj_norm = coord_to_vec(obj.el->n_vec.dir);
	normalize(&obj_norm);
	return (obj_norm); 
}

t_coord3	get_incident_point(t_ray ray, t_closest obj)
{
	t_coord3	inc_p;
	// t_mx		inc_p_mx;
	t_mx		tmp_mx;
	t_vec3		tmp_vec;	

	if (obj.el->type == F_CYLINDER)
	{
		tmp_mx = coord_to_mx(obj.inc_p, 4, 1, 1);
		tmp_mx = multiply_mx(obj.el->rotation, tmp_mx);
		tmp_mx = multiply_mx(obj.el->translation, tmp_mx);
		inc_p = create_coord(tmp_mx.m[X], tmp_mx.m[Y], tmp_mx.m[Z]);
	}
	else
	{
		tmp_vec = scale(obj.dist, ray.dir);
		inc_p = offset(ray.origin, tmp_vec);
	}
	return (inc_p);
}

t_closest	get_closest_el(t_scn_el **el, t_ray ray, t_range range)
{
	t_closest	obj;
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
		if (is_in_range_f(t, range.min, range.max) && t < obj.dist)
		{
			obj.dist = t;
			obj.el = el[i];
		}
		i++;
	}
	return (obj);
}

t_vec3	get_reflection_ray(t_vec3 ray, t_vec3 norm)
{
	t_vec3		scaled_vec;
	t_vec3		scaled_minus_ray;

	scaled_vec = scale(2 * dot(ray, norm), norm);
	scaled_minus_ray = subtract(scaled_vec, ray);
	return (scaled_minus_ray);
}
