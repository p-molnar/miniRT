/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:00:14 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/14 14:13:42 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <mrt_data_struct.h>
#include <stdlib.h>

void	init_scene(t_scn *scn)
{
	scn->els = NULL;
}

int	main(int argc, char *argv[])
{
	t_scn	scn;

	init_scene(&scn);
	parse_scene(&scn, argc, argv);
	return (EXIT_SUCCESS);
}
