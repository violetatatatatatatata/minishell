# Executable name
NAME = minishell
CC = cc

# Compiler flags
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
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
# CAMBIAR EL WILDCARD AL FINAL DEL PROYECTO!!!
SRC_FILES = $(shell find $(SRC_DIR) -name "*.c")
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

#mem:
#	valgrind --track-origins=yes --show-leak-kinds=all --leakcheck=full ./$(NAME)

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
