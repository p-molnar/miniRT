/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 10:46:11 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/08 11:32:13 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>
#include <stdlib.h>

void	init_scene(t_data *scn)
{
	ft_memset(scn, 0, sizeof(t_data));
}

void	create_projection_plane(t_data *d)
{
	long double	proj_plane_d;
	long double	proj_plane_side_len;
	long double	fov_rad;
	t_scn_el	**cam;

	proj_plane_d = 1;
	cam = get_scn_els(d->scn_el, CAM);
	if (!cam)
		error(ft_strdup("No camera found\n"), EXIT, 1);
	fov_rad = deg_to_rad(cam[0]->fov / 2.0);
	proj_plane_side_len = tan(fov_rad) * (2.0 * proj_plane_d);
	d->viewport[WIDTH] = proj_plane_side_len;
	d->viewport[HEIGHT] = proj_plane_side_len;
	free(cam);
}

void	set_up_rotation_mx(t_data *data)
{
	const long double	cam_orientation[COORD_SIZE] = {0, 0, 1};
	long double			r_angle;

	t_vec	*cam_orientation_vec = create_vec(NULL, (long double *) cam_orientation);
	r_angle = rad_to_deg(acos(dot(cam_orientation_vec, data->cam->n_vec)));
	t_vec	*rot_axis = cross(cam_orientation_vec, data->cam->n_vec);
	data->rotation_mx = get_rotation_mx(r_angle, rot_axis);
	free(cam_orientation_vec);
	free(rot_axis);
}

void	set_up_vars(t_data *data)
{
	t_list		*ptr;
	t_scn_el	*obj;
	t_scn_el	**cam;

	ptr = data->scn_el;
	while (ptr)
	{
		obj = ptr->content;
		obj->radius = obj->diameter / 2;
		ptr = ptr->next;
	}
	cam = get_scn_els(data->scn_el, CAM);
	if (cam)
		data->cam = cam[0];
	set_up_rotation_mx(data);
}