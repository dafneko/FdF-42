/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:53:24 by dkoca             #+#    #+#             */
/*   Updated: 2024/03/18 19:51:24 by dkoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	img_init(t_fdf *fdf)
{
	fdf->img = mlx_new_image(fdf->mlx_ptr, IMG_WIDTH, W_HEIGHT);
	if (!fdf->img)
		(error_handler(MLX_ERROR), close_mlx(fdf));
	fdf->img_data = malloc(sizeof(t_img_data));
	if (!fdf->img_data)
		(error_handler(ENOMEM), close_mlx(fdf));
	fdf->img_data->addr = mlx_get_data_addr(fdf->img, &fdf->img_data->bpp,
			&fdf->img_data->line_len, &fdf->img_data->endian);
	return (0);
}

int	menu_init(t_fdf *fdf)
{
	fdf->menu = mlx_new_image(fdf->mlx_ptr, MENU_WIDTH, MENU_HEIGHT);
	if (!fdf->menu)
		(error_handler(MLX_ERROR), close_mlx(fdf));
	fdf->menu_data = malloc(sizeof(t_img_data));
	if (!fdf->menu_data)
		(error_handler(MLX_ERROR), close_mlx(fdf));
	fdf->menu_data->addr = mlx_get_data_addr(fdf->menu, &fdf->menu_data->bpp,
			&fdf->menu_data->line_len, &fdf->menu_data->endian);
	return (EXIT_SUCCESS);
}

t_fdf	*fdf_init(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	if (!fdf->mlx_ptr)
		(close_mlx(fdf), error_handler(MLX_ERROR));
	fdf->window = mlx_new_window(fdf->mlx_ptr, W_WIDTH, W_HEIGHT, "Fil de Fer");
	if (!fdf->window)
		(error_handler(MLX_ERROR), close_mlx(fdf));
	img_init(fdf);
	cam_init(fdf);
	set_cam(fdf);
	menu_init(fdf);
	return (fdf);
}

int	main(int ac, char **av)
{
	t_fdf	*fdf;

	if (ac != 2)
		return (EXIT_FAILURE);
	fdf = ft_calloc(1, sizeof(t_fdf));
	if (!fdf)
		(error_handler(INIT_ERROR), close_mlx(fdf));
	if (check_fd(av[1], fdf) == -1)
		(error_handler(MAP_ERROR), close_mlx(fdf));
	parse_map(fdf->path, fdf);
	fdf_init(fdf);
	call_hooks(fdf);
	mlx_loop(fdf->mlx_ptr);
	return (0);
}
