/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_validator.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/28 14:39:15 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/28 14:49:51 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <mrt_macros.h>
#include <mrt_data_struct.h>
#include <mrt_error.h>

void	validate_line_formatting(t_scn_el el, char **input,
		t_line line_info)
{
	int	arr_size;

	arr_size = get_arr_size(input);
	if (el.type == F_AMB_LIGHT && arr_size != 3)
		error((t_err){FMT_E_AMB_LIGHT, line_info.file, line_info.num, EXIT, 1});
	else if (el.type == F_POINT_LIGHT && arr_size != 4)
		error((t_err){FMT_E_PNT_LIGHT, line_info.file, line_info.num, EXIT, 1});
	else if (el.type == F_DIR_LIGHT && arr_size != 5)
		error((t_err){FMT_E_DIR_LIGHT, line_info.file, line_info.num, EXIT, 1});
	else if (el.type == F_CAM && arr_size != 4)
		error((t_err){FMT_E_CAM, line_info.file, line_info.num, EXIT, 1});
	else if (el.type == F_TG_CAM && arr_size != 4)
		error((t_err){FMT_E_TGCAM, line_info.file, line_info.num, EXIT, 1});
	else if (el.type == F_SPHERE && arr_size != 6)
		error((t_err){FMT_E_SPHERE, line_info.file, line_info.num, EXIT, 1});
	else if (el.type == F_PLANE && arr_size != 6)
		error((t_err){FMT_E_PLANE, line_info.file, line_info.num, EXIT, 1});
	else if (el.type == F_CYLINDER && arr_size != 8)
		error((t_err){FMT_E_CYLINDER, line_info.file, line_info.num, EXIT, 1});
}
