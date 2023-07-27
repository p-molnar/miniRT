/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/28 10:01:12 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/27 17:42:28 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>

t_vec3	get_light_ray(t_coord3 inc_p, t_scn_el *light_obj, t_range *range)
{
	t_vec3	vec;

	range->min = 0.0001;
	if (light_obj->type == F_DIR_LIGHT)
	{
		vec = coord_to_vec(light_obj->pos);
		range->max = INF;
	}
	else if (light_obj->type == F_POINT_LIGHT)
	{
		vec = create_dir_vec(inc_p, light_obj->pos);
		range->max = vec.len;
	}
	normalize(&vec);
	return (vec);
}

long double	get_intensity(t_scn_el **objs, t_scn_el *light, t_ray rays[3],
		t_scn_el hit_obj)
{
	t_range		range;
	long double	intensity;
	long double	n_dot_l;

	intensity = 0;
	if (light->type == F_AMB_LIGHT)
		intensity += light->intensity;
	else
	{
		rays[2].origin = rays[1].origin;
		rays[2].dir = get_light_ray(rays[1].origin, light, &range);
		if (intersect(rays[2], objs, range).el == NULL)
		{
			n_dot_l = dot(rays[1].dir, rays[2].dir);
			if (n_dot_l > 0)
				intensity += light->intensity * n_dot_l / (rays[2].dir.len
						* rays[1].dir.len);
			if (hit_obj.specular > 0)
				intensity += get_specular_intensity(rays, light->intensity,
						hit_obj.specular);
		}
	}
	return (intensity);
}

long double	get_lighting_intensity(t_data *data, t_ray ray,
		t_ray reflection_ray, t_scn_el hit_obj)
{
	long double	intensity;
	int			i;
	t_ray		rays[3];

	rays[0] = ray;
	rays[1] = reflection_ray;
	intensity = 0;
	i = 0;
	while (data->scn_els[ALL_LIGHTS] && data->scn_els[ALL_LIGHTS][i])
	{
		intensity += get_intensity(data->scn_els[ALL_OBJS],
				data->scn_els[ALL_LIGHTS][i], rays, hit_obj);
		i++;
	}
	return (intensity);
}
