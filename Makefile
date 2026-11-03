NAME		= push_swap

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INC			= -I includes

SRC_DIR		= srcs
OBJ_DIR		= obj

SRCS		= main.c \
			  utils/ft_utils.c \
			  stack/stack_list.c \
			  stack/stack_list_utils.c \
			  stack/stack_find.c \
			  parsing/parse_args.c \
			  parsing/parse_numbers.c \
			  parsing/index_ranks.c \
			  operations/operations.c \
			  operations/op_record.c \
			  output/print_ops.c \
			  output/print_bench.c \
			  strategy/strategy.c \
			  sorting/simple/simple_sort.c \
			  sorting/medium/chunk_sort.c \
			  sorting/complex/quick_sort.c \
			  sorting/complex/quick_move.c \
			  sorting/complex/quick_small.c \
			  sorting/adaptive/adaptive_lis.c \
			  sorting/adaptive/adaptive_insert.c \
			  sorting/adaptive/adaptive_utils.c
			  

OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/push_swap.h Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re