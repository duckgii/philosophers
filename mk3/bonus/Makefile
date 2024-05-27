NAME = philo_bonus
CFLAGS = -Wall -Wextra -Werror

BONUS_SRCS = main_bonus.c \
			parse.c \
			utile_bonus.c \
			child_main_bonus.c \
			child_status_bonus.c \
			child_utile_bonus.c \
			ft_strncmp_bonus.c \
			child_print_bonus.c

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all : $(NAME)

make : all

clean :
	rm -f $(BONUS_OBJS)

fclean : 
	make clean
	rm -f $(NAME)

re :
	make fclean
	make all

$(NAME) : $(BONUS_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
