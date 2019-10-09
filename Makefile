# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/13 16:05:39 by fchevrey          #+#    #+#              #
#    Updated: 2019/10/09 15:16:15 by jules            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42run

## Colors ##
PURPLE = [038;2;255;40;255
GREEN = [038;2;82;255;123
CYAN = [038;2;0;255;255
PINK = [038;2;255;0;137
YELLOW = [038;2;252;125;91
ORANGE = [038;2;239;138;5

## Sources ##
SRCS_DIR = srcs

SRCS =  main.cpp  Player.cpp GameManager.cpp Obstacle.cpp RoomManager.cpp \

HEADER = Player.hpp GameManager.hpp Obstacle.hpp RoomManager.hpp \

## Objects ##
OBJS = $(SRCS:.cpp=.o)
OBJS_DIR = ./objs
OBJS_PRE = $(addprefix $(OBJS_DIR)/, $(OBJS))

## Lib dirs ##
LIB_DIR = ./lib
ENGINE_LIB_DIR = /GameEngine/lib

## Macros for extern library installation ##
SDL_VER = 2.0.9
SDL_MIXER_VER = 2.0.2
ASSIMP_VER = 4.1.0
FREETYPE_VER = 2.10.0

MAIN_DIR_PATH = $(shell pwd)
SDL_PATH = $(addprefix $(MAIN_DIR_PATH), $(ENGINE_LIB_DIR)/sdl2)
SDL_MIXER_PATH = $(addprefix $(MAIN_DIR_PATH), $(ENGINE_LIB_DIR)/sdl2_mixer)
GLAD_PATH = $(addprefix $(MAIN_DIR_PATH), $(ENGINE_LIB_DIR)/glad)
GLM_PATH = $(addprefix $(MAIN_DIR_PATH), $(ENGINE_LIB_DIR)/glm)
ASSIMP_PATH = $(addprefix $(MAIN_DIR_PATH), $(ENGINE_LIB_DIR)/assimp-$(ASSIMP_VER))
FREETYPE_PATH = $(addprefix $(MAIN_DIR_PATH), $(ENGINE_LIB_DIR)/freetype-$(FREETYPE_VER))

#IRRXML_PATH = $(addprefix $(ASSIMP_PATH), /build/contrib/irrXML)

HEADER_DIR = includes/

## Includes ##
INC = -I ./$(HEADER_DIR)

SDL2_INC = $(shell sh ./$(ENGINE_LIB_DIR)/sdl2/bin/sdl2-config --cflags)

LIB_INCS =	-I $(GLM_PATH)/glm \
			$(SDL2_INC) \
			-I $(SDL_MIXER_PATH)/include/SDL2 \
			-I $(ASSIMP_PATH)/include/ \
			-I $(GLAD_PATH)/includes/ \
			-I $(FREETYPE_PATH)/include \
			-I GameEngine/includes/


HEADERS = $(addprefix $(HEADER_DIR), $(HEADER))

INCS = $(INC) $(LIB_INCS)

## FLAGS ##
CC = clang++

SDL2_LFLAGS = $(shell sh ./$(ENGINE_LIB_DIR)/sdl2/bin/sdl2-config --libs)

LFLAGS =	$(GLAD_PATH)/glad.o\
			-L $(ASSIMP_PATH)/lib -lassimp\
			$(SDL2_LFLAGS) \
			-L $(SDL_MIXER_PATH)/lib/ -lSDL2_mixer \
			-L $(FREETYPE_PATH)/build -L ~/.brew/lib/ -lfreetype -lbz2 -lpng -lz \
			-L GameEngine/ -lGameEngine

LDFLAGS = "-Wl,-rpath,GameEngine/lib/assimp-4.1.0/lib"	


FRAMEWORK = -framework Carbon -framework OpenGL -framework IOKit -framework CoreVideo
#FRAMEWORK = -lGL -ldl #-lGLU #-lglut
#FRAMEWORK = -framework Carbon -framework OpenGL -framework IOKit -framework CoreVideo -lglfw

CFLAGS = -Wall -Wextra -Werror -std=c++11 -Wno-unknown-pragmas

MESSAGE = "make[1]: Nothing to be done for 'all'"
DONE_MESSAGE = "\033$(GREEN)2m✓\t\033$(GREEN)mDONE !\033[0m\
				\n ========================================\n"

## RULES ##

all: GAME_ENGINE print_name $(NAME) print_end

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp $(HEADERS)
	@echo "\033$(PURPLE)m⧖	Creating	$@\033[0m"
	@export PKG_CONFIG_PATH=$(PKG_CONFIG_PATH):$(addprefix $(SDL_PATH), /lib/pkgconfig) &&\
	$(CC) -c -o $@ $< $(CFLAGS) $(INCS)

$(OBJS_DIR):
	@echo "\033$(CYAN)m➼	\033$(CYAN)mCreating $(NAME)'s objects \
	with flag : \033$(GREEN)m $(CFLAGS)\033[0m"
	@mkdir -p $(OBJS_DIR)

GAME_ENGINE:
	make -C GameEngine;

$(NAME): $(OBJS_DIR) $(OBJS_PRE) $(HEADERS) 
	@echo "\033$(GREEN)m➼\t\033$(GREEN)32m Creating $(NAME)'s executable\033[0m"
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJS_PRE) $(LFLAGS) $(LDFLAGS) $(FRAMEWORK)
	@$(eval MESSAGE = $(DONE_MESSAGE))

set_linux :
	$(eval FRAMEWORK = -lGL -ldl)

linux : set_linux all

linux_re: set_linux re

rm_obj:
	@rm -rf $(OBJS_DIR)
	@echo "\033$(PINK)36m✗	\033[0m\033$(PINK)31m$(NAME)'s object removed\033[0m"

clean: rm_obj

fclean: rm_obj clean
	@rm -rf $(NAME)
	@echo "\033$(PINK)36m✗	\033[0m\033$(PINK)31m$(NAME) removed\033[0m"

re: fclean all

exe: rm_obj all

MODE_DEBUG: change_cflag all

re_sanitize: rm_obj MODE_DEBUG

sanitize:
	@$(eval CFLAGS = -fsanitize=address)

print_name:
	@echo "\033[033m➼\t\033[033mCompiling $(NAME) ...\033[0m"

print_end:
	@echo $(MESSAGE)
.PHONY: all clean fclean re rm_obj exe re_sanitize sanitize
