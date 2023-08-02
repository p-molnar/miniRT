/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   range.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/26 10:57:31 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/02 11:24:37 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	is_in_range_f(long double n, long double bound_low,
		long double bound_up, char bound_criteria[2])
{
	char	lower_bound;
	char	upper_bound;
	bool	is_in_range_lower;
	bool	is_in_range_upper;

	is_in_range_lower = false;
	is_in_range_upper = false;
	lower_bound = bound_criteria[0];
	upper_bound = bound_criteria[1];
	if (lower_bound == '(')
		is_in_range_lower = n > bound_low;
	else if (lower_bound == '[')
		is_in_range_lower = n >= bound_low;
	if (upper_bound == ')')
		is_in_range_upper = n < bound_up;
	else if (upper_bound == ']')
		is_in_range_upper = n <= bound_up;
	return (is_in_range_lower && is_in_range_upper);
}
