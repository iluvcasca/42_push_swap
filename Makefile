C_FILES = ps_algo1.c ps_lis.c ps_operations.c ps_sort.c push_swap_opti_r.c \
push_swap_utlis.c ps_algo2.c ps_operations1.c ps_parsing1.c \
push_swap.c push_swap_opti_rr1.c ps_algo.c ps_operations2.c \
ps_parsing.c push_swap_opti_r1.c push_swap_opti_rr.c \
sort_small.c sort_small1.c push_swap_utlis1.c

C_FILES_BONUS = checker.c ps_algo1.c ps_lis.c ps_operations.c \
ps_sort.c push_swap_opti_r.c \
push_swap_utlis.c ps_algo2.c ps_operations1.c ps_parsing1.c \
push_swap_opti_rr1.c ps_algo.c ps_operations2.c \
ps_parsing.c push_swap_opti_r1.c push_swap_opti_rr.c \
sort_small.c sort_small1.c push_swap_utlis1.c

C_FLAGS = -g -Wall -Wextra
#-Werror
NAME = push_swap

.PHONY: all clean fclean re
.DEFAULT: all

all: $(NAME)

$(NAME): $(C_FILES) | build
	cc $(C_FLAGS) $^ -o $(NAME) -L ./libft -lft

bonus: $(C_FILES_BONUS) | build
	cc $(C_FLAGS) $^ -o checker -L ./libft -lft

build:
	$(MAKE) -C libft

clean:
	$(MAKE) -C libft clean

fclean: clean
	-rm -f $(NAME)
	-rm -f checker
	$(MAKE) -C libft fclean


re: fclean all
