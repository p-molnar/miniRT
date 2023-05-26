/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 10:46:11 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/26 16:56:34 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>

void	init_scene(t_data *scn)
{
	ft_memset(scn, 0, sizeof(t_data));
}

void	create_projection_plane(t_data *d)
{
	long double	fov_rad;
	t_scn_el	**cam;

	cam = get_scn_els(d->scn_el, CAM | TG_CAM);
	if (!cam)
		error(ft_strdup("No camera found\n"), EXIT, 1);
	fov_rad = deg_to_rad(cam[0]->fov / 2.0);
	d->viewport[WIDTH] = 1;
	d->viewport[HEIGHT] = 1;
	d->viewport[DEPTH] = 0.5 / tan(fov_rad);
	free(cam);
}

int	is_cam_rotated(t_vec3 *n_vec)
{
	int	i;

	i = 0;
	while (i < COORD_SIZE && n_vec)
	{
		if (n_vec->dir[i] != 0)
			return (1);
		i++;
	}
	return (0);
}

void	set_up_rotation_mx(t_data *data)
{
	t_vec3		*rot_ax;
	long double	rot_agl;
	t_vec3		*cam_orientation_vec;
	t_vec3		*tg_dir;

	cam_orientation_vec = create_vec(NULL, create_coord(0, 0, 1));
	if (data->cam->type == CAM)
	{
		if (is_cam_rotated(data->cam->n_vec))
		{
			data->cam->n_vec = get_normal_vec(data->cam->n_vec);
			rot_agl = -acos(dot(cam_orientation_vec, data->cam->n_vec));
			rot_ax = cross(cam_orientation_vec, data->cam->n_vec);
		}
		else
		{
			rot_agl = 0;
			rot_ax = cross(cam_orientation_vec, cam_orientation_vec);
		}
		printf("cam dir: %Lf, %Lf, %Lf\n", data->cam->n_vec->dir[0],
				data->cam->n_vec->dir[1], data->cam->n_vec->dir[2]);
	}
	else
	{
		tg_dir = get_normal_vec(create_vec(data->cam->coord, data->cam->tg_coord));
		rot_agl = -acos(dot(cam_orientation_vec, tg_dir) / (cam_orientation_vec->len * tg_dir->len));
		rot_ax = cross(cam_orientation_vec, tg_dir);
		printf("cam dir: %Lf, %Lf, %Lf\n", tg_dir->dir[0],
				tg_dir->dir[1], tg_dir->dir[2]);
	}
	if (rot_ax->dir[X] == 0 && rot_ax->dir[Y] == 0 && rot_ax->dir[Z] == 0)
		rot_ax = create_vec(NULL, create_coord(1, 0, 0));
	data->rot_axis = get_normal_vec(rot_ax);
	data->rot_angle = rot_agl;
	printf("angle: %Lf, rad: %Lf\n", rad_to_deg(rot_agl), rot_agl);
	printf("rotation axis: %Lf, %Lf, %Lf\n", data->rot_axis->dir[0],
			data->rot_axis->dir[1], data->rot_axis->dir[2]);
	free(cam_orientation_vec);
	free(rot_ax);
}

void	set_up_vars(t_data *data)
{
	t_list *ptr;
	t_scn_el *obj;
	t_scn_el **cam;

	ptr = data->scn_el;
	while (ptr)
	{
		obj = ptr->content;
		obj->radius = obj->diameter / 2;
		ptr = ptr->next;
	}
	cam = get_scn_els(data->scn_el, CAM | TG_CAM);
	if (cam)
		data->cam = cam[0];
	set_up_rotation_mx(data);
}