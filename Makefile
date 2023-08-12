NAME	=	minishell

SRCS	=	main.c	\
			ft_error.c \
			ft_free.c \
			ft_free_2.c \
			ft_cmd_custom.c \
			ft_fill_tab.c \
			ft_cmd.c \
			ft_start_global.c \
			ft_signal.c \
			redir/ft_chevron.c \
			redir/ft_chevron_2.c \
			redir/ft_pipe.c \
			utils/ft_atoi.c \
			utils/ft_itoa.c \
			utils/ft_putnbr_chr.c \
			utils/ft_split.c \
			utils/ft_strcmp.c \
			utils/ft_strdup_char.c \
			utils/ft_strdup.c \
			utils/ft_strjoin_4.c \
			utils/ft_strjoin.c \
			utils/ft_strjoin_modif.c \
			utils/ft_strlen.c \
			utils/ft_strlen_char.c \
			utils/get_next_line.c \
			utils/get_next_line_utils.c \
			parsing/chr_dol.c \
			parsing/create_arg_and_cmd.c \
			parsing/fill_tab.c \
			parsing/ft_chrch_name.c \
			parsing/ft_paths.c \
			parsing/ft_quot.c \
			parsing/parsing.c \
			parsing/verif_2.c \
			parsing/verif.c \
			cmd_custom/ft_echo.c \
			cmd_custom/ft_pwd.c \
			cmd_custom/ft_cd.c \
			cmd_custom/ft_export.c \
			cmd_custom/ft_export_2.c \
			cmd_custom/ft_export_3.c \
			cmd_custom/ft_export_4.c \
			cmd_custom/ft_unset.c \
			cmd_custom/ft_unset_2.c \
			cmd_custom/ft_env.c \
			cmd_custom/ft_exit.c \

OBJ =	${SRCS:.c=.o}

CC =	gcc

CFLAGS	=	-Wall -Wextra -Werror -g #-fsanitize=address

OPTION = -lreadline

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): ${OBJ}
		$(CC) $(CFLAGS) -o $(NAME) ${OBJ} $(OPTION)

all:	${NAME}

clean:
		rm -f ${OBJ}

fclean:	clean
		rm -f ${NAME}

re:	fclean all

.PHONY: all clean fclean re
