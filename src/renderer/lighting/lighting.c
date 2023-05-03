/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lighting.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/28 10:01:12 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/03 10:01:38 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>

long double	compute_lighting_intensity(t_data *data, int specular)
{
	long double	intensity;
	t_scn_el	**lights;
	int			i;

	intensity = 0;
	lights = get_scn_els(data->scn_el, G_LIGHT);
	i = 0;
	while (lights && lights[i])
	{
		intensity += get_diffuse_lighting(data, lights[i]);
		if (lights[i]->type != AMB_LIGHT)
			intensity += get_specular_lighting(data, lights[i], specular);
		i++;
	}
	free(lights);
	return (intensity);
}
