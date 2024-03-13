# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/03 12:19:46 by aserebry          #+#    #+#              #
#    Updated: 2024/03/05 13:00:08 by aserebry         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf
CC = cc
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
LIBFT = libft/libft.a
NAME = minishell

SRC = 	src/aux/error.c \
		src/aux/ft_countchar.c \
		src/aux/ft_dup_matrix.c \
		src/aux/ft_extend_matrix.c \
		src/aux/ft_free_matrix.c \
		src/aux/ft_isspace.c \
		src/aux/ft_matrix_replace_in.c \
		src/aux/ft_matrixlen.c \
		src/aux/ft_putendl_m_fd.c \
		src/aux/ft_putmatrix_fd.c \
		src/aux/ft_putnchar_fd.c \
		src/aux/ft_putstr_m_fd.c \
		src/aux/ft_putstrn_fd.c \
		src/aux/ft_strchars_i.c \
		src/aux/ft_strchr_i.c \
		src/aux/ft_subsplit.c \
		src/aux/prompt.c \
		src/aux/signal.c \
		src/builtin/ft_cd.c \
		src/builtin/ft_echo.c \
		src/builtin/ft_env.c \
		src/builtin/ft_exit.c \
		src/builtin/ft_export.c \
		src/builtin/ft_export_aux1.c \
		src/builtin/ft_export_aux2.c \
		src/builtin/ft_pwd.c \
		src/builtin/ft_unset.c \
		src/executor/builtin_check.c \
		src/executor/custom_cmd.c \
		src/executor/exec.c \
		src/executor/get_cmd.c \
		src/executor/heredoc.c \
		src/minishell.c \
		src/parser/cmdsubsplit.c \
		src/parser/cmdtrim.c \
		src/parser/expand.c \
		src/parser/fill_node.c \
		src/parser/fill_node_redir.c \
		src/parser/get_params.c \
		src/parser/parse_args.c \
		src/parser/strtrim_all.c \
		
OBJS = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C libft
	$(CC) $(OBJS) $(LIBFT) -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include -lreadline -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I ~/.brew/opt/readline/include -MMD -MP -c $< -o $@

-include $(DEPS)

re: fclean all

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C libft clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C libft fclean

.PHONY: all clean fclean re