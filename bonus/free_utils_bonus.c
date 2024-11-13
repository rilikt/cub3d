/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:00:42 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/13 14:03:04 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	free_door(void *d)
{
	t_door *p;
	p = (t_door *)d;
	mlx_delete_texture(p->texture);
	free(p);
}

void	free_int_array(int **arr, int h)
{

	if (arr)
	{
		while (--h >= 0)
		{
			free(arr[h]);
		}
		free(arr);
	}
}
void	free_string_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i])
			free(str[i]);
		i++;
	}
	free(str);
}
void	free_indiv(t_tex *t)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (t->arr[i])
			mlx_delete_texture(&(t->side[i]));
	}
}