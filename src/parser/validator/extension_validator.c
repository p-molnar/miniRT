/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extension_validator.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/07 19:18:21 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/07 20:26:27 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <libft.h>

bool	is_valid_extension(char *file_name)
{
	char	*separator;

	if (file_name)
	{
		separator = ft_strchr(file_name, '.');
		if (separator)
			return (!ft_strncmp(separator, ".rt", ft_strlen(separator) + 1));
	}
	return (false);
}
