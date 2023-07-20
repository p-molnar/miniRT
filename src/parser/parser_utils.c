/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 09:38:24 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/19 15:00:00 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <minirt.h>
#include <string.h>

int	open_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		error((t_err){strerror(errno), file_name, -1, EXIT, 1});
	return (fd);
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
