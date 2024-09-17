#ifndef CUB_H
#define CUB_H

#define WIDTH 1600
#define HEIGHT 800

#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "include/libft/libft.h"
#include "include/get_next_line/get_next_line.h"
#include "include/MLX42/include/MLX42/MLX42.h"

enum e_identifyers
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	CEILING,
	FLOOR,
};
enum e_action
{
	GET,
	SET,
};

enum e_error
{
	FALSEIDENT = -3,
	DOUBLEIDENT = -2,
	EMPTYLINE = -1,
	NOUGHT,
	MALLOC,
};

typedef struct s_coordinate {
	double	x;
	double	y;
}	t_point;

typedef struct s_player
{
	int height;
	int width;
	t_point pos;
	t_point dir;
	t_point scr;
	double pov;
	int start;
	long color;
}	t_player;

typedef struct s_map
{
	int **map;
	char **str_map;
	int map_h;
	int map_w;
	mlx_texture_t north;
	mlx_texture_t south;
	mlx_texture_t east;
	mlx_texture_t west;
	long ceiling;
	long floor;
	int	start[3];
	int	scale;
} t_map;

typedef struct s_game
{
	mlx_t *mlx;
	mlx_image_t *img;
	t_player player;
	t_map map;
	long	color;
} t_game;


//structure of values needed for putting pixels betwwen two points.
typedef struct s_algorythm {
	int		a;
	int		b;
	int		p;
	int		xdiff;
	int		ydiff;
	int		zdiff;
	int		zstep;
	long	col;
	t_point	p_a;
	t_point	p_b;
	t_point	p_t;
}	t_pixel_line;

/*		draw_line.c			*/
int ft_absolute(int a, int b);
void	draw_line(t_point *p_a, t_point *p_b, t_game *game, int color);

void	raycasting(t_game *game);
void	draw_line(t_point *p_a, t_point *p_b, t_game *game, int color);

/*		main.c				*/
void	grid(t_game *game);
void	draw_player(t_game *game);
int		collision(t_player player, t_game *game, int mod);
void	ft_hook(mlx_key_data_t keydata, void *param);
void	rotate_dir_plane(t_point *dir, t_point *plane, double speed, double l_r);
void	render(void *param);

/*		raycaster.c			*/
void	raycasting(t_game *game);

/*		read_input.c		*/
int		comp_ident(char *str, int *idents);
int		check_identifyer(char *line, int *map_flag);
void	insert_map(t_map *map, char **str, int *map_flag);
void	get_info(int fd, t_map *map);
int		read_input(char **argv, t_player *player, t_map *map);

/*		read_map.c			*/
int		check_line(t_map *map, int x, int y, int i);
int		max_width(char **arr, int *y);
void	validate_map(t_map *map);

/*		error.c				*/
int		error(int e_action, int e_error);
void	err_check(void *p, int e_error);

/*		utils.c				*/
int		arr_len(char **arr);
int		mv_arr(char **src, char **dest);

#endif