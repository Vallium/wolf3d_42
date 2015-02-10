/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 16:55:44 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/13 16:55:46 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

struct timeval tv1;
struct timeval tv2;

void	setdt(t_game *game)
{
	tv2 = tv1;
	gettimeofday(&tv1, NULL);
	game->dt = ((tv1.tv_sec - tv2.tv_sec) +
	((tv1.tv_usec - tv2.tv_usec) / 1000000.0));
}

int		main(int ac, char **av)
{
	t_game	game;
	char	*fps;
	int		i;

	game.dt = 0;
	game_init_sdl(&game);
	if (ac == 2)
		map_init(&game, 1, ft_atoi(av[1]));
	else
		map_init(&game, 1, 2);
	i = ((GAME_LY) / 2) - 1;
	SDL_UpdateTexture(game.sdl.tex, NULL, game.sdl.text_buf,
			game.sdl.lx * sizeof(Uint32));
	SDL_RenderCopy(game.sdl.rd, game.sdl.tex, NULL, NULL);
	SDL_RenderPresent(game.sdl.rd);
	while (i++ < (GAME_LY) - 1)
		game.calcule[(i) - (GAME_LY / 2)] = (GAME_LY) / (2.0 * (i) - (GAME_LY));
	while (42)
	{
		setdt(&game);
		while (game_event_handler(&game))
			;
		player_update(&game.player, &game);
		game_render(&game);
		hud_render(&game);
		game_draw_all(&game);
		fps = ft_itoa(1/game.dt);
		SDL_SetWindowTitle(game.sdl.win, fps); // // //
		free(fps);
	}
	return (0);
}
