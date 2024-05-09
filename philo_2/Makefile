NAME = philosopher
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

SRCS = main.c \
		free.c \
		free2.c \
		init.c \
		init2.c \
		thread_start.c \
		utile.c \
		utile2.c \
		utile3.c \

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
	$(CC) -o $@ $^

$(LIBFT) :
	make -C ../libft/ bonus

$(OBJS) : %.o : %.c
	$(CC) $(INCLUDE) -c $< -o $@
