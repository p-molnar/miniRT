/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 11:55:08 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/09 19:39:24 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <libft.h>
#include <minirt.h>
#include <mrt_macros.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool	is_duplicate_el_type(enum e_scn_el_type_flags el_type, t_data *scn)
{
	t_list		*tmp;
	t_scn_el	*el;

	tmp = scn->all_scn_el;
	while (tmp)
	{
		el = tmp->content;
		if (is_in_range_i(el_type, F_AMB_LIGHT, F_TG_CAM))
		{
			if (el_type == el->type)
				return (true);
			else if (el_type == F_CAM && el->type == F_TG_CAM)
				return (true);
			else if (el_type == F_TG_CAM && el->type == F_CAM)
				return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

void	validate_scn_el_setup(t_data *scn)
{
	t_scn_el	*el;
	t_list		*tmp;
	long double	total_light_brightness;
	int			els;

	tmp = scn->all_scn_el;
	total_light_brightness = 0;
	els = 0;
	while (tmp)
	{
		el = tmp->content;
		total_light_brightness += el->intensity;
		els |= el->type;
		tmp = tmp->next;
	}
	if (!((els & F_CAM) || (els & F_TG_CAM)))
		error(ft_strdup("Required element missing: Camera"), EXIT, 1);
	if (scn && total_light_brightness < 0.05)
		warning(
			ft_strdup("Too dark scene: add lights, or increase brightness.")
			);
}

void	parse_data(t_data *scn, t_scn_el *el, char **input)
{
	parse_type_identifier(el, input[0]);
	if (is_duplicate_el_type(el->type, scn))
		error(ft_strdup("Duplicate element definition"), EXIT, 1);
	if (el->type == F_AMB_LIGHT)
		parse_elements(el, input, AMB_LIGHT_FIELDS);
	else if (el->type == F_POINT_LIGHT)
		parse_elements(el, input, LIGHT_FIELDS);
	else if (el->type == F_DIR_LIGHT)
		parse_elements(el, input, DIR_LIGHT_FIELDS);
	else if (el->type == F_CAM)
		parse_elements(el, input, CAM_FIELDS);
	else if (el->type == F_TG_CAM)
		parse_elements(el, input, TG_CAM_FIELDS);
	else if (el->type == F_SPHERE)
		parse_elements(el, input, SPHERE_FIELDS);
	else if (el->type == F_PLANE)
		parse_elements(el, input, PLANE_FIELDS);
	else if (el->type == F_CYLINDER)
	{
		parse_elements(el, input, CYLINDER_FIELDS);
		add_cylinder_caps(el);
		populate_transformation_mx(scn, el);
	}
}

void	parse_line(t_data *scn, char *line)
{
	char		**el_info;
	t_scn_el	*el;
	t_list		*list_el;

	el_info = ft_split(line, ' ');
	el = ft_calloc(1, sizeof(t_scn_el));
	if (!el_info || !el)
		error(strconcat(4, "Malloc error: ", __FILE__, ":", ft_itoa(__LINE__)),
				EXIT,
				1);
	parse_data(scn, el, el_info);
	list_el = ft_lstnew(el);
	if (!list_el)
		error(strconcat(4, "Malloc error: ", __FILE__, ":", ft_itoa(__LINE__)),
				EXIT,
				1);
	ft_lstadd_back(&scn->all_scn_el, list_el);
	free_arr((void **)el_info);
}

void	parse_input(t_data *scn, int argc, char *argv[])
{
	int		fd;
	char	*line;
	char	*tmp;

	if (argc != 2)
		error(ft_strdup("Expected argument count: 2"), EXIT, 1);
	fd = open_file(argv[1]);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n' && line[0] != '#')
		{
			tmp = line;
			line = ft_strtrim(tmp, "\n");
			if (!line)
				error(ft_strdup("Malloc error"), EXIT, 1);
			free(tmp);
			parse_line(scn, line);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	validate_scn_el_setup(scn);
}
