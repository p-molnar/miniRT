/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:50:50 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/09 18:06:17 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>

#define RED "\033[0;31m"
#define DEF "\033[0m"

void	mlx_err(t_data *data)
{
	clean_up(data);
	error((t_err){mlx_strerror(mlx_errno), NULL, 0, EXIT, 1});
}

int	error(t_err error)
{
	printf("%sError%s\n", RED, DEF);
	if (error.file)
		printf("%s", error.file);
	if (error.line > 0)
		printf(":%d ", error.line);
	if (error.msg)
		printf("\t%s", error.msg);
	printf("\nUsage: ./minirt <path-to-scene>.rt\n");
	if (error.exit_method == EXIT)
		exit(error.exit_code);
	else if (error.exit_method == RETURN)
		return (error.exit_code);
	return (EXIT_FAILURE);
}
