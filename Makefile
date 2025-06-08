###	Variables
NAME					=	shellforge
TEST_EXEC				=	test_runner
LIBFT 					=	libft
INCLUDES				=	./include
MAKEFLAGS				+=	--no-print-directory

###	Source files specs
#	dirs
SRC_DIR					=	src

#	files
SRC						=	$(SRC_DIR)/app/main.c											\
							$(SRC_DIR)/app/inits.c											\
							$(SRC_DIR)/app/cleanup_central.c								\
							$(SRC_DIR)/env/env_init.c										\
							$(SRC_DIR)/env/env_aux.c										\
							$(SRC_DIR)/env/env_utils.c										\
							$(SRC_DIR)/env/env_default.c									\
							$(SRC_DIR)/parser/lexer/lexer.c									\
							$(SRC_DIR)/parser/lexer/lexer_utils.c							\
							$(SRC_DIR)/parser/lexer/lexer_cleaners.c						\
							$(SRC_DIR)/parser/expansions/expander.c							\
							$(SRC_DIR)/parser/expansions/expander_utils.c					\
							$(SRC_DIR)/parser/parsing/parser.c								\
							$(SRC_DIR)/parser/parsing/parser_ast_init.c						\
							$(SRC_DIR)/parser/parsing/parser_ast_utils.c					\
							$(SRC_DIR)/parser/parsing/parser_handlers.c						\
							$(SRC_DIR)/parser/parsing/parser_redirections.c					\
							$(SRC_DIR)/parser/parsing/parser_aux.c							\
							$(SRC_DIR)/parser/parsing/parser_utils.c						\
							$(SRC_DIR)/parser/validation/parser_validation.c				\
							$(SRC_DIR)/parser/validation/parser_validation_operators.c		\
							$(SRC_DIR)/parser/validation/parser_validation_redirs.c			\
							$(SRC_DIR)/parser/get_ast_root.c								\
							$(SRC_DIR)/parser/parser_error_handling.c						\
							$(SRC_DIR)/parser/parser_mem_cleaners.c							\
							$(SRC_DIR)/executioner/init_execs.c								\
							$(SRC_DIR)/executioner/execute.c								\
							$(SRC_DIR)/executioner/cmd_utils.c								\
							$(SRC_DIR)/executioner/exec_mode_handlers.c						\
							$(SRC_DIR)/executioner/pipe_setup.c								\
							$(SRC_DIR)/executioner/pipe_process.c							\
							$(SRC_DIR)/executioner/cmd_path_resolution.c					\
							$(SRC_DIR)/executioner/exec_utils.c								\
							$(SRC_DIR)/executioner/heredoc.c								\
							$(SRC_DIR)/executioner/builtins/builtin_utils.c					\
							$(SRC_DIR)/executioner/builtins/cd.c							\
							$(SRC_DIR)/executioner/builtins/echo.c							\
							$(SRC_DIR)/executioner/builtins/env.c							\
							$(SRC_DIR)/executioner/builtins/exit.c							\
							$(SRC_DIR)/executioner/builtins/export.c						\
							$(SRC_DIR)/executioner/builtins/export_utils.c					\
							$(SRC_DIR)/executioner/builtins/pwd.c							\
							$(SRC_DIR)/executioner/builtins/unset.c							\
							$(SRC_DIR)/signals/signal_setup.c								\
							$(SRC_DIR)/signals/signal_handlers.c							\
							$(SRC_DIR)/utils/string_utils.c									\
							$(SRC_DIR)/utils/array_utils.c									\
							$(SRC_DIR)/utils/memory_utils.c									\
							$(SRC_DIR)/utils/error_handlers.c								\
							$(SRC_DIR)/utils/debug_utils.c									\
							$(SRC_DIR)/utils/char_designation.c

TOTAL_SRC_FILES			:=	$(words $(SRC))

### Object files specs
#	dirs
OBJ_DIR					=	obj

#	files
OBJ						=	$(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRC:.c=.o))

###	Compilation/ Linking configs
CC						=	cc
CFLAGS					=	-Werror -Wextra -Wall
LDFLAGS					=	-lreadline -Llibft -lft
RM						=	rm -rf
COUNT					:=	0

###	Color Schemes
DEF_COLOR		=	\033[0;37m # Light gray
BOLD_GREEN		=	\033[1;32m
ORANGE			=	\033[0;33m
VIVID_BLUE		=	\033[1;34m
PURPLE			=	\033[0;35m
MAGENTA			=	\033[1;35m

###	Target rules
#	Default Target
all						:	$(NAME)

#	prod
$(NAME)					:	$(OBJ) 
							@printf "\n"
							@printf "\n$(DEF_COLOR)🔄 Compiling dependencies...$(DEF_COLOR)\n"
							@make -C $(LIBFT) 
							@printf "\n$(DEF_COLOR)✅ Dependencies fulfilled.$(DEF_COLOR)\n"
							@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
							@printf "\n$(BOLD_GREEN)[$(NAME)]:\t✅ $(NAME) compiled successfully!$(DEF_COLOR)\n"

$(OBJ)					:	$(OBJ_DIR)

#	Create the object directory if it doesn't exist
$(OBJ_DIR)				:	
							@mkdir -p $(OBJ_DIR)
							@mkdir -p $(OBJ_DIR)/app
							@mkdir -p $(OBJ_DIR)/env
							@mkdir -p $(OBJ_DIR)/parser/ast
							@mkdir -p $(OBJ_DIR)/parser/expansions
							@mkdir -p $(OBJ_DIR)/parser/lexer
							@mkdir -p $(OBJ_DIR)/parser/parsing
							@mkdir -p $(OBJ_DIR)/parser/validation
							@mkdir -p $(OBJ_DIR)/executioner
							@mkdir -p $(OBJ_DIR)/executioner/builtins
							@mkdir -p $(OBJ_DIR)/signals
							@mkdir -p $(OBJ_DIR)/utils

###	Rules for creating compiling .c files into obj
##	prod
$(OBJ_DIR)/%.o			:	$(SRC_DIR)/%.c | $(OBJ_DIR)
							$(PROGRESS_BAR)
							@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

libft					:	@make -C $(LIBFT)

clean					:
							@$(RM) $(OBJ_DIR) $(TEST_OBJ_DIR)
							@make clean -C $(LIBFT)
							@echo "$(VIVID_BLUE)[$(NAME)]:\t🔥 Object files cleaned.$(DEF_COLOR)"

fclean					:	clean
							@$(RM) $(NAME) $(TEST_EXEC)
							@$(RM) $(LIBFT)/libft.a
							@echo "$(MAGENTA)[$(NAME)]:\t🔥 All executable files cleaned.$(DEF_COLOR)"

re						:	fclean all
							@echo "$(BOLD_GREEN)[$(NAME)]:\t🚀 Cleaned and rebuilt all.$(DEF_COLOR)"

.PHONY					:	all clean fclean re

###	Progress Bar
#	Macro to update progress bar
define PROGRESS_BAR
	@if [ $(COUNT) -eq 0 ]; then	\
		printf "\n";				\
	fi
	$(eval COUNT=$(shell echo $$(($(COUNT) + 1))))
	@printf "\r$(PURPLE)🔄 Compiling $(NAME)\t: [%-$(TOTAL_SRC_FILES)s] (%d/%d) $(DEF_COLOR)" \
	$$(printf '=%.0s' $$(seq 1 $(COUNT))) $(COUNT) $(TOTAL_SRC_FILES)
endef