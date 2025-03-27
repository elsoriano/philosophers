NAME = philo
GCC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCSDIR = src
OBJSDIR = obj
SRCSFILES = main.c \
			free.c \
			init.c \
			routine.c \
			utils.c
OBJSFILES = $(SRCSFILES:.c=.o)
SRCS = $(addprefix $(SRCSDIR)/, $(SRCSFILES))
OBJS = $(addprefix $(OBJSDIR)/, $(OBJSFILES))
HEAD = -I inc

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C ./inc/libft
	$(GCC) $(CFLAGS) $(OBJS) -o $(NAME) ./inc/libft/libft.a

$(OBJS): $(SRCS)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c | obj
	$(GCC) $(CFLAGS) -c $< -o $@ $(HEAD) 

obj:
	mkdir -p $(OBJSDIR)

clean:
	rm -rf $(OBJSDIR)
	$(MAKE) -C ./inc/libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./inc/libft fclean

re: fclean all

debug:
	clang src/*.c inc/libft/libft.a -g -fsanitize=thread -pthread -Wall -Wextra -Werror -o philo

.PHONY: clean fclean re debug

