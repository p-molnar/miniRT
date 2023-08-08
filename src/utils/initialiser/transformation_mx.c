/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transformation_mx.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 12:49:21 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/08 11:23:49 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdio.h>

bool	is_identical_coord(t_coord3 c1, t_coord3 c2)
{
	int	i;

	i = 0;
	while (i < COORD_SIZE)
	{
		if (c1.coord[i] != c2.coord[i])
			return (false);
		i++;
	}
	return (true);
}

void	populate_translation_mx(t_scn_el *el)
{
	t_mx	trans_mx;
	t_mx	inv_trans_mx;

	trans_mx = get_translation_mx(el->pos.x, el->pos.y, el->pos.z);
	inv_trans_mx = get_inverse_mx(trans_mx);
	el->translation = trans_mx;
	el->inv_translation = inv_trans_mx;
}

void	populate_rotation_mx(t_scn_el *el)
{
	long double	agl_r;
	t_vec3		pivot_ax;
	t_mx		pivot_mx;

	if (is_identical_coord((t_coord3){{0, 0, 0}}, el->orientation.dir))
		el->orientation.dir.z = 1;
	agl_r = get_agl_between(create_vec(0, 0, 1), el->orientation);
	pivot_ax = cross(create_vec(0, 0, 1), el->orientation);
	normalize_vec(&pivot_ax);
	pivot_mx = coord_to_mx(pivot_ax.dir, 4, 1, 1);
	el->rotation = get_rotation_mx(pivot_mx, agl_r);
	el->inv_rotation = get_inverse_mx(el->rotation);
}

void	populate_transformation_mx(t_scn_el *el)
{
	populate_translation_mx(el);
	populate_rotation_mx(el);
}
