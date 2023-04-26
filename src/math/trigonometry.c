/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trigonometry.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/26 11:20:13 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/26 11:23:51 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

long double	deg_to_rad(long double deg)
{
	return (deg * M_PI / 180);
}

long double	rad_to_deg(long double rad)
{
	return (rad * 180 / M_PI);
}
