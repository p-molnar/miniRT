/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/28 10:01:12 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/06/12 21:56:02 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

t_vec3	*cast_light_ray(t_coord3 *inc_p, t_scn_el *light_obj, long double *range)
{
	t_vec3	*vec;

	vec = NULL;
	range[0] = 0.0001;
	if (light_obj->type == F_DIR_LIGHT)
	{
		vec = coord_to_vec(light_obj->pos); // revise!
		range[1] = INF;
	}
	else if (light_obj->type == F_POINT_LIGHT)
	{
		vec = create_dir_vec(*inc_p, light_obj->pos);
		range[1] = 1; // vec->len
	}
	normalize(vec);
	return (vec);
}

long double	get_lighting_intensity(t_data *data, t_ray *ray, t_coord3 *inc_p, t_scn_el *obj)
{
	long double	intensity;
	t_closest	*shadow;
	t_scn_el	**lights;
	long double	range[RANGE_SIZE];
	int			i;
	t_ray	secondary_ray;

	intensity = 0;
	lights = data->scn_els[ALL_LIGHTS];
	i = 0;
	while (lights && lights[i])
	{
		if (lights[i]->type == F_AMB_LIGHT)
			intensity += lights[i]->intensity;
		else
		{
			secondary_ray.origin = inc_p;
			secondary_ray.dir = cast_light_ray(inc_p, lights[i], range);
			printf("scnd origin: %Lf, %Lf, %Lf\n", secondary_ray.origin->x, secondary_ray.origin->y, secondary_ray.origin->z);
			printf("scnd ray: %Lf, %Lf, %Lf\n", secondary_ray.dir->dir.x, secondary_ray.dir->dir.y, secondary_ray.dir->dir.z);
			shadow = cast_shadow(data, &secondary_ray, range);
			if (shadow->el != NULL)
			{
				// printf("shadow\n");
				i++;
				free(shadow);
				continue ;
			}
			long double n_dot_l = dot(data->v[NORM], secondary_ray.dir);
			printf("ndotl: %Lf\n", n_dot_l);
			printf(" - - - -- - -- \n");
			if (n_dot_l > 0)
				intensity += lights[i]->intensity * n_dot_l / (secondary_ray.dir->len
						* data->v[NORM]->len);
			if (obj->specular != -1)
				intensity += get_specular_lighting(ray, &secondary_ray, data->v[NORM], lights[i]->intensity, obj->specular);
			// free(shadow);
		}
		i++;
	}
	// free(lights);
	// printf("int: %Lf\n", intensity);
	return (intensity);
}
