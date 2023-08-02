/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   coordinate_parser.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 09:35:12 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/02 11:41:03 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <mrt_macros.h>
#include <mrt_error.h>

void	parse_coordinates(t_coord3 *coord, char *input, t_line line_info)
{
	char		**coords;
	int			i;
	t_coord3	f;

	coords = ft_split(input, ',');
	if (!coords)
		error((t_err){strerror(errno), __FILE__, __LINE__, EXIT, 1});
	if (get_arr_size(coords) != 3)
		error((t_err){WRONG_SEP, line_info.file, line_info.num, EXIT, 1});
	i = 0;
	while (coords[i])
	{
		if (!is_valid_number(coords[i]))
			error((t_err){INVALID_NUM, line_info.file, line_info.num, EXIT, 1});
		f.coord[i] = ft_atof(coords[i]);
		coord->coord[i] = f.coord[i];
		i++;
	}
	free_arr((void **)coords);
}

void	parse_norm_vec(t_vec3 *vec, char *input, t_line line_info)
{
	char		**coords;
	int			i;
	t_coord3	f;
	t_vec3		f_vec;

	coords = ft_split(input, ',');
	if (!coords)
		error((t_err){strerror(errno), __FILE__, __LINE__, EXIT, 1});
	if (get_arr_size(coords) != 3) 
		error((t_err){WRONG_SEP, line_info.file, line_info.num, EXIT, 1});
	i = 0;
	while (coords[i])
	{
		if (!is_valid_number(coords[i]))
			error((t_err){INVALID_NUM, line_info.file, line_info.num, EXIT, 1});
		f.coord[i] = ft_atof(coords[i]);
		if (!is_in_range_f(f.coord[i], -1.0, 1.0, "[]"))
			error((t_err){OUT_OF_RANGE, line_info.file,
				line_info.num, EXIT, 1});
		i++;
	}
	f_vec = coord_to_vec(f);
	normalize_vec(&f_vec);
	ft_memcpy(vec, &f_vec, sizeof(t_vec3));
	free_arr((void **)coords);
}
