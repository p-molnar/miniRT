/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 10:46:11 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/06/09 00:18:51 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>

void	set_up_camera(t_data *d)
{
	t_vec3		*right_vec;
	t_vec3		*fw_vec;
	t_vec3		*up_vec;
	t_vec3		*def_up_vec;
	t_scn_el	*cam;

	cam = *d->scn_el[CAM];
	def_up_vec = create_vec(0, 1, 0);
	if (cam->type == F_CAM)
		fw_vec = cam->n_vec;
	else
	{
		fw_vec = create_dir_vec(cam->pos, cam->target);
		// printf("fw_vec: %Lf, %Lf, %Lf\n", fw_vec->dir.x, fw_vec->dir.y, fw_vec->dir.z);
		normalize(fw_vec);
	}
	if (fw_vec->dir.x == 0 && fw_vec->dir.y == 0 && fw_vec->dir.z == 0)
	{
		fw_vec->dir.z = 1;
		fw_vec->len = 1;
	}
	else if ((fw_vec->dir.x == 0 && fw_vec->dir.z == 0) && (fw_vec->dir.y ==
				-1 || fw_vec->dir.y == 1))
	{
		def_up_vec->dir.y = 0;
		def_up_vec->dir.z = 1;
		fw_vec->len = 1;
	}
	right_vec = cross(def_up_vec, fw_vec);
	normalize(right_vec);
	up_vec = cross(fw_vec, right_vec);
	normalize(up_vec);
	printf("forward: %Lf, %Lf, %Lf\n", fw_vec->dir.x, fw_vec->dir.y,
			fw_vec->dir.z);
	printf("right: %Lf, %Lf, %Lf\n", right_vec->dir.x, right_vec->dir.y,
			right_vec->dir.z);
	printf("up: %Lf, %Lf, %Lf\n", up_vec->dir.x, up_vec->dir.y,
			up_vec->dir.z);
	d->ctw_mx = malloc(sizeof(t_mx));
	d->ctw_mx->r = 4;
	d->ctw_mx->c = 4;
	d->ctw_mx->m = ft_calloc(16, sizeof(long double));
	d->ctw_mx->m[0] = right_vec->dir.x;
	d->ctw_mx->m[1] = up_vec->dir.x;
	d->ctw_mx->m[2] = fw_vec->dir.x;
	d->ctw_mx->m[3] = cam->pos.x;
	d->ctw_mx->m[4] = right_vec->dir.y;
	d->ctw_mx->m[5] = up_vec->dir.y;
	d->ctw_mx->m[6] = fw_vec->dir.y;
	d->ctw_mx->m[7] = cam->pos.y;
	d->ctw_mx->m[8] = right_vec->dir.z;
	d->ctw_mx->m[9] = up_vec->dir.z;
	d->ctw_mx->m[10] = fw_vec->dir.z;
	d->ctw_mx->m[11] = cam->pos.z;
	d->ctw_mx->m[15] = 1;
	print_mx(d->ctw_mx);
}
