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

# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>
# include "../libft/libft.h"

# define XPM_ROUTE		"./xpm/"
# define BK_SIZE		50

# define KEY_ESC	53
# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_UP		126
# define KEY_DOWN	125
# define KEY_LEFT	123
# define KEY_RIGHT	124

typedef struct s_sprite
{
	void	*img;
	int		width;
	int		height;
}	t_sprite;


typedef struct s_player
{
	int			x;
	int			y;
	int			moves;
	t_sprite	sprite;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	char		**matriz_aux;
	char		*path;
	int			rows;
	int			cols;
	int			collectibles;
	int			exit_x;
	int			exit_y;
	t_sprite	wall;
	t_player	player;
	t_sprite	collectible;
	t_sprite	exit;
	t_sprite	floor;
}	t_game;

int			ft_move(int keycode, t_game *game);
void		ft_player_move(t_game *game, int x, int y);

void		ft_errors(bool if_error, char *str);

int			ft_validate_lines(t_game *game, char **matriz_aux);
void		ft_validate_ext(char *file_path, char *ext);
void		ft_validate_rectangle(t_game *game, char **matriz_aux);
void		ft_validate_border(t_game *game, char **matriz_aux);
int			ft_player_inmap(t_game *game, char **matriz_aux);
int			ft_exit_inmap(t_game *game, char **matriz_aux);
int			ft_collect_inmap(t_game *game, char **matriz_aux);
void		ft_validate_objects(t_game *game, char **matriz_aux);
int			ft_browse_map(t_game *game, char **matriz_aux, int row, int col);
void		ft_check_browse(t_game *game, char **matriz_aux);
int			ft_validate_map(t_game *game);

int			ft_close_esc(t_game *game);
void		ft_free_map(char **map, int rows);
void		ft_free_matriz(t_game *game);
void		ft_free_img(t_game *game);

void		ft_charge_map(t_game *game, char *file_path);
void		ft_charge_wall(t_game *game, int i, int j);
void		ft_charge_sprite(t_game *game, char *file_path);
void		ft_make_map(t_game *game, int fd);
void		ft_draw_map(t_game *game);
void		ft_game_init(t_game *game, char *file_path);
t_sprite	ft_load_texture(void *mlx, char *file_path);
void		ft_load_extras(t_game *game);
void		ft_load_player(t_game *game);
void		ft_animation(t_game *game);

void		ft_end_game(t_game *game);

#endif
