NAME = pipex
SRC = main.c	\
	  init.c	\
	  error.c	\
	  memory.c	\
	  cmd.c		\
	  exec.c	\
	  validation.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft.a
# FT_PRINTF = libftprintf.a


all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo "Linking..."
	@cc $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ): $(SRC)
	@echo "Compiling..."
	@cc $(CFLAGS) -c $(SRC)

libft.a:
	@echo "Compiling libft..."
	@make -C libft && mv libft/$(LIBFT) .

# $(FT_PRINTF):
# 	@echo "Compiling ft_printf..."
# 	@make -C ft_printf && mv ft_printf/$(FT_PRINTF) .

clean:
	@echo "Cleaning..."
	@make -C libft clean
	@rm -f $(OBJ) $(LIBFT)

fclean: clean
	@echo "Full cleaning..."
	@rm -f $(NAME)

b: all clean
	clear

re: fclean all