CC	= cc
CFLAGS	= -Wall -Wextra -Werror
SRCS	= ../srcs
OBJS	= $(SRCS:.c=.o)
RM  	= rm -rf
NAME	= drug.a

.o : .c
	$(CC) $(CFLAGS) -c $@ -o $< -I .

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS) 

bonus : $(NAME) $(BOBJS)
	ar rcs $(NAME) $(BOBJS) 

all 	: $(NAME)

clean :
	$(RM) $(OBJS) $(BOBJS)

fclean : clean
	$(RM) $(NAME)

compil :
	@echo "Compiling...\n"
	@$(CC) $(CFLAGS) -g -o lezgo $(SRCS)
	@./lezgo

debug	:
	@echo "Compiling...\n"
	@$(CC) $(CFLAGS) -g -o debug $(SRCS) $(BONUS)
	@lldb ./debug


drogue :
	@echo "Compiling...\n"
	@$(CC) $(CFLAGS) -g -o bonus $(BONUS)
	@./bonus

re : fclean all
