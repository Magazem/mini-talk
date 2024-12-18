SRCS    = client.c server.c

OBJS    := $(SRCS:%.c=%.o)

NAME    = minitalk

CC      = cc
RM      = rm -f

CFLAGS  = -Wall -Wextra -Werror

LIBFT_DIR = ft_addons/ft_printf/libft
PRINTF_DIR = ft_addons/ft_printf

all:    ${NAME}

%.o:    %.c
		${CC} ${CFLAGS} -I${LIBFT_DIR} -I${PRINTF_DIR} -c $< -o $@

${NAME}: server client

server:	server.o
		@$(MAKE) -C $(LIBFT_DIR)
		@$(MAKE) -C $(PRINTF_DIR)
		${CC} ${CFLAGS} $? -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lftprintf -o server

client:  client.o
		@$(MAKE) -C $(LIBFT_DIR)
		@$(MAKE) -C $(PRINTF_DIR)
		${CC} ${CFLAGS} $? -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lftprintf -o client

clean:
		@$(MAKE) fclean -C $(LIBFT_DIR)
		@$(MAKE) fclean -C $(PRINTF_DIR)
		${RM} ${OBJS}

fclean: clean
		${RM} server client

re:		fclean all

.PHONY:	all clean fclean re libft printf
