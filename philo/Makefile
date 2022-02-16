CC			= gcc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror
# CFLAGS		= -fsanitize=thread

NAME		= philo

SRCDIR		= ./src/
OBJDIR		= ./obj/
INCDIR		= ./includes/

SRC			= main.c initialize.c philosopher.c utils_ft.c utils_philo.c time.c
OBJ			= $(addprefix $(OBJDIR), $(SRC:.c=.o))

all: $(NAME)

$(OBJDIR)%.o : $(SRCDIR)%.c $(INCDIR)philosophers.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR) -Ofast

$(NAME): $(OBJDIR) $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: $(NAME)

test: $(NAME)
	./$(NAME) 5 800 200 200 2

.PHONY: all clean fclean re bonus
