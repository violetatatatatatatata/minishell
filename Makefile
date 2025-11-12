NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -I. -Ilibft -g
LDFLAGS = -Llibft -lft -lreadline

# LEXER
SRCS_LEXER = ft_lexer.c

# TOKENIZE
SRCS_TOKENIZE = ft_tokens_count.c ft_tokenize.c ft_get_token.c

# PARSE
SRCS_PARSER = ft_parse.c ft_word_split.c ft_check_quotes.c ft_split_tokens.c ft_build_token.c\
ft_add_tokentolist.c ft_build_cmd_table.c ft_remove_quotes.c ft_expand_dolar.c ft_expansion.c ft_handle_env_var.c

# FD_FILES
SRCS_FD_FILES = ft_here_doc.c ft_set_infile.c ft_open_outfile.c ft_open_infile.c

# EXECUTE
SRCS_EXECUTE = ft_exec_args.c ft_find_command_path.c ft_exec_cmd_line.c ft_wait_children.c

# UTILS
SRCS_UTILS = ft_getenv.c ft_utils.c

# IS_DEFINITION_DIR
SRCS_IS_DEFINITION = ft_is_pipe.c ft_is_redirection.c ft_isspace.c

# SRCS_DIRS
INCLUDES_DIR = includes
LEXER_DIR = lexer
PARSER_DIR = parser
TOKENIZE_DIR = $(PARSER_DIR)/tokenize
FD_FILES_DIR = fd_files
EXECUTE_DIR = execute
UTILS_DIR = utils
IS_DEFINITION_DIR = $(UTILS_DIR)/is_definition

# SOURCE
SRCS = minishell.c\
ft_free_memory.c\
$(addprefix $(LEXER_DIR)/, $(SRCS_LEXER))\
$(addprefix $(TOKENIZE_DIR)/, $(SRCS_TOKENIZE))\
$(addprefix $(PARSER_DIR)/, $(SRCS_PARSER))\
$(addprefix $(FD_FILES_DIR)/, $(SRCS_FD_FILES))\
$(addprefix $(EXECUTE_DIR)/, $(SRCS_EXECUTE))\
$(addprefix $(UTILS_DIR)/, $(SRCS_UTILS))\
$(addprefix $(IS_DEFINITION_DIR)/, $(SRCS_IS_DEFINITION))\

# OBJECTS
OBJSDIR = obj
OBJS = $(SRCS:.c=.o)
OBJS := $(addprefix $(OBJSDIR)/, $(OBJS))

LIBFT = libft/libft.a

all: $(NAME)

$(LIBFT): libft/*.c libft/*.h libft/Makefile
	$(MAKE) -C libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

$(OBJSDIR)/%.o: %.c Makefile $(INCLUDES_DIR)/minishell.h libft/libft.h | $(OBJSDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJSDIR):
	@mkdir -p $@

clean:
	rm -rf $(OBJSDIR)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
