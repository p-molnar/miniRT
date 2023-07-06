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

t_vec3	*get_incident_point_norm(t_scn_el *cam, t_coord3 *inc_p, t_closest *obj)
{
	t_vec3	*obj_norm;
	t_mx	*obj_norm_mx;

	obj_norm = NULL;
	if (obj->el->type == F_CYLINDER)
	{
		if (((float) obj->inc_p->z > obj->el->cap[0].pos.z && (float) obj->inc_p->z < obj->el->cap[1].pos.z))
		{
			t_coord3 *cy_inc_p_depth = create_coord(0, 0, obj->inc_p->z);
			obj_norm = create_dir_vec(*cy_inc_p_depth, *obj->inc_p);
		}
		else
		{
			if (cam->pos.z <= obj->inc_p->z)
				obj_norm = create_vec(0, 0, -1);
			else
				obj_norm = create_vec(0, 0, 1);
		}
		obj_norm_mx = coord_to_mx(&obj_norm->dir, 3, 1);
		expand_mx(obj_norm_mx, 4, 1, 1);
		obj_norm_mx = multiply_mx(obj->el->rotation, obj_norm_mx);
		obj_norm = create_vec(obj_norm_mx->m[0], obj_norm_mx->m[1], obj_norm_mx->m[2]);
	}
	else if (obj->el->type == F_SPHERE)
		obj_norm = create_dir_vec(obj->el->pos, *inc_p);
	else if (obj->el->type == F_PLANE)
	{	
		obj_norm = coord_to_vec(obj->el->n_vec->dir);
	}
	normalize(obj_norm);
	return (obj_norm); 
}

t_coord3	*get_incident_point(t_ray *ray, t_closest *obj)
{
	t_coord3	*inc_p;
	t_mx		*inc_p_mx;
	t_mx		*tmp_mx;
	t_vec3		*tmp_vec;	

	if (obj->el->type == F_CYLINDER)
	{
		tmp_mx = coord_to_mx(obj->inc_p, 3, 1);
		expand_mx(tmp_mx, 4, 1, 1);
		inc_p_mx = multiply_mx(obj->el->rotation, tmp_mx);
		free(tmp_mx);
		tmp_mx = multiply_mx(obj->el->translation, inc_p_mx);
		free_mx(inc_p_mx);
		inc_p = create_coord(tmp_mx->m[X], tmp_mx->m[Y], tmp_mx->m[Z]);
		free(tmp_mx);
	}
	else
	{
		tmp_vec = scale(obj->dist, ray->dir);
		inc_p = offset(ray->origin, tmp_vec);
		free(tmp_vec);
	}
	return (inc_p);
}

t_closest	*get_closest_el(t_scn_el **el, t_ray *ray, const long double *range)
{
	t_closest	*closest;
	long double	t;
	int			i;

	closest = malloc(sizeof(t_closest));
	if (!closest)
		return (NULL);
	closest->el = NULL;
	closest->dist = INF;
	closest->inc_p = NULL;
	i = 0;
	while (el && el[i])
	{
		if (el[i]->type == F_SPHERE)
			t = get_sphere_intersections(ray, el[i]);
		else if (el[i]->type == F_CYLINDER)
			t = get_cylinder_intersection(ray, el[i], &closest->inc_p);
		else if (el[i]->type == F_PLANE)
			t = get_plane_intersection(ray, el[i]);
		if (is_in_range_f(t, range[MIN], range[MAX]) && t < closest->dist)
		{
			closest->dist = t;
			closest->el = el[i];
		}
		if (is_in_range_f(t, range[MIN], range[MAX]) && t < closest->dist)
		{
			closest->dist = t;
			closest->el = el[i];
		}
		i++;
	}
	return (closest);
}

t_vec3	*get_ray_reflection(t_vec3 *ray, t_vec3 *norm)
{
	long double	ray_dot_norm;
	t_vec3		*scaled_vec;
	t_vec3		*scaled_minus_ray;

	if (!ray || !norm)
		return (NULL);
	ray_dot_norm = 2 * dot(ray, norm);
	scaled_vec = scale(ray_dot_norm, norm);
	scaled_minus_ray = subtract(scaled_vec, ray);
	free(scaled_vec);
	return (scaled_minus_ray);
}
