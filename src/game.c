/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/15 21:45:47 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/15 21:45:47 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

void	game_init_sdl(t_game *game)
{
	game->sdl.lx = WIN_X;
	game->sdl.ly = WIN_Y;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC) < 0)
		exit(EXIT_FAILURE);
	SDL_CreateWindowAndRenderer(game->sdl.lx,
			game->sdl.ly,
			SDL_WINDOW_SHOWN,
			&(game->sdl.win),
			&(game->sdl.rd));
	game->sdl.tex = SDL_CreateTexture(game->sdl.rd,
			SDL_PIXELFORMAT_RGB888,
			SDL_TEXTUREACCESS_STREAMING,
			game->sdl.lx,
			game->sdl.ly);
	SDL_SetWindowTitle(game->sdl.win, "Wolf3d");
	if (game->sdl.win == NULL)
	{
		printf("Wolf3D: Error windows can't load\n");
		exit(1);
	}
	game->sdl.text_buf = malloc(sizeof(Uint32) * game->sdl.lx * game->sdl.ly);
	if (game->sdl.text_buf == NULL)
	{
		printf("Wolf3D: Error can't allocate buffer\n");
		exit(1);
	}
	if(SDL_NumJoysticks() == 1)
	{
		SDL_JoystickEventState(SDL_ENABLE);
		game->joystick = SDL_JoystickOpen(0);
		game->haptic = SDL_HapticOpenFromJoystick(game->joystick);
		if (SDL_HapticRumbleInit(game->haptic))
				printf("Can not init %s\n", SDL_GetError());
	}
	game_init_sdl_mixer(&game->sounds);
	SDL_SetRelativeMouseMode(1);
}



void	game_draw_rect(t_game *game, Uint32 *buf, int x, int y,int color)
{
	int a = x;
	int b = y;
	t_color	c;

	c.r = color / 0x10000;
	c.g = (color % 0x10000) / 0x100;
	c.b = color % 0x100;
	while (a < (x + 4))
	{
		b = y;
		while (b < (y + 4))
		{
			game_draw_pixel(game, buf, a, b , &c);
			b++;
		}
		a++;
	}
}



void	game_draw_all(t_game *game)
{
	//hud_put(game);
	SDL_UpdateTexture(game->sdl.tex, NULL, game->sdl.text_buf, game->sdl.lx * sizeof(Uint32));
	SDL_RenderCopy(game->sdl.rd, game->sdl.tex, NULL, NULL);
	SDL_RenderPresent(game->sdl.rd);
}

inline void	game_draw_pixel(t_game *game, Uint32 *buf, int x, int y, void *c)
{
	//if (x >= 0 && x < game->sdl.lx && y >=0 && y < game->sdl.ly)
		ft_memcpy(&buf[x + (y * game->sdl.lx)], c, 3);
}

inline void	game_draw_pixel_black(t_game *game, Uint32 *buf, int x, int y, void *c)
{
	t_color color;
	ft_memcpy(&color, c, 3);

	color.r = color.r >> 1;
	color.g = color.g >> 1;
	color.b = color.b >> 1;
	//if (x >= 0 && x < game->sdl.lx && y >=0 && y < game->sdl.ly)
		ft_memcpy(&buf[x + (y * game->sdl.lx)], &color, 3);
}

void	init_ray(t_game *game, t_ray *ray, double camera_x)
{
	ray->pos.x = game->player.pos.x;
	ray->pos.y = game->player.pos.y;

	ray->dir.x = game->player.dir.x + game->player.plane.x * camera_x;
	ray->dir.y = game->player.dir.y + game->player.plane.y * camera_x;

	ray->delta.x = sqrt(1 + (ray->dir.y * ray->dir.y) /
			(ray->dir.x * ray->dir.x));
	ray->delta.y = sqrt(1 + (ray->dir.x * ray->dir.x) /
			(ray->dir.y * ray->dir.y));
}

