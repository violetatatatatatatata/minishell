# Makefile for libft

# Compiler
CC = cc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror

# Source files
SRCS = \
    convs/ft_atoi.c \
    mem/ft_bzero.c \
    mem/ft_calloc.c \
    comps/ft_isalnum.c \
    comps/ft_isalpha.c \
    comps/ft_isascii.c \
    comps/ft_isdigit.c \
    comps/ft_isprint.c \
	comps/ft_is_negative.c \
    mem/ft_memchr.c \
    mem/ft_memcmp.c \
    mem/ft_memcpy.c \
    mem/ft_memmove.c \
    mem/ft_memset.c \
	mem/ft_swap.c \
    fd/ft_putchar_fd.c \
    fd/ft_putendl_fd.c \
    fd/ft_putnbr_fd.c \
    fd/ft_putstr_fd.c \
    strings/ft_strdup.c \
    strings/ft_strchr.c \
    strings/ft_strlcat.c \
    strings/ft_strlcpy.c \
    strings/ft_strlen.c \
    strings/ft_strncmp.c \
    strings/ft_strnstr.c \
    strings/ft_tolower.c \
    strings/ft_toupper.c \
    strings/ft_substr.c \
    strings/ft_strjoin.c \
    strings/ft_strtrim.c \
    strings/ft_strmapi.c \
	strings/ft_strcmp.c \
    convs/ft_itoa.c \
    strings/ft_split.c \
    list/ft_lstnew_bonus.c \
    list/ft_lstadd_front_bonus.c \
    list/ft_lstadd_back_bonus.c \
    list/ft_lstclear_bonus.c \
    list/ft_lstdelone_bonus.c \
    list/ft_lstiter_bonus.c \
    list/ft_lstlast_bonus.c \
    list/ft_lstmap_bonus.c \
    list/ft_lstsize_bonus.c \
    list/ft_lstalast_bonus.c \
	arrays/ft_count_if.c \
	arrays/ft_foreach.c \
	arrays/ft_range.c \
    printf/ft_printf.c \
    printf/printnum.c \
    printf/printstring.c \
    printf/printpoint.c \
    printfd/ft_printfd.c \
    printfd/printnumfd.c \
    printfd/printstringfd.c \
    printfd/printpointfd.c \

# Object files
OBJS = $(SRCS:.c=.o)

# Library name
LIBRARY = libft.a

# Default target
all: $(LIBRARY)
	echo "libft done."

# Rule to create the library
$(LIBRARY): $(OBJS)
	@ar rcs $@ $^

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and the library
clean:
	rm -f $(OBJS)

# Clean up the library
fclean: clean
	rm -f $(LIBRARY)

# Rebuild the library
re: fclean all

.PHONY: all clean fclean re
