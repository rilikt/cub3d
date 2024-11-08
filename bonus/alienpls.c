/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alienpls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:00:03 by timschmi          #+#    #+#             */
/*   Updated: 2024/11/08 13:46:35 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	swap(t_ai **head)
{
	t_ai	*first;
	t_ai	*second;

	first = *head;
	second = (*head)->next;
	first->next = second->next;
	second->next = first;
	*head = second;
}

void sort_ai(t_ai **enemy)
{
	t_ai **temp = enemy;

	while((*temp)->next)
	{
		if ((*temp)->next->dist > (*temp)->dist)
		{
			swap(temp);
			temp = enemy;
		}
		else
			temp = &(*temp)->next;
	}
}

void render_sprite(t_game *game, t_enemy_var i, t_ai *e)
{
	while (i.line < i.endx && i.proj.y > 0)
	{
		i.tex.tex.x = e->tex[e->state][e->i]->width * ((double)(i.line - i.startx) / i.swidth);	
		i.y = i.starty;
		if (i.y < 0)
			i.y = 0;
		while(i.y < i.endy && i.proj.y < game->dist_arr[i.line])
		{
			i.tex.tex.y = (double)(i.y - i.starty) * i.tex.step;
			i.tex.arr_pos = ((int)i.tex.tex.y * e->tex[e->state][e->i]->width + (int)i.tex.tex.x) * 4;
			i.tex.tex_pos = &e->tex[e->state][e->i]->pixels[i.tex.arr_pos];
			i.tex.pic_pos = (i.y * game->img->width + i.line) * 4;
			i.tex.img_pos = &game->img->pixels[i.tex.pic_pos];
			i.tex.test = darken_colour(*(u_int32_t *)i.tex.tex_pos, i.proj.y * 15);
			if (i.tex.test != 0)
			{
				if (e->hit)
					*(uint32_t *)i.tex.img_pos = 0xFF0000FF;
				else
					*(uint32_t *)i.tex.img_pos = i.tex.test;
			}
			i.y++;
		}
		i.line++;
	}
}

void enemy_calc(t_game *game, t_enemy_var *i, t_ai *e)
{
	i->s.x = (e->pos.x - game->player.pos.x);
	i->s.y = (e->pos.y - game->player.pos.y);
	
	i->invcam = 1.0 / ((game->player.scr.x * 10) * (game->player.dir.y * 10) - (game->player.dir.x * 10) * (game->player.scr.y * 10));

	i->proj.x = i->invcam * ((game->player.dir.y * 10) * i->s.x - (game->player.dir.x * 10) * i->s.y);
	i->proj.y = i->invcam * ((-game->player.scr.y * 10) * i->s.x + (game->player.scr.x * 10) * i->s.y);

	i->height_offset = (int)((0.1 - 0) / i->proj.y * HEIGHT);

	i->spritescrx = (int)((WIDTH / 2) * (1 + i->proj.x / i->proj.y));

	i->sheight = abs((int)(HEIGHT / i->proj.y));
	i->starty = (-i->sheight) / 2 + HEIGHT / 2 + i->height_offset - game->y;
	i->endy = i->sheight / 2 + HEIGHT / 2 + i->height_offset - game->y;
	if (i->endy >= HEIGHT)
		i->endy = HEIGHT;
	
	i->swidth = abs((int)(HEIGHT / i->proj.y));
	i->startx = (-i->swidth) / 2 + i->spritescrx;
	i->endx = i->swidth / 2 + i->spritescrx;
	if (i->endx >= WIDTH)
		i->endx = WIDTH;
}

void hit_check(t_game *game, t_enemy_var i, t_ai *e)
{
	if (e->state == ALIVE && (WIDTH/2 >= i.startx && WIDTH/2 <= i.endx) && (HEIGHT/2 >= i.starty && HEIGHT/2 <= i.endy) && game->player.attack == 1 && i.proj.y > 0.0)
	{
		e->hp -= 50; // actual damage dealt
		e->hit = 1;
		if (e->hp <= 0)
		{
			e->state = DYING;
			e->i = 0;
		}
	}
}

void draw_sprites(t_game *game, t_ai *enemy, int frame)
{
	t_ai *e = enemy;
	t_enemy_var i;

	e = enemy;
	while(e)
	{
		if (e->state == ALIVE)
			e->i = frame / 6;
		else if (frame % 5 == 0 && e->i < 7)
			e->i += 1;
		
		enemy_calc(game, &i, e);
		hit_check(game, i, e);

		i.line = i.startx;
		if (i.startx < 0)
			i.line = 0;
		i.tex.step = 1.0 * e->tex[e->state][e->i]->height / i.sheight;
		render_sprite(game, i, e);
		e->hit = 0;
		e = e->next;
	}
}

void game_over_check(t_game *game)
{
	int x; 
	int y;

	x = 0;
	if (game->player.hp > 0)
		return;
	
	mlx_texture_t *end = mlx_load_png("./include/textures/GAME_OVER.png");
	mlx_image_t *go = mlx_texture_to_image(game->mlx, end);
	mlx_image_t *black = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			mlx_put_pixel(black, x, y, 0x000000FF);
			y++;
		}
		x++;
	} 
	mlx_image_to_window(game->mlx, black, 0, 0);
	mlx_image_to_window(game->mlx, go, 180, 100);
	game->over = 1;
}

void enemy_dist(t_game *game, t_ai **enemy, int frame)
{
	t_ai *e;
	t_point p;
	t_point len;

	e = *enemy;
	p = game->player.pos;
	while(e)
	{
		len.x = fabs(e->pos.x - p.x);
		len.y = fabs(e->pos.y - p.y);
		
		e->dist = sqrt(pow(len.x, 2.0) + pow(len.y, 2.0));
		if (e->state == ALIVE && e->dist <= 0.5 && game->player.hp > 0)
		{
			game->player.hp -= 5;
			health_bar(game);
			game_over_check(game);
		}
		e = e->next;
	}
	sort_ai(enemy);
	draw_sprites(game, *enemy, frame);
}
