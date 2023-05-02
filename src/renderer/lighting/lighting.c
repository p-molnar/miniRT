/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/28 10:01:12 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/02 17:22:35 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long double	compute_lighting_intensity(t_data *data, int specular)
{
	long double	intensity;
	t_scn_el	**lights;
	int			i;
	long double	n_dot_l;
	long double	rv_dot_v;

	intensity = 0;
	lights = get_scn_els(data->scn_el, G_LIGHT);
	i = 0;
	while (lights && lights[i])
	{
		if (lights[i]->type == AMB_LIGHT)
			intensity += lights[i]->intensity;
		else
		{
			if (lights[i]->type == DIR_LIGHT)
				data->vec[L] = create_vec(NULL, lights[i]->coord);
			else if (lights[i]->type == LIGHT)
				data->vec[L] = create_vec(data->vec[P]->coord, lights[i]->coord);	
			n_dot_l = dot(data->vec[N], data->vec[L]);
			if (n_dot_l > 0)
				intensity += lights[i]->intensity * n_dot_l / (data->vec[L]->len * data->vec[N]->len);
		}
		if (specular != -1)
		{
			data->vec[Ns] = scale(2 * n_dot_l, data->vec[N]);
			data->vec[Rv] = subtract(data->vec[Ns], data->vec[L]);
			data->vec[V] = scale(-1, data->vec[D]);
			rv_dot_v = dot(data->vec[Rv], data->vec[V]);
			if (rv_dot_v > 0)
				intensity += lights[i]->intensity * pow(rv_dot_v / (data->vec[Rv]->len * data->vec[V]->len), specular);
				
		}
		i++;
	}
	free(lights);
	return (intensity);
}
