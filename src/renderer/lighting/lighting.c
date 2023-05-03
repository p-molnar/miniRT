/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/28 10:01:12 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/03 16:28:44 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>

long double	compute_lighting_intensity(t_data *data, int specular)
{
	long double	intensity;
	t_closest	*shadow;
	t_scn_el	**lights;
	long double	range[RANGE_SIZE];
	int			i;

	intensity = 0;
	range[0] = 0.000001;
	lights = get_scn_els(data->scn_el, G_LIGHT);
	i = 0;
	while (lights && lights[i])
	{
		if (lights[i]->type != AMB_LIGHT)
		{
			if (lights[i]->type == DIR_LIGHT)
				range[1] = INF;
			else if (lights[i]->type == LIGHT)
				range[1] = 1;
			shadow = get_closest_el(data, data->vec[P]->coord, data->vec[L], range);
			if (shadow->el != NULL)
			{
				i++;
				free(shadow);
				continue ;
			}
			intensity += get_specular_lighting(data, lights[i], specular);
			intensity += get_diffuse_lighting(data, lights[i]);
			free(shadow);
		}
		i++;
	}
	free(lights);
	return (intensity);
}
