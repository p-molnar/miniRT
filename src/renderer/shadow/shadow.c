/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shadow.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 15:44:35 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/18 12:37:56 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdio.h>

t_closest	*cast_shadow(t_data *data, t_ray ray, long double *range)
{
	t_closest	*closest_el;
	
	closest_el = get_closest_el(data->scn_els[ALL_OBJS], ray, range);
	return (closest_el);
}
