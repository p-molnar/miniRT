/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coordinate_parser.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 09:35:12 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/17 21:17:25 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <mrt_macros.h>

void	parse_coordinates(t_coord3 *coord, char *input)
{
	char		**coords;
	int			i;
	t_coord3	f;

	coords = ft_split(input, ',');
	if (!coords)
		error(strconcat(4, "Malloc error: ", __FILE__, ":", ft_itoa(__LINE__)),
				EXIT, 1);
	if (get_arr_size(coords) != 3)
		error(ft_strdup("Required coordinates: x, y, x"), EXIT, 1);
	i = 0;
	while (coords[i])
	{
		if (!is_valid_number(coords[i]))
			error(strconcat(2, "Invalid number: ", coords[i]), EXIT, 1);
		f.coord[i] = ft_atof(coords[i]);
		coord->coord[i] = f.coord[i];
		i++;
	}
	free_arr((void **)coords);
}

void	parse_norm_vec(t_vec3 *vec, char *input)
{
	char		**coords;
	int			i;
	t_coord3	f;
	t_vec3		f_vec;

	coords = ft_split(input, ',');
	if (!coords)
		error(strconcat(4, "Malloc error: ", __FILE__, ":", ft_itoa(__LINE__)),
				EXIT, 1);
	if (get_arr_size(coords) != 3)
		error(ft_strdup("Required coordinates: x, y, x"), EXIT, 1);
	i = 0;
	while (coords[i])
	{
		if (!is_valid_number(coords[i]))
			error(strconcat(2, "Invalid number: ", coords[i]), EXIT, 1);
		f.coord[i] = ft_atof(coords[i]);
		if (!is_in_range_f(f.coord[i], -1.0, 1.0))
			error(strconcat(6, "Number out of range [", "-1.0", ", ", "1.0",
						"]: ", coords[i]), EXIT, 1);
		i++;
	}
	f_vec = coord_to_vec(f);
	normalize(&f_vec);
	ft_memcpy(vec, &f_vec, sizeof(t_vec3));
	free_arr((void **)coords);
}
