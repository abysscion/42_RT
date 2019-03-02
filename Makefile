NAME	=	RT
OS		=	$(shell uname)

# directories
SRCDIR	= ./src
INCDIR	= ./include
OBJDIR	= ./obj

# sources
SRC		=	main.c \
			gui.c \
			freer.c \
			debug.c \
			light.c \
			scener.c \
			initer.c \
			supply.c \
			hooker.c \
			render.c \
			test_0.c \
			test_1.c \
			test_2.c \
			test_3.c \
			test_4.c \
			intersect.c \
			find_normal.c

OBJ		=	$(addprefix $(OBJDIR)/,$(SRC:.c=.o))

# compiler
CC		=	gcc
CFLAGS	=	-g -Ofast -Wall -Wextra #-Werror

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

# mlx lib
ifeq ($(OS), Linux)
MLX 	=	./lib/libmlx/
MLX_LNK	=	-L $(MLX) -lmlx -lXext -lX11 -lOpenCL
else
MLX		=	./lib/libmlx_macos/
MLX_LNK =	-L ./lib/libmlx_macos/ -lmlx $(FWS)
endif
MLX_INC =	-I $(MLX)
MLX_LIB =	$(addprefix $(MLX),mlx.a)

all: obj $(FT_LIB) $(VEC_LIB) $(MLX_LIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(MLX_INC) $(VEC_INC) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	make -C $(FT)

$(VEC_LIB):
	make -C $(VEC)

$(MLX_LIB):
	make -C $(MLX)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_LNK) $(VEC_LNK) $(FT_LNK) -lpthread -lm -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C $(FT) clean
	make -C $(VEC) clean
	make -C $(MLX) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean
	make -C $(VEC) fclean

re: fclean all
