NAME = philosopher
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c \
		utile.c

OBJS = $(SRCS:.c=.o)

LIBFT = ./libft/libft.a

all : $(NAME)

make : all

clean :
	rm -f $(OBJS)
	make -c ./libft/ clean

fclean : 
	rm -f $(NAME)
	make -c ./libft/ fclean

${NAME} : $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(LIBFT) :
	make -c ./libft/ bonus

$(OBJS) : %.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
