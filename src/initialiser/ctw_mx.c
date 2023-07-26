/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ctw_mx.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 10:46:11 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/26 15:17:42 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>

t_mx	get_ctw_mx(t_vec3 right, t_vec3 up, t_vec3 fw, t_scn_el cam)
{
	t_mx	ctw_mx;

	ft_memset(&ctw_mx, 0, sizeof(t_mx));
	ctw_mx.c = 4;
	ctw_mx.r = 4;
	ctw_mx.m[0] = right.dir.x;
	ctw_mx.m[1] = up.dir.x;
	ctw_mx.m[2] = fw.dir.x;
	ctw_mx.m[3] = cam.pos.x;
	ctw_mx.m[4] = right.dir.y;
	ctw_mx.m[5] = up.dir.y;
	ctw_mx.m[6] = fw.dir.y;
	ctw_mx.m[7] = cam.pos.y;
	ctw_mx.m[8] = right.dir.z;
	ctw_mx.m[9] = up.dir.z;
	ctw_mx.m[10] = fw.dir.z;
	ctw_mx.m[11] = cam.pos.z;
	ctw_mx.m[15] = 1;
	return (ctw_mx);
}

void	get_directional_vectors(t_vec3 *up, t_vec3 *fw, t_scn_el *cam)
{
	*up = create_vec(0, 1, 0);
	*fw = coord_to_vec(cam->n_vec.dir);
	if ((fw->dir.x == 0 && fw->dir.z == 0) && (fw->dir.y == -1
				|| fw->dir.y == 1))
	{
		up->dir.y = 0;
		up->dir.z = 1;
	}
}

void	set_up_ctw_mx(t_data *d)
{
	t_vec3	right;
	t_vec3	fw;
	t_vec3	up;
	t_mx	ctw;

	get_directional_vectors(&up, &fw, *d->scn_els[CAM]);
	right = cross(up, fw);
	normalize(&right);
	up = cross(fw, right);
	normalize(&up);
	ctw = get_ctw_mx(right, up, fw, **d->scn_els[CAM]);
	ft_memcpy(&d->ctw_mx, &ctw, sizeof(t_mx));
	print_mx(&d->ctw_mx);
}
