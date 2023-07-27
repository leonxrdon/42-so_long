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

#include <mlx.h>
#include <stdio.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int	bits_x_pixel;
	int	line_length;
	int	endian;
}	t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_x_pixel / 8));
	*(unsigned int*)dst = color;
}


int	main(void)
{

	void	*mlx;
	void	*mlx_win;
	t_data	img;
	char	*relative_path = "./mario.xpm";
	int		img_width;
	int		img_height;


	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 500, 500, "so_long");
	// Crear una nueva imagen
	img.img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
	// Get data Address
	img.addr = mlx_get_data_addr(img.img, &img.bits_x_pixel, &img.line_length, &img.endian);
	// Insertar pixeles
	my_mlx_pixel_put(&img, 225, 225, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

	mlx_loop(mlx);

}
