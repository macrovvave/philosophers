CC = cc
CFLAGS = -Wall -Wextra -Werror -ggdb
NAME = philo

SRC = main.c helpers.c eat.c exit.c launch.c sleep.c think.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.SECONDARY: $(OBJ)

.PHONY: clean