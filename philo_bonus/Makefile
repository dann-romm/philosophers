CC			= gcc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -Ofast -MMD

NAME		= philo_bonus

SRCDIR		= ./
OBJDIR		= ./build
INCDIR		= ./

SRC			=	$(SRCDIR)/main_bonus.c \
				$(SRCDIR)/initialize_bonus.c \
				$(SRCDIR)/philosopher_bonus.c \
				$(SRCDIR)/utils_ft_bonus.c \
				$(SRCDIR)/utils_philo_bonus.c \
				$(SRCDIR)/time_bonus.c

OBJ			= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
DEP			= $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJDIR)/%.o : $(SRCDIR)/%.c Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re
