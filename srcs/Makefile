NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -I. -Ilibft -g
LDFLAGS = -Llibft -lft -lreadline

# LEXER
SRCS_LEXER = ft_lexer.c

# TOKENIZE
SRCS_TOKENIZE = ft_tokens_count.c ft_tokenize.c ft_get_token.c ft_tokenize_utils.c

# PARSE
SRCS_PARSER = ft_trim_quotes.c ft_parse.c ft_word_split.c ft_expand_dolar.c ft_check_quotes.c ft_split_tokens.c ft_build_token.c\
ft_add_token.c ft_build_cmd_table.c

# FD_FILES
SRCS_FD_FILES = ft_here_doc.c ft_set_infile.c ft_open_outfile.c ft_open_infile.c

# EXECUTE
SRCS_EXECUTE = ft_exec_args.c ft_find_command_path.c ft_exec_cmd_line.c ft_command_list.c

# UTILS
SRCS_UTILS = ft_getenv.c

# SRCS_DIRS
LEXER_DIR = lexer
PARSER_DIR = parser
TOKENIZE_DIR = $(PARSER_DIR)/tokenize
FD_FILES_DIR = fd_files
EXECUTE_DIR = execute
UTILS_DIR = utils

# SOURCE
SRCS = minishell.c ft_change_dolar_val.c ft_contains_quotes.c ft_count_simple_quote.c\
ft_extend_dolar.c ft_free_memory.c ft_isspace.c ft_quotes_count.c\
ft_token_expanded_len.c ft_utils.c\
$(addprefix $(LEXER_DIR)/, $(SRCS_LEXER))\
$(addprefix $(TOKENIZE_DIR)/, $(SRCS_TOKENIZE))\
$(addprefix $(PARSER_DIR)/, $(SRCS_PARSER))\
$(addprefix $(FD_FILES_DIR)/, $(SRCS_FD_FILES))\
$(addprefix $(EXECUTE_DIR)/, $(SRCS_EXECUTE))\
$(addprefix $(UTILS_DIR)/, $(SRCS_UTILS))

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

$(OBJSDIR)/%.o: %.c Makefile minishell.h libft/libft.h | $(OBJSDIR)
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
