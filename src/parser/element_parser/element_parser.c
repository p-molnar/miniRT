/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   element_parser.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 09:27:54 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/26 10:47:19 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <mrt_data_struct.h>
#include <mrt_macros.h>
#include <stdio.h>

void	parse_type_identifier(t_scn_el *el, char *line)
{
	int	el_type;
	int	str_len;

	str_len = ft_strlen(line) + 1;
	el_type = TYPE_UNDEF;
	if (ft_strncmp("A", line, str_len) == 0)
		el_type = AMB_LIGHT;
	else if (ft_strncmp("L", line, str_len) == 0)
		el_type = POINT_LIGHT;
	else if (ft_strncmp("DL", line, str_len) == 0)
		el_type = DIR_LIGHT;
	else if (ft_strncmp("C", line, str_len) == 0)
		el_type = CAM;
	else if (ft_strncmp("TC", line, str_len) == 0)
		el_type = TG_CAM;
	else if (ft_strncmp("sp", line, str_len) == 0)
		el_type = SPHERE;
	else if (ft_strncmp("pl", line, str_len) == 0)
		el_type = PLANE;
	else if (ft_strncmp("cy", line, str_len) == 0)
		el_type = CYLINDER;
	else
		error(strconcat(3, "Unknown element: '", line,
					"'. Element must be of type: A, C, TC, L, DL, sp, pl, cy"), EXIT,
				1);
	el->type = el_type;
}

void	parse_elements(t_scn_el *el, char **input, unsigned int field)
{
	int	col;

	col = 1;
	if (field & F_COORD)
		parse_coordinates(el->coord, input[col++]);
	if (field & F_TG_COORD)
		parse_coordinates(el->tg_coord, input[col++]);
	if (field & F_N_VEC)
		parse_norm_vec(&el->n_vec, input[col++]);
	if (field & F_DMETER)
		parse_float(&el->diameter, input[col++]);
	if (field & F_HEIGHT)
		parse_float(&el->height, input[col++]);
	if (field & F_FOV)
		parse_range(&el->fov, input[col++], 0.0, 180.0);
	if (field & F_INTENSITY)
		parse_range(&el->intensity, input[col++], 0.0, 1.0);
	if (field & F_COLOR)
		parse_color(&el->color, input[col++], 0, 255);
	if (field & F_SPECULAR)
		parse_range(&el->specular, input[col++], -1, 3000);
	if (field & F_REFLECTION)
		parse_range(&el->reflection, input[col++], 0, 1);
}
