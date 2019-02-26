NAME	= libvec.a

FILES	=	vector.c \
			vector2.c

CFLAGS	= -Wall -Wextra -Werror

OBJ		= $(FILES:.c=.o)

all: $(NAME)

%.o:%.c
	gcc $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
