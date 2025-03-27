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
	$(GCC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): $(SRCS)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c | obj
	$(GCC) $(CFLAGS) -c $< -o $@ $(HEAD) 

obj:
	mkdir -p $(OBJSDIR)

clean:
	rm -rf $(OBJSDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug:
	clang src/*.c inc/libft/libft.a -g -fsanitize=thread -pthread -Wall -Wextra -Werror -o philo

.PHONY: clean fclean re debug

