NAME = philosopher
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

SRCS = main.c \
		thread_function.c \
		thread_utile.c \
		init.c \
		monitoring.c

OBJS = $(SRCS:.c=.o)

LIBFT = ./libft/libft.a

all : $(NAME)

make : all

clean :
	rm -f $(OBJS)
	make -C ./libft/ clean

fclean : 
	make clean
	rm -f $(NAME)
	make -C ./libft/ fclean

re :
	make fclean
	make all

${NAME} : $(LIBFT) $(OBJS)
	$(CC) -o  $@ $^

$(LIBFT) :
	make -C ./libft/ bonus

$(OBJS) : %.o : %.c
	$(CC) $(INCLUDE) -c $< -o $@
