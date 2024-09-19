/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 14:09:10 by pstrohal          #+#    #+#             */
/*   Updated: 2024/09/15 16:38:40 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	error(int e_action, int e_error)
{
	static int error_status;

	if (e_action == GET)
		return (error_status);
	else if (e_action == SET)
		error_status = e_error;
	return (NOUGHT);
}

void err_check(void *p, int e_error)
{
	if (!p)
	{
		exit(e_error);
	}
	else
		return ;
}