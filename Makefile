NAME	=	RT
OS		=	$(shell uname)

# directories
SRCDIR	= ./src
INCDIR	= ./include
OBJDIR	= ./obj

# sources
SRC		=	main.c \
			event.c \
			lists.c \
			light.c \
			render.c \
			initer.c \
			refract.c \
			sdl_draw.c \
			calc_normal.c \
			image_saver.c \
			event_utility.c \
			light_utility.c \
			check_file.c \
			multithreading.c \
			intersects/intersect_utility.c \
			intersects/intersect_conic.c \
			intersects/intersect_limits.c \
			intersects/intersect_other.c \
			intersects/intersect_limits_flat.c \
			gui/gui.c \
			effects/anti_aliasing.c \
			effects/blur.c \
			effects/sepia.c \
			effects/stereoscopy.c \
			textures/texture_color.c \
			textures/calc_basis.c \
			textures/calc_local_coords.c \
			parser/parser.c \
			parser/parser_validation.c \
			parser/parser_write_surface.c \
			parser/parser_writing_fields.c \
			parser/parser_reading_utility.c \
			parser/parser_open_close_check.c \
			parser/parser_float_fields_check.c \
			parser/parser_other_fields_check.c

OBJ		=	$(addprefix $(OBJDIR)/,$(SRC:.c=.o))

# compiler
CC		=	gcc
CFLAGS	=	-Wall -Wextra #-Werror
# CFLAGS	+=	-Ofast
# CFLAGS	+=	-O0
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

# kiss lib
KISS_LIB	=	$(addprefix $(FT),libkiss.a)
KISS		=	./lib/libkiss/
KISS_INC	=	-I ./lib/libkiss
KISS_LNK	=	-L ./lib/libkiss -lkiss

# sdl lib
ifeq ($(OS), Linux)
SDL_INC	=	-I /usr/include/SDL2
SDL_LNK	=	-L /usr/include/SDL2 -lSDL2_image -lSDL2 -lSDL2_ttf
else
SDL_INC	=	-I ~/.brew/include/SDL2
SDL_LNK	=	-L ~/.brew/lib -lSDL2-2.0.0 -lSDL2_image-2.0.0 -lSDL2_ttf-2.0.0
endif

LNK		=	$(FT_LNK)
LNK		+=	$(VEC_LNK)
LNK		+=	$(KISS_LNK)
LNK		+=	$(SDL_LNK)

INC		=	$(FT_INC)
INC		+=	$(VEC_INC)
INC		+=	$(KISS_INC)
INC		+=	$(SDL_INC)

all: obj $(FT_LIB) $(VEC_LIB) $(KISS_LIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/parser
	mkdir -p $(OBJDIR)/textures
	mkdir -p $(OBJDIR)/effects
	mkdir -p $(OBJDIR)/intersects
	mkdir -p $(OBJDIR)/gui

$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	make -C $(FT)

$(VEC_LIB):
	make -C $(VEC)

$(KISS_LIB):
	make -C $(KISS)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LNK) -lm -o $@

clean:
	rm -rf $(OBJDIR)
	make -C $(FT) clean
	make -C $(VEC) clean
	make -C $(KISS) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean
	make -C $(VEC) fclean
	make -C $(KISS) fclean

cleanobj:
	rm -rf $(OBJDIR)

repair: cleanobj all

re: fclean all
