/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 10:59:42 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/02 12:20:33 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>

void	add_cylinder_caps(t_scn_el *cylinder)
{
	t_scn_el	*caps;
	t_coord3	cap_std_pos;

	cap_std_pos = (t_coord3){{0, 0, 0}};
	caps = ft_calloc(2, sizeof(t_scn_el));
	caps[0].pos.z = cap_std_pos.z - (cylinder->height / 2);
	caps[0].n_vec = create_vec(cap_std_pos.x, cap_std_pos.y, -1);
	caps[1].pos.z = cap_std_pos.z + (cylinder->height / 2);
	caps[1].n_vec = create_vec(cap_std_pos.x, cap_std_pos.y, 1);
	cylinder->cap = caps;
}

long double	yield_smallest_positive(long double *arr, int arr_size)
{
	int			i;
	long double	smallest;

	smallest = INF;
	i = 0;
	while (i < arr_size)
	{
		if (arr[i] > 0 && arr[i] < smallest)
			smallest = arr[i];
		i++;
	}
	if (smallest == INF)
		smallest = -1;
	return (smallest);
}

bool	get_body_intersections(t_ray ray, t_scn_el *obj, long double z[2],
		long double *intersects)
{
	t_quad_param	param;
	long double		*t;

	param.a = pow(ray.dir.dir.x, 2) + pow(ray.dir.dir.y, 2);
	param.b = 2 * (ray.origin.x * ray.dir.dir.x + ray.origin.y * ray.dir.dir.y);
	param.c = pow(ray.origin.x, 2) + pow(ray.origin.y, 2) - pow(obj->diameter
			/ 2, 2);
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

void	get_cap_intersections(t_ray ray, t_scn_el *obj, long double z[2],
		long double *intersects)
{
	if ((z[0] < obj->cap[0].pos.z && z[1] > obj->cap[0].pos.z)
		|| (z[0] > obj->cap[0].pos.z && z[1] < obj->cap[0].pos.z))
		intersects[0] = (obj->cap[0].pos.z - ray.origin.z) / ray.dir.dir.z;
	if ((z[0] < obj->cap[1].pos.z && z[1] > obj->cap[1].pos.z)
		|| (z[0] > obj->cap[1].pos.z && z[1] < obj->cap[1].pos.z))
		intersects[1] = (obj->cap[1].pos.z - ray.origin.z) / ray.dir.dir.z;
}

long double	get_cylinder_intersection(t_ray ray, t_scn_el *obj_info,
		t_coord3 *inc_p)
{
	long double	z[2];
	long double	intersects[4];
	long double	smallest_positive;
	t_coord3	tmp_coord;
	t_ray		transformed_ray;

	intersects[0] = -1;
	intersects[1] = -1;
	intersects[2] = -1;
	intersects[3] = -1;
	smallest_positive = -1;
	transformed_ray = apply_transformations(ray, obj_info);
	if (get_body_intersections(transformed_ray, obj_info, z, intersects))
	{
		get_cap_intersections(transformed_ray, obj_info, z, &intersects[2]);
		smallest_positive = yield_smallest_positive(intersects, 4);
	}
	if (smallest_positive >= 0.0)
	{
		tmp_coord = offset_pt(transformed_ray.origin,
				scale_vec(smallest_positive, transformed_ray.dir));
		ft_memcpy(inc_p, &tmp_coord, sizeof(t_coord3));
	}
	return (smallest_positive);
}
