/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trigonometry.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/26 11:20:13 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/09 18:12:07 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>

long double	deg_to_rad(long double deg)
{
	return (deg * M_PI / 180);
}

long double	get_agl_between(t_vec3 vec_1, t_vec3 vec_2)
{
	long double	agl;

	agl = dot(vec_1, vec_2) / (vec_1.len * vec_2.len);
	return (acos(agl));
}
