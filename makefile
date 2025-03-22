debug:
	gcc src/*.c inc/libft/libft.a -g -fsanitize=address -Wall -Wextra -Werror -o philo

PHONY: debug