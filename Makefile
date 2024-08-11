NAME = philo

CC = cc

CFLAGS = -Werror -Wall -Wextra

RM = rm -rf

SRCS_DIR = src/
OBJS_DIR = obj/

SRCS =	src/main.c src/init.c src/utils.c src/utils_2.c src/routine.c src/atoi.c src/action.c

OBJ = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

DEBUG = debug
OBJD_DIR = obj_debug/
OBJD = $(SRCS:$(SRCS_DIR)%.c=$(OBJD_DIR)%.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

$(DEBUG) : $(OBJD)
	@$(CC) $(OBJD) $(CFLAGS) -fsanitize=address -g -o $(DEBUG)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(OBJD_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJD_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

clean :
	@$(RM) obj/*.o
	@$(RM) -r obj

fclean : clean
	@$(RM) $(NAME)

re : fclean all
 