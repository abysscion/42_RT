NAME	=	RT
OS		=	$(shell uname)

# directories
SRCDIR	= ./src
INCDIR	= ./include
OBJDIR	= ./obj

# sources
SRC		=	main.c \
			ft_atod.c \
			light.c \
			calc_normal.c \
			initer.c \
			render.c \
			intersect.c \
			intersect_utility.c \
			light_utility.c \
			parser.c \
			parser_validation.c \
			parser_utility.c \
			lists.c \
			key_events.c \
			anti_aliasing.c \
			textures.c \
			refract.c
			#gui_initer.c \
			#gui_supply.c \
			#gui_handler.c \
			gui.c \


OBJ		=	$(addprefix $(OBJDIR)/,$(SRC:.c=.o))

# compiler
CC		=	gcc
CFLAGS	=	-Wall -Wextra #-Werror
CFLAGS	+=	-Ofast
#CFLAGS	+=	-g

#OSX frameworks
FWS		=	-framework OpenCL -framework OpenGL -framework AppKit

# ft lib
FT_LIB	=	$(addprefix $(FT),libft.a)
FT		=	./lib/libft/
FT_INC	=	-I ./lib/libft
FT_LNK	=	-L ./lib/libft -lft

# vec lib
VEC_LIB	=	$(addprefix $(VEC),libvec.a)
VEC		=	./lib/libvec/
VEC_INC	=	-I ./lib/libvec
VEC_LNK	=	-L ./lib/libvec -lvec

# sdl lib
ifeq ($(OS), Linux)
SDL_INC	=	-I /usr/include/SDL2
SDL_LNK	=	-L /use/include/SDL2 -lSDL2_image -lSDL2
else
SDL_INC	=	-I ~/.brew/include/SDL2
SDL_LNK	=	-L ~/.brew/lib -lSDL2-2.0.0 -lSDL2_image-2.0.0
endif

all: obj $(FT_LIB) $(VEC_LIB) $(MLX_LIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(SDL_INC) $(VEC_INC) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	make -C $(FT)

$(VEC_LIB):
	make -C $(VEC)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(SDL_LNK) $(VEC_LNK) $(FT_LNK) -lpthread -lm -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C $(FT) clean
	make -C $(VEC) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean
	make -C $(VEC) fclean

re: fclean all
