/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transformation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 11:51:58 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/06/08 13:16:46 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>

t_coord3	*get_SiRi(t_coord3 *c, t_coord3 *obj_coord)
{
	t_mx	*c_mx;
	t_mx	*trans_mx;
	t_mx	*tmp;

	tmp = coord_to_mx(c, 3, 1);
	c_mx = expand_mx(tmp, 4, 1, 1);
	free(tmp);
	trans_mx = get_translation_mx(obj_coord->x, obj_coord->y, obj_coord->z);
	c_mx = multiply_mx(trans_mx, c_mx);
	return (create_coord(c_mx->m[X], c_mx->m[Y], c_mx->m[Z]));
}

t_coord3	*get_RSi(t_coord3 *c, t_coord3 *obj_coord)
{
	t_mx	*c_mx;
	t_mx	*trans_mx;
	t_mx	*tmp;

	tmp = coord_to_mx(c, 3, 1);
	c_mx = expand_mx(tmp, 4, 1, 1);
	free(tmp);
	trans_mx = get_translation_mx(obj_coord->x, obj_coord->y, obj_coord->z);
	c_mx = multiply_mx(trans_mx, c_mx);
	return (create_coord(c_mx->m[X], c_mx->m[Y], c_mx->m[Z]));
}

t_coord3	*get_TRS(t_coord3 *c, t_coord3 *obj_coord)
{
	t_mx	*c_mx;
	t_mx	*trans_mx;
	t_mx	*tmp;

	tmp = coord_to_mx(c, 3, 1);
	c_mx = expand_mx(tmp, 4, 1, 1);
	free(tmp);
	trans_mx = get_translation_mx(obj_coord->x, obj_coord->y, obj_coord->z);
	c_mx = multiply_mx(trans_mx, c_mx);
	return (create_coord(c_mx->m[X], c_mx->m[Y], c_mx->m[Z]));
}

t_coord3	*get_SiRiTi(t_coord3 *c, t_coord3 *obj_coord)
{
	t_mx *c_mx;
	t_mx *trans_mx;
	t_mx *tmp;

	tmp = coord_to_mx(c, 3, 1);
	c_mx = expand_mx(tmp, 4, 1, 1);
	free(tmp);
	trans_mx = get_translation_mx(obj_coord->x, obj_coord->y, obj_coord->z);
	t_mx *inv_trans_mx = get_inverse_mx(trans_mx);
	c_mx = multiply_mx(inv_trans_mx, c_mx);
	return (create_coord(c_mx->m[X], c_mx->m[Y], c_mx->m[Z]));
}