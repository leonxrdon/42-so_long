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

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

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


typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	char	*path;
	int		rows;
	int		cols;
	t_sprite	player;
	t_sprite	collectible;
	t_sprite	wall;
	t_sprite	exit;
	t_sprite	floor;
}	t_game;

int		move(int keycode, t_vars *vars);
void	mlx_rectangle(void *mlx, void *win, int x, int y, int width, int height, int color);
// void	draw_map(void *mlx, void *win, Map *map, Texture *wall_texture, Texture *user_texture, Texture *coin, Texture *salida);
// Texture	load_texture(void *mlx, char *file_path);

int		ft_validate_ext(char *file_path, char *ext);
void	ft_charge_map(t_game *game);
void	load_texture(t_game *game, char *file_path);
void	load_player(t_game *game);
void	load_collectible(t_game *game);
void	load_exit(t_game *game);
void	load_floor(t_game *game);
void	ft_make_map(t_game *game, int fd);
void	ft_draw_map(t_game *game, t_sprite *wall);
void	ft_game_init(t_game *game);
#endif
