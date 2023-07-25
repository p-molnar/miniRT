/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 11:55:08 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/25 23:21:55 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <libft.h>
#include <math.h>
#include <minirt.h>
#include <mrt_error.h>
#include <mrt_macros.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

static void	parse_data(t_data *data, t_scn_el *el, char **input,
		t_line line_info)
{
	parse_type_identifier(el, input[0], line_info);
	if (is_duplicate_el_type(el->type, data))
		error((t_err){DUPLICATE_EL, line_info.file, line_info.num, EXIT, 1});
	if (el->type == F_AMB_LIGHT)
		parse_elements(el, input, AMB_LIGHT_FIELDS, line_info);
	else if (el->type == F_POINT_LIGHT)
		parse_elements(el, input, LIGHT_FIELDS, line_info);
	else if (el->type == F_DIR_LIGHT)
		parse_elements(el, input, DIR_LIGHT_FIELDS, line_info);
	else if (el->type == F_CAM)
		parse_elements(el, input, CAM_FIELDS, line_info);
	else if (el->type == F_TG_CAM)
		parse_elements(el, input, TG_CAM_FIELDS, line_info);
	else if (el->type == F_SPHERE)
		parse_elements(el, input, SPHERE_FIELDS, line_info);
	else if (el->type == F_PLANE)
		parse_elements(el, input, PLANE_FIELDS, line_info);
	else if (el->type == F_CYLINDER)
	{
		parse_elements(el, input, CYLINDER_FIELDS, line_info);
		add_cylinder_caps(el);
		populate_transformation_mx(el);
	}
}

static void	parse_line(t_data *scn, t_line *line)
{
	char		**el_info;
	t_scn_el	*el;
	t_list		*list_el;
	char		*tmp_line;

	tmp_line = line->content;
	line->content = ft_strtrim(tmp_line, "\n");
	free(tmp_line);
	if (!line->content)
		error((t_err){strerror(errno), __FILE__, __LINE__, EXIT, 1});
	el_info = ft_split(line->content, ' ');
	el = ft_calloc(1, sizeof(t_scn_el));
	if (!el_info || !el)
		error((t_err){strerror(errno), __FILE__, __LINE__, EXIT, 1});
	parse_data(scn, el, el_info, *line);
	list_el = ft_lstnew(el);
	if (!list_el)
		error((t_err){strerror(errno), __FILE__, __LINE__, EXIT, 1});
	ft_lstadd_back(&scn->all_scn_el, list_el);
	free_arr((void **)el_info);
}

void	parse_input(t_data *scn, int argc, char *argv[])
{
	int		fd;
	t_line	line;

	if (argc != 2)
		error((t_err){REQUIRED_ARGC, NULL, -1, EXIT, 1});
	fd = open_file(argv[1]);
	line.file = argv[1];
	line.content = get_next_line(fd);
	line.num = 1;
	while (line.content)
	{
		if (line.content[0] != '\n' && line.content[0] != '#')
			parse_line(scn, &line);
		free(line.content);
		line.content = get_next_line(fd);
		line.num++;
	}
	validate_scn_el_setup(scn);
}
