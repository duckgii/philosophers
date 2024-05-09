NAME = philosopher
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=thread

SRCS = main.c \
		thread_function.c \
		thread_utile.c \
		init.c \
		monitoring.c \
		check_in_mutex.c \
		free.c \
		philo_status.c

OBJS = $(SRCS:.c=.o)

LIBFT = ../libft/libft.a

all : $(NAME)

make : all

clean :
	rm -f $(OBJS)
	make -C ../libft/ clean

fclean : 
	make clean
	rm -f $(NAME)
	make -C ../libft/ fclean

re :
	make fclean
	make all

${NAME} : $(LIBFT) $(OBJS)
	$(CC) -o  $@ $^

$(LIBFT) :
	make -C ../libft/ bonus

$(OBJS) : %.o : %.c
	$(CC) $(INCLUDE) -c $< -o $@
