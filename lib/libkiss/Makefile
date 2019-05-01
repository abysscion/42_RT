NAME	= libkiss.a
OS		=	$(shell uname)

FILES	=	kiss_draw.c \
			kiss_general.c \
			kiss_posix.c \
			kiss_widgets.c

CFLAGS	= -Wall -Wextra

ifeq ($(OS), Linux)
SDL_INC	=	-I /usr/include/SDL2
else
SDL_INC	=	-I ~/.brew/include/SDL2
endif

OBJ		= $(FILES:.c=.o)

all: $(NAME)

%.o:%.c
	gcc $(CFLAGS) $(SDL_INC) -o $@ -c $<

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

