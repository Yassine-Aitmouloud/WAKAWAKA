NAME = so_long
CFLAGS =  -g3
CC = cc

CFILES = main.c get_next_line.c get_next_line_utils.c utils1.c

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

OBJ = $(CFILES:.c=.o)


all: $(NAME)

$(NAME): $(OBJ) so_long.h get_next_line.h
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)


clean:
	rm -f $(OBJ)

fclean: clean
	rm $(OBJ) $(NAME)

re: fclean all 

.PHONY: all clean fclean re
