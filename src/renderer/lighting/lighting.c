/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/28 10:01:12 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/06/08 11:24:25 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

t_vec3	*cast_light_ray(t_coord3 *inc_p, t_coord3 *light, int type, long double *range)
{
	t_vec3	*vec;

	vec = NULL;
	range[0] = 0.0001;
	if (type == F_DIR_LIGHT)
	{
		vec = coord_to_vec(light); // revise!
		range[1] = INF;
	}
	else if (type == F_POINT_LIGHT)
	{
		vec = create_dir_vec(inc_p, light);
		range[1] = vec->len;
	}
	return (get_normal_vec(vec));
}

long double	get_lighting_intensity(t_data *data, t_coord3 *inc_p, t_scn_el *obj)
{
	long double	intensity;
	t_closest	*shadow;
	t_scn_el	**lights;
	long double	range[RANGE_SIZE];
	int			i;

	intensity = 0;
	lights = get_scn_els(data->all_scn_el, G_LIGHTS);
	i = 0;
	while (lights && lights[i])
	{
		if (lights[i]->type == F_AMB_LIGHT)
			intensity += lights[i]->intensity;
		else
		{
			data->v[LIGHT] = cast_light_ray(inc_p, lights[i]->pos, lights[i]->type, range);
			shadow = cast_shadow(data, inc_p, data->v[LIGHT], range);
			if (shadow->el != NULL)
			{
				// printf("el: %i\n", shadow->el->type);
				// printf("n_vec->dir: x=%Lf, y=%Lf, z=%Lf\n",
				// shadow->el->n_vec->dir[0],
				// shadow->el->n_vec->dir[1],
				// shadow->el->n_vec->dir[2]);
				i++;
				free(shadow);
				continue ;
			}
			long double n_dot_l = dot(data->v[NORM], data->v[LIGHT]);
			// printf("agl: %Lf\n", n_dot_l);
			if (n_dot_l > 0)
				intensity += lights[i]->intensity * n_dot_l / (data->v[LIGHT]->len
						* data->v[NORM]->len);
			if (obj->specular > 0)
				intensity += get_specular_lighting(data->v[RAY], data->v[LIGHT], data->v[NORM], lights[i]->intensity, obj->specular);
			// free(shadow);
		}
		i++;
	}
	// free(lights);
	// printf("int: %Lf\n", intensity);
	return (intensity);
}
