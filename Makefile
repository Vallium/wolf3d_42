# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/06 10:11:24 by aalliot           #+#    #+#              #
#*   Updated: 2015/02/05 22:37:42 by aalliot          ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

STATIC_EXE	= wolf3d
DEBUG_EXE	= wolf3d_debug

SRC		=	main.c		\
			game.c		\
			player.c	\
			vect.c		\
			map.c		\
			sound.c		\
			hud.c		\
			weapon.c	\
			sprites.c	\
			joystick.c	\
			keyboard.c	\
			render.c	\
			pixel.c		\
			map_dlc.c	\
			caster.c

##HEADFILES = wolf3d.h

HEAD_DIR	= includes
SRC_DIR		= src
DEBUG_DIR	= debug
STATIC_DIR	= static
C_HEAD_DIR	= debug

LIBFT_STATIC= libft/libft.a
LIBFT_DEBUG	= libft/libft_debug.a
LIBFT_HEAD	= libft/includes/

STATIC_OBJ	= $(patsubst %.c,$(STATIC_DIR)/%.o,$(SRC))
DEBUG_OBJ	= $(patsubst %.c,$(DEBUG_DIR)/%.o,$(SRC))

CC		= gcc
NORMINETTE	= ~/project/colorminette/colorminette
OPTI		= -O3

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	SDL	= -lSDL2 -lm -lSDL_mixer
	FLAGS	= -Wall -Wextra
endif

ifeq ($(UNAME_S),Darwin)
	SDL	= -F ~/Library/Frameworks -I ~/Library/Frameworks/SDL2.framework/Headers/ -framework SDL2 -I ~/Library/Frameworks/SDL2_mixer.framework/Headers -framework SDL2_mixer	
	FLAGS	= -Wall -Wextra -Werror
endif

$(shell mkdir -p $(STATIC_DIR) $(DEBUG_DIR))

all: $(STATIC_EXE)
	@echo "Compilation terminee. (realease)"
debug: $(DEBUG_EXE)
	@echo "Compilation terminee. (debug)"
$(DEBUG_EXE): $(DEBUG_OBJ) $(LIBFT_DEBUG)
	$(CC) -O0 -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $(DEBUG_EXE) $(DEBUG_OBJ) $(LIBFT_DEBUG) $(SDL) $(FLAGS) -g

$(STATIC_EXE): $(STATIC_OBJ) $(LIBFT_STATIC)
	$(CC) $(OPTI) -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $@ $(STATIC_OBJ) $(LIBFT_STATIC) $(SDL) $(FLAGS)

$(STATIC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(OPTI) -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $@ -c $< $(SDL) $(FLAGS)

$(DEBUG_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -O0 -I $(HEAD_DIR) -I $(LIBFT_HEAD) -o $@ -c $< $(SDL) $(FLAGS) -g

$(LIBFT_STATIC):
	make -C libft/ libft.a

$(LIBFT_DEBUG):
	make -C libft/ libft_debug.a

.PHONY: clean fclean re debug normem sdl_install

clean:
	rm -f $(STATIC_OBJ) $(DEBUG_OBJ)
	make -C libft clean

fclean: clean
	rm -f $(STATIC_EXE) $(DEBUG_EXE)
	make -C libft fclean

norme:
	$(NORMINETTE) $(SRC_DIR)/ $(HEAD_DIR)/
	make -C libft norme

sdl_install:
	curl https://dl.dropboxusercontent.com/u/22561204/SDL/Archive.zip > /tmp/Archive.zip
	unzip -o /tmp/Archive.zip -d ~/Library/Frameworks/

re: fclean
	make
