/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnarvaez <lnarvaez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:18:22 by lnarvaez          #+#    #+#             */
/*   Updated: 2023/07/12 18:18:27 by lnarvaez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_leaks(void)
{
	printf("Leaks\n");
	system("leaks so_long");
}
/*
static int	ft_close(t_game *game)
{

	mlx_destroy_window(game->mlx, game->win);
	return (0);
} */

void	ft_game_init(t_game *game, char *file_path)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx,
			(game->cols * BK_SIZE),
			(game->rows * BK_SIZE),
			"so_long");
	ft_charge_sprite(game, file_path);
	mlx_hook(game->win, 17, 0L, ft_close_esc, game);
	mlx_key_hook(game->win, ft_move, game);
	mlx_loop(game->mlx);
}

void	ft_update_frames(t_player *player)
{
	player->frame = (player->frame + 1) % NUM_FRAMES;
}

void	ft_end_game(t_game *game)
{
	printf("Movimientos: %d\n", game->player.moves);
	printf("Saliendo del juego\n");
	ft_close_esc(game);
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		fd;

	atexit(ft_leaks);
	ft_errors((argc != 2), "Error\n");
	if (argv[0] != 0)
	{
		fd = open(argv[1], O_RDONLY);
		ft_errors((fd < 0), "Error:\n");
		ft_validate_ext(argv[1], ".ber");
		ft_make_map(&game, fd);
		printf("Mapa cargado\n");
		ft_charge_map(&game, argv[1]);
		ft_errors((ft_validate_map(&game)),
			"Error:\nEl mapa no es valido");
		ft_game_init(&game, argv[1]);
		close(fd);
	}
	return (0);
}
