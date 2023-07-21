/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/28 10:01:12 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/21 13:31:30 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

t_vec3	cast_light_ray(t_coord3 inc_p, t_scn_el *light_obj, t_range *range)
{
	t_vec3	vec;

	range->min = 0.0001;
	if (light_obj->type == F_DIR_LIGHT)
	{
		vec = coord_to_vec(light_obj->pos); // revise!
		range->max = INF;
	}
	else if (light_obj->type == F_POINT_LIGHT)
	{
		vec = create_dir_vec(inc_p, light_obj->pos);
		range->max = vec.len; // was 1
	}
	normalize(&vec);
	return (vec);
}

long double	get_lighting_intensity(t_data *data, t_ray ray, t_ray reflection_ray, t_scn_el *obj)
{
	long double	intensity;
	t_closest	*shadow;
	t_range		range;
	int			i;
	t_ray	secondary_ray;

	intensity = 0;
	i = 0;
	while (data->scn_els[ALL_LIGHTS] && data->scn_els[ALL_LIGHTS][i])
	{
		if (data->scn_els[ALL_LIGHTS][i]->type == F_AMB_LIGHT)
			intensity += data->scn_els[ALL_LIGHTS][i]->intensity;
		else
		{
			secondary_ray.origin = reflection_ray.origin;
			secondary_ray.dir = cast_light_ray(reflection_ray.origin, data->scn_els[ALL_LIGHTS][i], &range);
			shadow = cast_shadow(data, secondary_ray, range);
			if (shadow && shadow->el != NULL)
			{
				free(shadow);
				i++;
				continue ;
			}
			long double n_dot_l = dot(reflection_ray.dir, secondary_ray.dir);
			if (n_dot_l > 0)
				intensity += data->scn_els[ALL_LIGHTS][i]->intensity * n_dot_l / (secondary_ray.dir.len
						* reflection_ray.dir.len);
			if (obj->specular != -1)
				intensity += get_specular_lighting(ray, secondary_ray, reflection_ray.dir, data->scn_els[ALL_LIGHTS][i]->intensity, obj->specular);	
			free(shadow);
		}
		i++;
	}
	return (intensity);
}
