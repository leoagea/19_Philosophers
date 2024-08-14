NAME = philo

CC = cc

CFLAGS = -Werror -Wall -Wextra #-fsanitize=thread -g

RM = rm -rf

SRCS_DIR = src/
OBJS_DIR = obj/

SRCS =	src/main.c src/init.c src/utils.c src/utils_2.c src/routine.c src/atoi.c src/action.c

OBJ = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

DEBUG = debug
OBJD_DIR = obj_debug/
OBJD = $(SRCS:$(SRCS_DIR)%.c=$(OBJD_DIR)%.o)

GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
RESET = \033[0m

BLOCK = █
EMPTY_BLOCK = ░

TOTAL := $(words $(SRCS))
COUNT := 0

define PROGRESS_BAR
    @$(eval COUNT=$(shell echo $$(($(COUNT) + 1))))
    @printf "\r$(YELLOW)[%3d/%3d]$(RESET) $(BLUE)" $(COUNT) $(TOTAL)
    @bash -c 'for i in `seq 1 $$(($(COUNT) * 50 / $(TOTAL)))`; do printf $(BLOCK); done'
    @bash -c 'for i in `seq 1 $$((50 - $(COUNT) * 50 / $(TOTAL)))`; do printf $(EMPTY_BLOCK); done'
    @printf "$(RESET)]"
endef

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(OBJ) $(CFLAGS) -o $(NAME)
	@printf "\nCompilation complete.\n"
	@printf "$(GREEN)Executable philo created.$(RESET)\n"

$(DEBUG) : $(OBJD)
	@$(CC) $(OBJD) $(CFLAGS) -fsanitize=address -g -o $(DEBUG)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	$(PROGRESS_BAR)
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
 