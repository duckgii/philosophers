NAME = philo
BONUS = philo_bonus
CFLAGS = -Wall -Wextra -Werror -O3

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

MANDATORY_DIR = ./mandatory/
MANDATORY = $(addprefix $(MANDATORY_DIR),$(MANDATORY_SRCS))
MANDATORY_OBJS = $(MANDATORY:.c=.o)

BONUS_SRCS = main_bonus.c

BONUS_DIR = ./bonus/
BONUS_TEMP = $(addprefix $(BONUS_DIR),$(BONUS_SRCS))
BONUS_OBJS = $(BONUS_TEMP:.c=.o)

all : $(NAME)

bonus : $(BONUS)

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

$(BONUS) : $(BONUS_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
