/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 10:59:42 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/19 12:03:06 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>

void	populate_cylinder_properties(t_scn_el *cap, t_scn_el *cy, char cap_type)
{
	int			is_btm;
	t_coord3	std_pos;

	std_pos = (t_coord3){{0, 0, 0}};
	is_btm = cap_type == 'B';
	if (is_btm)
	{
		cap->pos.z = std_pos.z - (cy->height / 2);
		cap->n_vec = create_vec(std_pos.x, std_pos.y, -1);
	}
	else
	{
		cap->pos.z = std_pos.z + (cy->height / 2);
		cap->n_vec = create_vec(std_pos.x, std_pos.y, -1);
	}
}

void	add_cylinder_caps(t_scn_el *cylinder)
{
	t_scn_el	*caps;

	caps = ft_calloc(2, sizeof(t_scn_el));
	populate_cylinder_properties(&caps[0], cylinder, 'B');
	populate_cylinder_properties(&caps[1], cylinder, 'T');
	cylinder->cap = caps;
}

long double	yield_smallest_positive(long double *arr)
{
	int			i;
	long double	smallest;

	smallest = INF;
	i = 0;
	while (i < 4)
	{
		if (arr[i] > 0 && arr[i] < smallest)
			smallest = arr[i];
		i++;
	}
	if (smallest == INF)
		smallest = -1;
	return (smallest);
}

bool	get_body_intersections(t_ray ray, t_scn_el *obj, long double *z,
		long double *intersects)
{
	t_quad_param	param;
	long double		*t;

	param.a = pow(ray.dir.dir.x, 2) + pow(ray.dir.dir.y, 2);
	param.b = 2 * (ray.origin.x * ray.dir.dir.x + ray.origin.y
			* ray.dir.dir.y);
	param.c = pow(ray.origin.x, 2) + pow(ray.origin.y, 2) - pow(obj->diameter / 2,  2);
	t = quad_eq_solver(param, NULL);
	if (t)
	{
		z[0] = ray.origin.z + t[0] * ray.dir.dir.z;
		z[1] = ray.origin.z + t[1] * ray.dir.dir.z;
		if (z[0] > obj->cap[0].pos.z && z[0] < obj->cap[1].pos.z)
			intersects[0] = t[0];
		if (z[1] > obj->cap[0].pos.z && z[1] < obj->cap[1].pos.z)
			intersects[1] = t[1];
		free(t);
		return (true);
	}
	free(t);
	return (false);
}

void	get_cap_intersections(t_ray ray, t_scn_el *obj, long double *z,
		long double *intersects)
{
	if ((z[0] < obj->cap[0].pos.z && z[1] > obj->cap[0].pos.z)
		|| (z[0] > obj->cap[0].pos.z && z[1] < obj->cap[0].pos.z))
		intersects[0] = (obj->cap[0].pos.z - ray.origin.z) / ray.dir.dir.z;
	if ((z[0] < obj->cap[1].pos.z && z[1] > obj->cap[1].pos.z)
		|| (z[0] > obj->cap[1].pos.z && z[1] < obj->cap[1].pos.z))
		intersects[1] = (obj->cap[1].pos.z - ray.origin.z) / ray.dir.dir.z;
}



long double	get_cylinder_intersection(t_ray ray, t_scn_el *obj_info, t_coord3 *inc_p)
{
	long double	z[2];
	long double	intersects[4] = {-1, -1, -1, -1};
	long double	smallest_positive;
	t_coord3		tmp_coord;
	t_ray		transformed_ray;

	smallest_positive = -1;
	transformed_ray = apply_transformations(ray, obj_info);
	if (get_body_intersections(transformed_ray, obj_info, z, intersects))
	{
		get_cap_intersections(transformed_ray, obj_info, z, &intersects[2]);
		smallest_positive = yield_smallest_positive(intersects);
	}
	tmp_coord = offset(transformed_ray.origin, scale(smallest_positive, transformed_ray.dir));
	ft_memcpy(inc_p, &tmp_coord, sizeof(t_coord3));
	return (smallest_positive);
}
