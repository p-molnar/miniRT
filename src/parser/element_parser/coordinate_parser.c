/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coordinate_parser.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 09:35:12 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/06/08 10:53:24 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <mrt_macros.h>

void	parse_coordinates(long double *coord, char *input)
{
	char		**coords;
	int			i;
	long double	f[3];

	coords = ft_split(input, ',');
	if (!coords)
		error(strconcat(4, "Malloc error: ", __FILE__, ":",
				ft_itoa(__LINE__)), EXIT, 1);
	if (get_arr_size(coords) != 3)
		error(ft_strdup("Required coordinates: x, y, x"), EXIT, 1);
	i = 0;
	while (coords[i])
	{
		if (!is_valid_number(coords[i]))
			error(strconcat(2, "Invalid number: ", coords[i]), EXIT, 1);
		f[i] = ft_atof(coords[i]);
		coord[i] = f[i];
		i++;
	}
	free_arr((void **)coords);
}

void	parse_norm_vec(t_vec3 **vec, char *input)
{
	char		**coords;
	int			i;
	t_coord3	f[3];

	coords = ft_split(input, ',');
	if (!coords)
		error(strconcat(4, "Malloc error: ", __FILE__, ":",
				ft_itoa(__LINE__)), EXIT, 1);
	if (get_arr_size(coords) != 3)
		error(ft_strdup("Required coordinates: x, y, x"), EXIT, 1);
	i = 0;
	while (coords[i])
	{
		if (!is_valid_number(coords[i]))
			error(strconcat(2, "Invalid number: ", coords[i]), EXIT, 1);
		f[i] = ft_atof(coords[i]);
		if (!is_in_range_f(f[i], -1.0, 1.0))
			error(strconcat(6, "Number out of range [",
					"-1.0", ", ", "1.0", "]: ", coords[i]), EXIT, 1);
		i++;
	}
	*vec = coord_to_vec(f);
	normalize(*vec);
	if (!vec)
		error(ft_strdup("Malloc error at vector creation"), EXIT, 1);
	free_arr((void **)coords);
}
