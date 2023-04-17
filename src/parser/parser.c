/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 11:55:08 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/17 18:23:16 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minirt.h>
#include <mrt_macros.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>

void	parse_data(t_scn_el *el, char **input)
{
	parse_type_identifier(el, input[0]);
	if (el->type == AMB_LIGHT)
		parse_elements(el, input, F_BRIGHT | F_COLOR);
	else if (el->type == CAM)
		parse_elements(el, input, F_COORD | F_VEC | F_FOV);
	else if (el->type == LIGHT)
		parse_elements(el, input, F_COORD | F_BRIGHT | F_COLOR);
	else if (el->type == SPHERE)
		parse_elements(el, input, F_COORD | F_DMETER | F_COLOR);
	else if (el->type == PLANE)
		parse_elements(el, input, F_COORD | F_VEC | F_COLOR);
	else if (el->type == CYLYNDER)
		parse_elements(el, input,
			F_COORD | F_VEC | F_DMETER | F_HEIGHT | F_COLOR);
}

void	parse_line(t_scn *scn, char *line)
{
	char		**el_info;
	t_scn_el	*el;
	t_list		*list_el;

	el_info = ft_split(line, ' ');
	el = ft_calloc(1, sizeof(t_scn_el));
	if (!el_info || !el)
		error(strconcat(4, "Malloc error: ", __FILE__, ":", ft_itoa(__LINE__)),
			EXIT, 1);
	// printf("line: %s\n", line);
	parse_data(el, el_info);
	list_el = ft_lstnew(el);
	if (!list_el)
		error(strconcat(4, "Malloc error: ", __FILE__, ":", ft_itoa(__LINE__)),
			EXIT, 1);
	ft_lstadd_back(&scn->els, list_el);
	free_arr(el_info);
}

void	parse_scene(t_scn *scn, int argc, char *argv[])
{
	int		fd;
	char	*line;
	char	*tmp;

	if (argc != 2)
		error(ft_strdup("Invalid argument count"), EXIT, 1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error(ft_strdup(strerror(errno)), EXIT, 1);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n')
		{
			tmp = line;
			line = ft_strtrim(line, "\n");
			if (!line)
				error(strconcat(4, "Malloc error: ", __FILE__, ": ",
						ft_itoa(__LINE__)), EXIT, 1);
			free(tmp);
			parse_line(scn, line);
		}
		free(line);
		line = get_next_line(fd);
	}
}
