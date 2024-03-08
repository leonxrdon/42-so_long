/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charge_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnarvaez <lnarvaez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:48:38 by lnarvaez          #+#    #+#             */
/*   Updated: 2024/03/05 15:48:44 by lnarvaez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_make_map(t_game *game, int fd)
{
	char	*gnl;
	int		rows;
	int		cols;
	int		i;

	rows = 0;
	cols = 0;
	i = 0;
	gnl = get_next_line(fd);
	while (gnl != NULL)
	{
		printf("gnl: %s", gnl);
		rows++;
		cols = (ft_strlen(gnl) - 1);
		free(gnl);
		gnl = get_next_line(fd);
	}
	game->rows = rows;
	game->cols = cols;
	game->map = (char **)malloc(sizeof(char *) * rows + 1);
	close(fd);
}

char *build_path(char *base_path, int frame_number)
{
    // Suponiendo que ft_strjoin concatena dos cadenas
    char *frame_path;
    char *full_path;

	frame_path = ft_strjoin(base_path, ft_itoa(frame_number));
	full_path = ft_strjoin(frame_path, ".xpm");
    free(frame_path);
    return full_path;
}


//Funcion para cargar el mapa en la estructura
void	ft_load_player(t_game *game)
{
	t_sprite	front;
	t_sprite	left;
	t_sprite	right;
	t_sprite	up;
	t_sprite	down;
	char		*path;
	int		i;

	i = 0;
	while (i < NUM_FRAMES - 1)
	{
		path = build_path("god_", i);
		front = load_texture(game->mlx, path);
		game->player.front[i] = front;
		game->player.front[i].path = path;
		free(path);
		i++;
	}
	i = 0;
	while (i < NUM_FRAMES)
	{
		path = build_path("gk_left_", i);
		right = load_texture(game->mlx, path);
		game->player.right[i] = right;
		game->player.right[i].path = path;
		free(path);
		i++;
	}
	i = 0;
	while (i < NUM_FRAMES)
	{
		path = build_path("gk_right_", i);
		left = load_texture(game->mlx, path);
		game->player.left[i] = left;
		game->player.left[i].path = path;
		free(path);
		i++;
	}
	i = 0;
	while (i < NUM_FRAMES)
	{
		path = build_path("gk_up_", i);
		up = load_texture(game->mlx, path);
		game->player.up[i] = up;
		game->player.up[i].path = path;
		free(path);
		i++;
	}
	i = 0;
	while (i < NUM_FRAMES)
	{
		path = build_path("gk_up_", i);
		down = load_texture(game->mlx, path);
		game->player.down[i] = down;
		game->player.down[i].path = path;
		free(path);
		i++;
	}
}

void	ft_charge_sprite(t_game *game, char *file_path)
{
	char		*gnl;
	int			i;
	int			fd;
	t_sprite	wall;
	t_sprite	collectible;
	t_sprite	exit;
	t_sprite	floor;
	t_sprite	front;

	wall = load_texture(game->mlx, "wall.xpm");
	collectible = load_texture(game->mlx, "ball_0.xpm");
	exit = load_texture(game->mlx, "salida.xpm");
	floor = load_texture(game->mlx, "floor.xpm");
	front = load_texture(game->mlx, "god_1.xpm");
	game->wall = wall;
	game->collectible = collectible;
	game->exit = exit;
	game->floor = floor;
	fd = open(file_path, O_RDONLY);
	gnl = get_next_line(fd);
	i = 0;
	while (gnl != NULL && gnl[0] != '\0' && i < game->rows)
	{
		game->map[i] = *ft_split(gnl, '\n');
		gnl = get_next_line(fd);
		i++;
	}
	ft_load_player(game);
	ft_draw_map(game);
	close(fd);
}

void	ft_charge_map(t_game *game, char *file_path)
{
	char		*gnl;
	int			i;
	int			fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	gnl = get_next_line(fd);
	i = 0;
	while (gnl != NULL && gnl[0] != '\0' && i < game->rows)
	{
		game->map[i] = *ft_split(gnl, '\n');
		gnl = get_next_line(fd);
		i++;
	}
	game->collectibles = 0;
	game->player.moves = 0;
	game->player.frame = 0;
	game->player.action = "front";
}

void	ft_draw_map(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	printf("Movimientos: %d\n", game->player.moves);
	ft_update_frames(&game->player);
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			mlx_put_image_to_window(game->mlx, game->win, game->floor.img, j * BK_SIZE, i * BK_SIZE);
			if (game->map[i][j] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->wall.img, j * BK_SIZE, i * BK_SIZE);
			else if (game->map[i][j] == 'P')
			{
				game->player.x = j * BK_SIZE;
				game->player.y = i * BK_SIZE;
				ft_animation(game);
				//mlx_put_image_to_window(game->mlx, game->win, game->player.front[game->player.frame].img, game->player.x, game->player.y);
			}
			else if (game->map[i][j] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->collectible.img, j * BK_SIZE, i * BK_SIZE);
			else if (game->map[i][j] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->exit.img, j * BK_SIZE, i * BK_SIZE);
			else if (game->map[i][j] == '0')
				mlx_put_image_to_window(game->mlx, game->win, game->floor.img, j * BK_SIZE, i * BK_SIZE);
			else
			{
				printf("Error: Mapa invalido\n");
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
}
