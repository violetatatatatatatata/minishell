# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avelandr <avelandr@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/18 20:09:52 by avelandr          #+#    #+#              #
#    Updated: 2025/12/18 20:12:18 by avelandr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable name
NAME = minishell
CC = cc

# Compiler flags
CFLAGS = -Wall -Werror -Wextra -g
RDFLAG = -lreadline

#Libs
LIBFT_DIR = libft

# Directories
SRC_DIR		= srcs
OBJ_DIR		= objs
LIB_DIR		= libs
INC_DIR		= ./includes/
DEPS_DIR	= deps

# Source files
SRC_FILES = \
	srcs/main.c \
	srcs/builtins/cd.c \
	srcs/builtins/echo.c \
	srcs/builtins/env.c \
	srcs/builtins/exit.c \
	srcs/builtins/export.c \
	srcs/builtins/pwd.c \
	srcs/builtins/unset.c \
	srcs/env/env_setandget.c \
	srcs/env/env_to_array.c \
	srcs/env/env_utils.c \
	srcs/env/init_env.c \
	srcs/execute/ft_close_pipes.c \
	srcs/execute/ft_exec_args.c \
	srcs/execute/ft_exec_builtin.c \
	srcs/execute/ft_exec_cmd_line.c \
	srcs/execute/ft_exect_children.c \
	srcs/execute/ft_find_command_path.c \
	srcs/execute/ft_free_pipes.c \
	srcs/execute/ft_set_pipes.c \
	srcs/execute/ft_wait_children.c \
	srcs/execute/ft_wait_fork.c \
	srcs/fd_files/ft_here_doc.c \
	srcs/fd_files/ft_open_infile.c \
	srcs/fd_files/ft_open_outfile.c \
	srcs/fd_files/ft_set_infile.c \
	srcs/init/minishell.c \
	srcs/init/shell_loop.c \
	srcs/init/signals.c \
	srcs/init/signals_heredoc.c \
	srcs/lexer/ft_lexer.c \
	srcs/parser/ft_add_tokentolist.c \
	srcs/parser/ft_build_cmd_table.c \
	srcs/parser/ft_build_token.c \
	srcs/parser/ft_check_quotes.c \
	srcs/parser/ft_expand_dolar.c \
	srcs/parser/ft_expand_red.c \
	srcs/parser/ft_expansion.c \
	srcs/parser/ft_handle_env_var.c \
	srcs/parser/ft_insert_exit_value.c \
	srcs/parser/ft_parse.c \
	srcs/parser/ft_remove_quotes.c \
	srcs/parser/ft_split_tokens.c \
	srcs/parser/ft_word_split.c \
	srcs/parser/tokenize/ft_get_token.c \
	srcs/parser/tokenize/ft_tokenize.c \
	srcs/parser/tokenize/ft_tokens_count.c \
	srcs/terminator/ft_free_cmd_list.c \
	srcs/terminator/ft_free_memory.c \
	srcs/terminator/ft_free_split.c \
	srcs/terminator/terminator.c \
	srcs/utils/export_utils.c \
	srcs/utils/ft_double_arr_size.c \
	srcs/utils/is_definition/ft_is_builtin.c \
	srcs/utils/is_definition/ft_is_pipe.c \
	srcs/utils/is_definition/ft_is_redirection.c \
	srcs/utils/is_definition/ft_isblank.c \
	srcs/utils/is_definition/ft_ismeta.c \
	srcs/utils/is_definition/ft_isspace.c \
	srcs/utils/is_definition/is_controlop.c \
	srcs/utils/is_definition/is_filename.c \
	srcs/utils/is_definition/is_redop.c \
	srcs/utils/is_definition/is_token.c \
	srcs/utils/is_definition/is_word.c \
	srcs/utils/print_msg.c \
	srcs/utils/prompt.c \
	srcs/utils/utils.c
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(DEPS_DIR)/%.d)
CLIB = .a

# Rules
all: $(NAME)
	echo "Minishell done."

$(NAME): $(OBJ_FILES) $(LIB_DIR)/$(LIBFT_DIR)$(CLIB)
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES) -I $(INC_DIR) -L $(LIB_DIR) -lft $(RDFLAG)

$(LIB_DIR)/$(LIBFT_DIR)$(CLIB):
	@make -C $(LIBFT_DIR)
	@mkdir -p $(LIB_DIR)
	@cp -a $(LIBFT_DIR)/$(LIBFT_DIR)$(CLIB) $(LIB_DIR)/

$(INC_DIR):
	@mkdir -p $(INC_DIR)
	@cp -a $(LIBFT_DIR)/$(INC_DIR)/*.h $(INC_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(DEPS_DIR)/$*.d)
	$(CC) $(CFLAGS) -c $< -o $@ -MD -MF $(DEPS_DIR)/$*.d -I $(INC_DIR)

-include $(DEP_FILES)

norm:
	norminette $(Includes) $(SRC_DIR)# $(LIBFT_DIR)

mem:
	valgrind --track-origins=yes --show-leak-kinds=all --leakcheck=full ./$(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(LIB_DIR)
	@rm -rf $(DEPS_DIR)
	@make fclean -C $(LIBFT_DIR)
	echo "Minishell cleaned."

fclean: clean
	@rm -f $(NAME)
	echo "Everything erased."

re: fclean all

.PHONY: all clean fclean re
