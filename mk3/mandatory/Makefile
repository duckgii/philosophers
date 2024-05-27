NAME = philo
CFLAGS = -Wall -Wextra -Werror

MANDATORY_SRCS = main.c \
		free.c \
		free2.c \
		ft_atoi.c \
		ft_strncmp.c \
		init_info.c \
		init_one_philo.c \
		init_philo_array.c \
		thread_main.c \
		thread_status.c \
		thread_utile.c \
		thread_utile2.c \
		thread_mutex_print.c

MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)

all : $(NAME)

make : all

clean :
	rm -f $(MANDATORY_OBJS)

fclean : 
	make clean
	rm -f $(NAME)

re :
	make fclean
	make all

${NAME} : $(MANDATORY_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
