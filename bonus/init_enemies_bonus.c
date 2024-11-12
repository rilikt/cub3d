/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemies_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:53:58 by timschmi          #+#    #+#             */
/*   Updated: 2024/11/12 15:14:13 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	append_node(t_ai **e, t_point pos, mlx_texture_t **idle,
		mlx_texture_t **dying)
{
	t_ai	*new_node;
	t_ai	*temp;
	static int	id = 1;

	new_node = NULL;
	temp = *e;
	new_node = (t_ai *)malloc(sizeof(t_ai));
	new_node->tex[0] = idle;
	new_node->tex[1] = dying;
	new_node->pos = pos;
	new_node->next = NULL;
	new_node->hp = 100;
	new_node->state = ALIVE;
	new_node->i = 0;
	new_node->hit = 0;
	new_node->dead = 0;
	new_node->id = id++;
	if (!*e)
	{
		*e = new_node;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

mlx_texture_t	**allocate_textures_idle(void)
{
	mlx_texture_t	**idle;
	int				i;

	i = 0;
	idle = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *) * 6);
	idle[0] = mlx_load_png("./include/textures/sprites/idle/tile000.png");
	idle[1] = mlx_load_png("./include/textures/sprites/idle/tile001.png");
	idle[2] = mlx_load_png("./include/textures/sprites/idle/tile002.png");
	idle[3] = mlx_load_png("./include/textures/sprites/idle/tile003.png");
	idle[4] = mlx_load_png("./include/textures/sprites/idle/tile004.png");
	idle[5] = mlx_load_png("./include/textures/sprites/idle/tile005.png");
	while (i < 6)
	{
		err_check(idle[i], "idle texture error\n");
		i++;
	}
	return (idle);
}

mlx_texture_t	**allocate_textures_dying(void)
{
	mlx_texture_t	**dying;
	int				i;

	i = 0;
	dying = (mlx_texture_t **)malloc(sizeof(mlx_texture_t *) * 8);
	dying[0] = mlx_load_png("./include/textures/sprites/dying/dying1.png");
	dying[1] = mlx_load_png("./include/textures/sprites/dying/dying2.png");
	dying[2] = mlx_load_png("./include/textures/sprites/dying/dying3.png");
	dying[3] = mlx_load_png("./include/textures/sprites/dying/dying4.png");
	dying[4] = mlx_load_png("./include/textures/sprites/dying/dying5.png");
	dying[5] = mlx_load_png("./include/textures/sprites/dying/dying6.png");
	dying[6] = mlx_load_png("./include/textures/sprites/dying/dying7.png");
	dying[7] = mlx_load_png("./include/textures/sprites/dying/dying8.png");
	while (i < 8)
	{
		err_check(dying[i], "dying texture error\n");
		i++;
	}
	return (dying);
}

t_ai	*load_alien(t_game *game)
{
	int				count;
	t_point			pos;
	t_ai			*e;
	mlx_texture_t	**idle;
	mlx_texture_t	**dying;

	int x;
	int y;

	x = 0;
	y = 0;

	count = (game->map.map_h * game->map.map_w) / 30;
	game->enemy_count = count;
	e = NULL;
	game->emg = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	idle = allocate_textures_idle();
	dying = allocate_textures_dying();

	while(y < game->map.map_h && count)
	{
		if (x >= game->map.map_w)
		{
			x = 0;
			y++;
		}
		if (y >= game->map.map_h)
		{
			y = 0;
		}
		if(game->map.map[y][x] != 0)
		{
			x++;
			continue;
		}
		pos.x = x + 0.5;
		pos.y = y + 0.5;
		if (sqrt(pow(pos.x - game->player.pos.x, 2.0) + pow(pos.y - game->player.pos.y, 2.0)) > 5.0)
		{
			// printf("%lf\n", mlx_get_time());
			if (rand() % 2 && rand() % 2)
			{
				append_node(&e, pos, idle, dying);
				count--;
				// x += rand() / 2;
				y++;
			}
		}
		x++;
	}

	return (e);
}
