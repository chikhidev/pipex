NAME = pipex
BONUS = pipex_bonus

SRC = manda/main.c    \
      manda/init.c    \
      manda/error.c   \
      manda/memory.c  \
      manda/cmd.c     \
      manda/exec.c    \
      manda/validation.c

BSRC = bonus/main_bonus.c       \
       bonus/init_bonus.c       \
       bonus/error_bonus.c      \
       bonus/memory_bonus.c     \
       bonus/cmd_bonus.c        \
       bonus/exec_bonus.c       \
       bonus/validation_bonus.c

OBJ = $(SRC:.c=.o)
BOBJ = $(BSRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft.a

all: $(NAME)
bonus: $(BONUS)

$(NAME): $(OBJ) $(LIBFT)
	@echo "Linking..."
	@cc $(OBJ) $(LIBFT) -o $(NAME)

$(BONUS): $(BOBJ) $(LIBFT)
	@echo "Linking..."
	@cc $(BSRC:.c=.o) $(LIBFT) -o $(BONUS)

$(LIBFT):
	@echo "Compiling libft..."
	@make -C ./libft && mv ./libft/$(LIBFT) .

clean:
	@echo "Cleaning..."
	@rm -f $(OBJ) $(LIBFT) $(BOBJ)

fclean: clean
	@echo "Full cleaning..."
	@rm -f $(NAME) $(BONUS)

re: fclean all
