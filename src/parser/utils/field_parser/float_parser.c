/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   float_parser.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 12:37:52 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/01 15:24:18 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minirt.h>
#include <mrt_error.h>
#include <mrt_macros.h>
#include <stdio.h>

void	parse_range(long double *f, char *input, t_range range,
		t_line line_info)
{
	if (!f || !input)
		error((t_err){"NULL pointer", __FILE__, __LINE__, EXIT, 1});
	if (!is_valid_number(input))
		error((t_err){INVALID_NUM, line_info.file, line_info.num, EXIT, 1});
	*f = ft_atof(input);
	if (!is_in_range_f(*f, range.min, range.max))
		error((t_err){OUT_OF_RANGE, line_info.file, line_info.num, EXIT, 1});
}
