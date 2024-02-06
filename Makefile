CC	= cc
CFLAGS	= -Wall -Wextra -Werror
MLX_INCLUDES = includes/minilibx-linux
LIBFT_DIR = includes/libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBMLX = $(MLX_INCLUDES)/libmlx.a
MLX_FLAGS = -lXext -lX11 -lm -lz
FILES 			= 	colors		\
					event_hook	\
					fractal		\
					image		\
					main
SRCS 			= 	$(addsuffix .c, $(addprefix src/, $(FILES)))
OBJS	= $(SRCS:.c=.o)
RM  	= rm -rf
NAME	= fractol

define LIB :=
	$(LIBFT)
	$(LIBMLX)
endef
LIB := $(strip $(LIB))

# CURSOR MOVEMENTS
MOV_U			= 	\033[1A
MOV_D			= 	\033[1B
MOV_F			= 	\033[1C
MOV_B			= 	\033[1D

ERASE_ALL		= 	\033[0J

# COLORS 
YELLOW 			= 	\033[0;33m
GREEN 			= 	\033[0;32m
BLUE 			= 	\033[0;34m
RED				= 	\033[0;31m
PURPLE 			= 	\033[0;35m
CYAN 			= 	\033[0;36m
BLACK 			= 	\033[0;30
WHITE 			= 	\033[0;37m

lib : 
	@echo "$(CYAN)Compiling..."
	@make --silent -C $(LIBFT_DIR)
	@make --silent -C $(MLX_INCLUDES)
	@echo "$(MOV_U)$(ERASE_ALL)$(GREEN)libft compiled $(RESET)"

drugs :
	@${CC} ${CFLAGS} ${SRCS} $(LIB) $(MLX_FLAGS) -o $(NAME)
	
clean :
	@$(RM) $(OBJS) $(BOBJS)
	@make clean --silent -C $(LIBFT_DIR)
	@make clean --silent -C $(MLX_INCLUDES)
	@echo "$(PURPLE)Clean up bro"

fclean : clean
	@$(RM) $(NAME)
	@make fclean --no-print-directory -C $(LIBFT_DIR)
	@make clean --no-print-directory -C $(MLX_INCLUDES)
	@echo "$(CYAN)everything clean bro"

re : fclean all

.PHONY	: all clean fclean re ${NAME}