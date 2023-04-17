/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 09:38:24 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/17 13:53:10 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	is_in_range_f(float n, float n_lower, float n_upper)
{
	return (n >= n_lower && n <= n_upper);
}

int	is_in_range_i(int n, int n_lower, int n_upper)
{
	return (n >= n_lower && n <= n_upper);
}

int	get_arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		i++;
	}
	return (i);
}

int	is_valid_number(char *c)
{
	int	i;
	int	c_len;

	i = 0;
	c_len = ft_strlen(c);
	if (!ft_isdigit(c[i]) && !ft_strchr("+-", c[i]))
		return (0);
	i++;
	while (ft_isdigit(c[i]))
		i++;
	if (c[i] == '.')
		i++;
	while (ft_isdigit(c[i]))
		i++;
	return (c_len == i);
}
