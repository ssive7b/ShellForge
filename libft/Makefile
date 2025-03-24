# Variables
NAME 			= 	libft.a
INCLUDES		=	./include
SRC_DIR			=	src/
OBJ_DIR			=	obj/

# Compilation specifications
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -I
RM				=	rm -f
AR				=	ar rcs

# Color Schemes
DEF_COLOR		=	\033[0;37m

# Sources
FTIS_DIR		=	ft_is/
FTIS			=	ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint

FTMEM_DIR		=	ft_mem/
FTMEM			=	ft_memset ft_bzero ft_memcpy ft_memmove ft_memchr ft_memcmp ft_calloc

FTPUT_DIR		=	ft_put/
FTPUT			=	ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd

FTTO_DIR		=	ft_to/
FTTO			=	ft_atoi ft_itoa ft_toupper ft_tolower

FTSTR_DIR		=	ft_str/
FTSTR			=	ft_strlen ft_strlcpy ft_strlcat ft_strchr \
					ft_strrchr ft_strncmp ft_strnstr ft_strdup \
					ft_substr ft_strjoin ft_strtrim ft_split \
					ft_strmapi ft_striteri ft_strcmp

FTLST_DIR		=	ft_lst/
FTLST			=	ft_lstnew_bonus ft_lstadd_front_bonus ft_lstsize_bonus \
					ft_lstlast_bonus ft_lstadd_back_bonus ft_lstdelone_bonus \
					ft_lstclear_bonus ft_lstiter_bonus ft_lstmap_bonus

FTREADS_DIR		=	ft_reads/
FTREADS			=	get_next_line

FTWRITES_DIR	=	ft_writes/
FTWRITES		=	ft_printf ft_printf_utils auxiliary_funcs	

# Aggregate source files
SRC_FILES+=$(addprefix $(FTIS_DIR), $(FTIS))
SRC_FILES+=$(addprefix $(FTMEM_DIR), $(FTMEM))
SRC_FILES+=$(addprefix $(FTPUT_DIR), $(FTPUT))
SRC_FILES+=$(addprefix $(FTTO_DIR), $(FTTO))
SRC_FILES+=$(addprefix $(FTSTR_DIR), $(FTSTR))
SRC_FILES+=$(addprefix $(FTLST_DIR), $(FTLST))
SRC_FILES+=$(addprefix $(FTREADS_DIR), $(FTREADS))
SRC_FILES+=$(addprefix $(FTWRITES_DIR), $(FTWRITES))

SRC				=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 			= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))


# Default Target
all: $(NAME)

# Ensure libft is up-to-date and combine with project files
$(NAME): $(OBJ)
			@$(AR) $(NAME) $(OBJ)
			@echo "$(DEF_COLOR)$(NAME) compiled successfully.$(DEF_COLOR)"

# Pattern rule to compile .c to .o files in the obj/ directory
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
			@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create object directory if it doesn't already exist
$(OBJ_DIR):
			@mkdir -p $(OBJ_DIR)
			@mkdir -p $(OBJ_DIR)$(FTIS_DIR)
			@mkdir -p $(OBJ_DIR)$(FTMEM_DIR)
			@mkdir -p $(OBJ_DIR)$(FTPUT_DIR)
			@mkdir -p $(OBJ_DIR)$(FTTO_DIR)
			@mkdir -p $(OBJ_DIR)$(FTSTR_DIR)
			@mkdir -p $(OBJ_DIR)$(FTLST_DIR)
			@mkdir -p $(OBJ_DIR)$(FTREADS_DIR)
			@mkdir -p $(OBJ_DIR)$(FTWRITES_DIR)

# Clean up object filesss
clean:
			@$(RM) -rf $(OBJ_DIR)
	
# Remove all artifacts
fclean: clean
			@$(RM) $(NAME)

# Full rebuild
# Make sure build is completely fresh and there are no leftover artifacts from previous builds
re: fclean all

# Prevent conflicts with files named like the below targets
.PHONY: all clean fclean re