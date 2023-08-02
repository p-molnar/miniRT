/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_ops_3.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 22:11:02 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/02 11:37:43 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_coord3	offset_pt(t_coord3 p, t_vec3 vec)
{
	int			i;
	t_coord3	new_point;
	t_coord3	offset_vec;

	i = 0;
	while (i < COORD_SIZE)
	{
		new_point.coord[i] = p.coord[i] + vec.dir.coord[i];
		i++;
	}
	offset_vec = create_coord(new_point.x, new_point.y, new_point.z);
	return (offset_vec);
}
