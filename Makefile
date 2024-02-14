NAME = pipex
SRC = pipex.c validation.c error.c config.c memo.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft.a
GNL = get_next_line.o

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(GNL)
	@echo "Linking..."
	@say "Linking..."
	@cc $(OBJ) $(LIBFT) $(GNL) -o $(NAME)
	@say "Done!, pipex is ready!!!"

$(OBJ): $(SRC)
	@echo "Compiling..."
	@say "Compiling..."
	@cc $(CFLAGS) -c $(SRC)

libft.a:
	@echo "Compiling libft..."
	@say "Compiling libft..."
	@make -C libft && mv libft/$(LIBFT) .

get_next_line.o:
	@echo "Compiling get_next_line..."
	@say "Compiling get_next_line..."
	@cc $(CFLAGS) -c get_next_line/get_next_line.c -o $(GNL)

clean:
	@echo "Cleaning..."
	@say "Cleaning..."
	@make -C libft clean
	@rm -f $(OBJ) $(GNL) $(LIBFT)

fclean: clean
	@echo "Full cleaning..."
	@say "Full cleaning..."
	@rm -f $(NAME)

build: all clean

re: fclean all