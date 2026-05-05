NAME		= philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread

SRC_DIR		= src
INC_DIR		= include

SRCS		= $(SRC_DIR)/main.c \
			  $(SRC_DIR)/init.c \
			  $(SRC_DIR)/time.c \
			  $(SRC_DIR)/utils.c \
			  $(SRC_DIR)/actions.c \
			  $(SRC_DIR)/monitor.c

OBJS		= $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
