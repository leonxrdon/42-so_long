/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnarvaez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:56:03 by lnarvaez          #+#    #+#             */
/*   Updated: 2023/11/30 16:56:05 by lnarvaez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <mlx.h>
#include <stdio.h>
#include <fcntl.h>
#include "../libft/libft.h"

# define XPM_ROUTE		"./texturas/"
# define NUM_FRAMES		3
# define FRAME_DELAY_US	100000

typedef struct {
	char **map;
	int rows;
	int cols;
} Map;

typedef struct s_sprite
{
	void	*img;
	char	*path;
	int		width;
	int		height;
}	t_sprite;


typedef struct s_player
{
	int		x;
	int		y;
	int		moves;
	char	*action;
	int		frame;
	t_sprite	front[NUM_FRAMES];
	t_sprite	left;
	t_sprite	right[NUM_FRAMES];
	t_sprite	up;
	t_sprite	down;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	char		*path;
	int			rows;
	int			cols;
	int			collectibles;
	t_player	player;
	t_sprite	collectible;
	t_sprite	wall;
	t_sprite	exit;
	t_sprite	floor;
}	t_game;

int		ft_move(int keycode, t_game *game);
void	ft_player_move(t_game *game, int i, int j, int x, int y);

int		ft_validate_ext(char *file_path, char *ext);
void	ft_charge_map(t_game *game, char *file_path);
t_sprite	load_texture(void *mlx, char *file_path);
void	ft_make_map(t_game *game, int fd);
void	ft_draw_map(t_game *game);
void	ft_game_init(t_game *game, int fd, char *file_path);

void	ft_load_player(t_game *game);
void	ft_animation(t_game *game);
void	ft_update_frames(t_player *player);
char *build_path(char *base_path, int frame_number);
#endif
