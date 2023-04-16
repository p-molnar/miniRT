/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 11:55:08 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/16 20:32:29 by pmolnar       ########   odam.nl         */
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

void	parse_type_identifier(t_scn_el *el, char *line)
{
	int		el_type;
	int		len;

	len = ft_strlen(line) + 1;
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

void	parse_line(t_scn *scn, char *line)
{
	char		**el_info;
	t_scn_el	*el;

	el_info = ft_split(line, ' ');
	el = ft_calloc(1, sizeof(t_scn_el));
	printf("line: %s", line);
	if (!el_info || !el)
		error(ft_strdup("Malloc error: __FILE__: __LINE__"), EXIT, 1);
	parse_type_identifier(el, el_info[0]);
}

void	parse_scene(t_scn *scn, int argc, char *argv[])
{
	int		fd;
	char	*line;
	t_list	*el;

	if (argc != 2)
		error(ft_strdup("Invalid argument count"), EXIT, 1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error(ft_strdup(strerror(errno)), EXIT, 1);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n')
			parse_line(scn, line);
		free(line);
		line = get_next_line(fd);
	}
}


