NAME = philosopher
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

SRCS = main.c \
		utile.c

OBJS = $(SRCS:.c=.o)

LIBFT = ./libft/libft.a

all : $(NAME)

make : all

clean :
	rm -f $(OBJS)
	make -C ./libft/ clean

fclean : 
	rm -f $(NAME)
	make -C ./libft/ fclean

re :
	make fclean
	make all

${NAME} : $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(LIBFT) :
	make -C ./libft/ bonus

$(OBJS) : %.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
