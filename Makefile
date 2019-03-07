NAME	=	RT
OS		=	$(shell uname)

# directories
SRCDIR	= src
INCDIR	= include
OBJDIR	= obj

# PATHS TO SRC SUBDIRECTORIES & NAMES OF SUBDIRECTORIES
SRC_SUBDIR = $(wildcard $(SRCDIR)/*)
SUBDIR = $(SRC_SUBDIR:$(SRCDIR)/%=%)

# PATHS TO C SOURCE FILES
SRC_PATH = $(foreach subdir,$(SRC_SUBDIR),$(wildcard $(subdir)/*.c))

# PATHS TO OBJ SUBDIRECTRIES, PATHS TO & NAMES OF OBJECTS
OBJ_SUBDIR = $(addprefix $(OBJDIR)/,$(SUBDIR))
OBJ_PATH = $(SRC_PATH:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# compiler
CC		=	gcc
CFLAGS	=	-Wall -Wextra
#CFLAGS	+=	-Werror
#CFLAGS	+=	-g
CFLAGS	+=	-Ofast #-O0

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
	mkdir -p $(OBJ_SUBDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(MLX_INC) $(VEC_INC) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	make -C $(FT)

$(VEC_LIB):
	make -C $(VEC)

$(MLX_LIB):
	make -C $(MLX)

$(NAME): $(OBJ_PATH)
	$(CC) $(OBJ_PATH) $(MLX_LNK) $(VEC_LNK) $(FT_LNK) -lpthread -lm -o $(NAME)

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
