/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trigonometry.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/26 11:20:13 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/06/09 13:36:49 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt.h>
#include <stdlib.h>

long double	deg_to_rad(long double deg)
{
	return (deg * M_PI / 180);
}

long double	rad_to_deg(long double rad)
{
	return (rad * 180 / M_PI);
}

long double	*get_euler_agls(t_mx *rot_mx)
{
	long double	*agls;
	long double	*m;

	agls = malloc(3 * sizeof(long double));
	if (!agls)
		return (NULL);
	m = rot_mx->m;
	agls[0] =  atan2(m[9], m[10]);
	agls[1] =  atan2(-m[8], sqrt(m[9] * m[9] + m[10] * m[10]));
	agls[2] =  atan2(m[4], m[0]);
	return (agls);
}

long double	get_agl_between(t_vec3 *vec_1, t_vec3 *vec_2)
{
	long double agl;

	if (!vec_1 || !vec_2)
		return (-1);
	agl = dot(vec_1, vec_2) / (vec_1->len * vec_2->len);
	return (acos(agl));
}

long double	get_agl_between_d(t_vec3 *vec_1, t_vec3 *vec_2)
{
	long double	agl;

	agl = get_agl_between(vec_1, vec_2);
	if (agl == -1)
		return (-1);
	return (rad_to_deg(agl));
}
