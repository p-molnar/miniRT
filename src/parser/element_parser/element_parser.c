/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   element_parser.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 09:27:54 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/17 13:55:12 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mrt_macros.h>
#include <mrt_data_struct.h>
#include <minirt.h>
#include <stdio.h>

void	parse_type_identifier(t_scn_el *el, char *line)
{
	int		el_type;
	int		len;

	len = ft_strlen(line) + 1;
	el_type = UNDEFINED;
	if (ft_strncmp("A", line, len) == 0)
		el_type = AMB_LIGHT;
	else if (ft_strncmp("C", line, len) == 0)
		el_type = CAM;
	else if (ft_strncmp("L", line, len) == 0)
		el_type = LIGHT;
	else if (ft_strncmp("sp", line, len) == 0)
		el_type = SPHERE;
	else if (ft_strncmp("pl", line, len) == 0)
		el_type = PLANE;
	else if (ft_strncmp("cy", line, len) == 0)
		el_type = CYLYNDER;
	else
		error(ft_strdup("Unkown type identifier"), EXIT, 1);
	el->type = el_type;
}

void	parse_elements(t_scn_el *el, char **input, unsigned int flags)
{
	int	col;

	col = 1;
	if (flags & F_COORD)
		parse_coordinates(el->coord, input[col++]);
	if (flags & F_VEC)
		parse_norm_vec(el->norm_vec, input[col++]);
	if (flags & F_DMETER)
		parse_float(&el->diameter, input[col++]);
	if (flags & F_HEIGHT)
		parse_float(&el->height, input[col++]);
	if (flags & F_FOV)
		parse_range(&el->fov, input[col++], 0.0, 180.0);
	if (flags & F_BRIGHT)
		parse_range(&el->brightness, input[col++], 0.0, 1.0);
	if (flags & F_COLOR)
		parse_color(el->color, input[col++], 0, 255);
}
