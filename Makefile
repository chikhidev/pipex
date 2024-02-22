NAME = pipex
SRC = pipex.c validation.c error.c config.c memo.c v2.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft.a
GNL = get_next_line.o
FT_PRINTF = libftprintf.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(GNL) $(FT_PRINTF)
	@echo "Linking..."
	@cc $(OBJ) $(GNL) $(LIBFT) $(FT_PRINTF) -o $(NAME)

$(OBJ): $(SRC)
	@echo "Compiling..."
	@cc $(CFLAGS) -c $(SRC)

libft.a:
	@echo "Compiling libft..."
	@make -C libft && mv libft/$(LIBFT) .

get_next_line.o:
	@echo "Compiling get_next_line..."
	@cc $(CFLAGS) -c get_next_line/get_next_line.c -o $(GNL)

$(FT_PRINTF):
	@echo "Compiling ft_printf..."
	@make -C ft_printf && mv ft_printf/$(FT_PRINTF) .

clean:
	@echo "Cleaning..."
	@make -C libft clean
	@rm -f $(OBJ) $(GNL) $(LIBFT)
	@make -C ft_printf clean

fclean: clean
	@echo "Full cleaning..."
	@rm -f $(NAME)

build: all clean

re: fclean all