
SRCS =	pipex.c \
	pipex_utils.c \

AR = ar rcs
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror
NAME = pipex
OBJS = $(SRCS:.c=.o)
LIBFT = Libft/libft.a

.c.o:
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS) $(LIBFT)
	$(AR) $(NAME) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)
	make clean -C Libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C Libft

re: fclean all

.PHONY: all clean fclean re