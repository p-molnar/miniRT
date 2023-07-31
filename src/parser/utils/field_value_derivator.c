/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   field_value_derivator.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/28 14:46:16 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/31 00:53:19 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <mrt_data_struct.h>
#include <mrt_macros.h>

static void	populate_dir_light_derived_fields(t_scn_el *el)
{
	t_vec3	light_dir;

	light_dir = create_dir_vec(el->pos, el->target);
	if (light_dir.dir.x == 0 && light_dir.dir.y == 0 && light_dir.dir.z == 0)
	{
		el->type = F_TYPE_UNDEF;
		return ;
	}
	normalize(&light_dir);
	ft_memcpy(&el->n_vec, &light_dir, sizeof(t_vec3));
}

static void	populate_camera_derived_fields(t_scn_el *el)
{
	t_vec3	cam_dir;

	if (el->type == F_TG_CAM)
	{
		el->type = F_CAM;
		cam_dir = create_dir_vec(el->pos, el->target);
		normalize(&cam_dir);
		ft_memcpy(&el->n_vec, &cam_dir, sizeof(t_vec3));
	}
	if (el->type == F_CAM)
	{
		if (el->n_vec.dir.x == 0 && el->n_vec.dir.y == 0
			&& el->n_vec.dir.z == 0)
		{
			cam_dir = create_vec(0, 0, 1);
			ft_memcpy(&el->n_vec, &cam_dir, sizeof(t_vec3));
		}
	}
}

void	populate_derived_fields(t_scn_el *el)
{
	if (el->type == F_CAM || el->type == F_TG_CAM)
		populate_camera_derived_fields(el);
	else if (el->type == F_DIR_LIGHT)
		populate_dir_light_derived_fields(el);
}
