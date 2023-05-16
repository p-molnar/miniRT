/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coord_ops.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 10:49:45 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/16 11:03:06 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdlib.h>

t_coord3	*create_coord(long double x, long double y, long double z)
{
	t_coord3	*coord;

	coord = malloc(3 * sizeof(long double));
	if (!coord)
		return (NULL);
	coord[X] = x;
	coord[Y] = y;
	coord[Z] = z;
	return (coord);
}