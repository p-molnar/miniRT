/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shadow.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 15:44:35 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/06/12 21:55:37 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdio.h>

t_closest	*cast_shadow(t_data *data, t_ray *ray, long double *range)
{
	t_closest	*closest_el;
	t_scn_el **scn_els;

	scn_els = data->scn_els[ALL_OBJS];
	closest_el = get_closest_el(scn_els, ray, range);
	if (closest_el->dist != INF)
		printf("shadow: %Lf\n", closest_el->dist);
	printf("range: %Lf, %Lf\n", range[0], range[1]);
	return (closest_el);
}
