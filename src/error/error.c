/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:50:50 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/19 14:53:23 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mrt_macros.h>
#include <mrt_data_struct.h>
#include <stdio.h>
#include <stdlib.h>

#define RED "\033[0;31m"
#define DEF "\033[0m"

int	error(t_err error)
{
	printf("%sError%s\n", RED, DEF);
	if (error.msg)
		printf("%s: ", error.msg);
	if (error.file)
		printf("%s", error.file);
	if (error.line > 0)
		printf(":%d\n", error.line);
	printf("\nUsage: ./minirt <path-to-map>\n");
	if (error.exit_method == EXIT)
		exit(error.exit_code);
	else if (error.exit_method == RETURN)
		return (error.exit_code);
	return (EXIT_FAILURE);
}