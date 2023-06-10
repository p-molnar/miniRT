/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shadow.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 15:44:35 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/06/10 15:37:55 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdio.h>

t_closest	*cast_shadow(t_data *data, t_ray *ray, long double *range)
{
	t_closest	*closest_el;
	t_scn_el **scn_els;

	scn_els = data->grp_scn_el[OBJS];
	closest_el = get_closest_el(scn_els, ray, range);
	return (closest_el);
}
