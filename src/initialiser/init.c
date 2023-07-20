/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 10:46:11 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/20 15:28:41 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>

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
	ft_memcpy(&el->translation, &trans_mx, sizeof(t_mx));
	ft_memcpy(&el->inv_translation, &inv_trans_mx, sizeof(t_mx));
}

void	populate_rotation_mx(t_scn_el *el)
{
	long double		agl_r;
	t_vec3			pivot_ax;
	t_mx			pivot_mx;
	t_mx			rot_mx;
	t_mx			inv_rot_mx;
	t_vec3			dft_world_orientation;

	dft_world_orientation = create_vec(0, 0, 1);
	if (is_identical_coord((t_coord3) {{0, 0, 0}}, el->n_vec.dir))
		el->n_vec.dir.z = 1;
	agl_r = get_agl_between(dft_world_orientation, el->n_vec);
	printf("agl_r: %Lf\n", agl_r);
	pivot_ax = cross(dft_world_orientation, el->n_vec);
	normalize(&pivot_ax);
	pivot_mx = coord_to_mx(pivot_ax.dir, 4, 1, 1);
	rot_mx = get_rotation_mx(pivot_mx, agl_r);
	inv_rot_mx = get_inverse_mx(rot_mx);
	ft_memcpy(&el->rotation, &rot_mx, sizeof(t_mx));
	ft_memcpy(&el->inv_rotation, &inv_rot_mx, sizeof(t_mx));
	printf("rotation_mx\n");
	print_mx(&el->rotation);
	printf("inverse_rotation mx\n");
	print_mx(&el->inv_rotation);
}

void	populate_transformation_mx(t_scn_el *el)
{
	populate_translation_mx(el);
	populate_rotation_mx(el);
}

void	set_up_camera_orientation(t_data *d)
{
	t_vec3		right_vec;
	t_vec3		fw_vec;
	t_vec3		up_vec;
	t_mx		ctw_mx_local;
	t_vec3		dft_up_vec;
	t_scn_el	*cam;

	dft_up_vec = create_vec(0, 1, 0);
	cam = *d->scn_els[CAM];
	if (cam->type == F_CAM)
		fw_vec = coord_to_vec(cam->n_vec.dir);
	else
	{
		fw_vec = create_dir_vec(cam->pos, cam->target);
		normalize(&fw_vec);
	}
	if (fw_vec.dir.x == 0 && fw_vec.dir.y == 0 && fw_vec.dir.z == 0)
	{
		fw_vec.dir.z = 1;
		fw_vec.len = 1;
	}
	else if ((fw_vec.dir.x == 0 && fw_vec.dir.z == 0) && (fw_vec.dir.y ==
				-1 || fw_vec.dir.y == 1))
	{
		dft_up_vec.dir.y = 0;
		dft_up_vec.dir.z = 1;
		fw_vec.len = 1;
	}
	right_vec = cross(dft_up_vec, fw_vec);
	normalize(&right_vec);
	up_vec = cross(fw_vec, right_vec);
	normalize(&up_vec);
	ft_memset(&ctw_mx_local, 0, sizeof(t_mx));
	ctw_mx_local.m[0] = right_vec.dir.x;
	ctw_mx_local.m[1] = up_vec.dir.x;
	ctw_mx_local.m[2] = fw_vec.dir.x;
	ctw_mx_local.m[3] = cam->pos.x;
	ctw_mx_local.m[4] = right_vec.dir.y;
	ctw_mx_local.m[5] = up_vec.dir.y;
	ctw_mx_local.m[6] = fw_vec.dir.y;
	ctw_mx_local.m[7] = cam->pos.y;
	ctw_mx_local.m[8] = right_vec.dir.z;
	ctw_mx_local.m[9] = up_vec.dir.z;
	ctw_mx_local.m[10] = fw_vec.dir.z;
	ctw_mx_local.m[11] = cam->pos.z;
	ctw_mx_local.m[15] = 1;
	ctw_mx_local.c = 4;
	ctw_mx_local.r = 4;
	ft_memcpy(&d->ctw_mx, &ctw_mx_local, sizeof(t_mx));
	print_mx(&d->ctw_mx);
}
