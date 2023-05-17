/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/28 10:01:12 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/17 12:13:41 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

t_vec3	*get_light_ray(t_vec3 *inc_p, t_scn_el *light, long double *range)
{
	t_vec3	*vec;

	vec = NULL;
	range[0] = 0 + EPS;
	if (light->type == DIR_LIGHT)
	{
		vec = create_vec(NULL, light->coord); // revise!
		range[1] = INF;
	}
	else if (light->type == LIGHT)
	{
		vec = create_vec(inc_p->coord, light->coord);
		range[1] = 1;
	}
	return (vec);
}

long double	get_lighting_intensity(t_data *data, t_scn_el *obj)
{
	long double	intensity;
	t_closest	*shadow;
	t_scn_el	**lights;
	long double	range[RANGE_SIZE];
	int			i;

	intensity = 0;
	lights = get_scn_els(data->scn_el, G_LIGHT);
	i = 0;
	while (lights && lights[i])
	{
		if (lights[i]->type == AMB_LIGHT)
			intensity += lights[i]->intensity;
		else
		{
			data->vec[L] = get_light_ray(data->vec[P], lights[i], range);
			shadow = cast_shadow(data, range);
			if (shadow->el != NULL)
			{
				i++;
				free(shadow);
				continue ;
			}
			long double n_dot_l = dot(data->vec[N], data->vec[L]);
			if (n_dot_l > 0)
				intensity += lights[i]->intensity * n_dot_l / (data->vec[L]->len
						* data->vec[N]->len);
			if (obj->specular != -1)
				intensity += get_specular_lighting(data, lights[i], obj->specular);
			free(shadow);
		}
		i++;
	}
	free(lights);
	return (intensity);
}