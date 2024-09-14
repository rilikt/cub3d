/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:36:56 by timschmi          #+#    #+#             */
/*   Updated: 2024/09/14 17:38:05 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void grid(t_game *game)
{
	int x = 0;
	int y = 0;

	game->map = (int**)malloc(sizeof(int*) * 10);
	while (x < 10)
	{
		game->map[x] = (int*)malloc(sizeof(int) * 10);
		x++;
	}

	int arr[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	x = 0;
	while (x < 10)
	{
		y = 0;
		while (y < 10)
		{
			game->map[x][y] = arr[x][y];
			y++;
		}
		x++;
	}

	x = 0;
	y = 0;

	while (x < 10)
	{
		y = 0;
		while (y < 10)
		{
			int arr_x = x * 80;
			int arr_y = y * 80;

			while (arr_x < (x * 80 + 80))
			{
				arr_y = y * 80;
				while (arr_y < (y * 80 + 80))
				{
					if ((arr_x == x * 80 || arr_y == y * 80) || (arr_x == 799 || arr_y == 799)) // if the current pixel is in the border of the block or the edges of our window its painted black to create a grid layout
						mlx_put_pixel(game->img, arr_x, arr_y, 0x000000FF);
					else if (game->map[x][y] == 1)
						mlx_put_pixel(game->img, arr_x, arr_y, 0xD3D3D3FF);
					else
						mlx_put_pixel(game->img, arr_x, arr_y, 0x808080FF);
					arr_y++;
				}
				arr_x++;
			}
			y++;
		}
		x++;
	}
}

void draw_player(mlx_image_t *img, t_player *player)
{
	int x = (int)player->pos.x - 10;
	int y = (int)player->pos.y - 10;
	int size_x = 0;
	int size_y = 0;

	while (size_x < 20)
	{
		y = (int)player->pos.y - 10;
		size_y = 0;
		while (size_y < 20)
		{
			mlx_put_pixel(img, x, y, 0xFFFF00FF);
			y++;
			size_y++;
		}
		x++;
		size_x++;
	}
}

int collision(t_player player, t_game *game, int mod)
{
	double x;
	double y;
	double px = player.pos.x;
	double py = player.pos.y;
	if (mod == 1)
	{
		x = ((px + 10) / 80);
		y = ((py) / 80);
	}
	else if (mod == 2)
	{
		x = ((px - 10) / 80) -0.001;
		y = ((py) / 80);
	}
	else if (mod == 3)
	{
		x = ((px) / 80);
		y = ((py + 10) / 80);
	}
	else if (mod == 4)
	{
		x = ((px) / 80);
		y = ((py - 10) / 80) - 0.001;
	}
	int ix = (int)floor(x);
	int iy = (int)floor(y);
	// printf("player: x: %f y: %f, index: x: %d y: %d\n", player.pos.x, player.pos.y, ix, iy);
	if (game->map[ix][iy] == 1)
		return(0);
	return (1);
}

void ft_hook(mlx_key_data_t keydata, void *param)
{
	t_game *game;

	game = (t_game*)param;

	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (collision(game->player, game, 4))
			game->player.pos.y -= 5;
	}
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (collision(game->player, game, 3))
			game->player.pos.y += 5;
	}
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (collision(game->player, game, 1))
			game->player.pos.x += 5;
	}
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		if (collision(game->player, game, 2))
			game->player.pos.x -= 5;
	}
}

void render(void *param)
{
	t_game *game;

	game = (t_game*)param;
	grid(game);
	draw_player(game->img, &game->player);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	usleep(1000);
}


int main(void)
{
	t_game game;

	game.player.pos.x = 120;
	game.player.pos.y = 120;
	game.player.height = HEIGHT;
	game.player.width = WIDTH;
	game.player.colour = 0x6cf542ff;

	game.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);

	mlx_key_hook(game.mlx, &ft_hook, (void*)&game);
	mlx_loop_hook(game.mlx, render, (void*)&game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
