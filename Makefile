###	Variables
NAME					=	minishell
TEST_EXEC				=	test_runner
LIBFT 					=	libft
INCLUDES				=	./include
MAKEFLAGS				+=	--no-print-directory

###	Source files specs
#	dirs
SRC_DIR					=	src
SRC_DIR_APP				=	$(SRC_DIR)/app
SRC_DIR_PARSER			=	$(SRC_DIR)/parser
SRC_DIR_EXEC			=	$(SRC_DIR)/executioner
#	files
SRC_FILES_APP			=	main.c
SRC_FILES_PARSER		=	parse_placeholder.c
SRC_FILES_EXEC			=	pseudo_test.c
SRC						=	$(addprefix $(SRC_DIR_APP)/, $(SRC_FILES_APP))				\
							$(addprefix $(SRC_DIR_PARSER)/, $(SRC_FILES_PARSER))		\
							$(addprefix $(SRC_DIR_EXEC)/, $(SRC_FILES_EXEC))
TOTAL_SRC_FILES			:=	$(words $(SRC))

### Object files specs
#	dirs
OBJ_DIR					=	obj
OBJ_DIR_APP				=	$(OBJ_DIR)/app
OBJ_DIR_PARSER			=	$(OBJ_DIR)/parser
OBJ_DIR_EXEC			=	$(OBJ_DIR)/executioner
#	files
OBJ_APP					=	$(addprefix $(OBJ_DIR_APP)/, $(SRC_FILES_APP:.c=.o))
OBJ_PARSER				=	$(addprefix $(OBJ_DIR_PARSER)/, $(SRC_FILES_PARSER:.c=.o))
OBJ_EXEC				=	$(addprefix $(OBJ_DIR_EXEC)/, $(SRC_FILES_EXEC:.c=.o))
OBJ						=	$(OBJ_APP) $(OBJ_PARSER) $(OBJ_EXEC)

###	Compilation/ Linking configs
CC						=	cc
CFLAGS					=	-Werror -Wextra -Wall
LDFLAGS					=	-lreadline -Llibft -lft
RM						=	rm -rf
COUNT					:=	0

###	</Testing set-up
TEST_DIR				=	tests
TEST_SRC_FILES			=	test_harness.c
TEST_SRC_DIR			=	$(TEST_DIR)/src
TEST_OBJ_DIR			=	$(TEST_DIR)/obj
TEST_SRC				= 	$(addprefix $(TEST_SRC_DIR)/, $(TEST_SRC_FILES))
TEST_OBJ				=	$(addprefix $(TEST_OBJ_DIR)/, $(TEST_SRC_FILES:.c=.o))
CFLAGS_TEST				=	$(CFLAGS) -g
LDFLAGS_TEST			=	$(LDFLAGS) -lcriterion
###	Testing set-up />

###	Color Schemes
DEF_COLOR		=	\033[0;37m # Light gray
BOLD_GREEN		=	\033[1;32m
ORANGE			=	\033[0;33m
VIVID_BLUE		=	\033[1;34m
PURPLE			=	\033[0;35m
MAGENTA			=	\033[1;35m

###	Target rules
#	Default Target
all						:	$(OBJ) $(NAME)

#	prod
$(NAME)					:	$(OBJ) 
							@printf "\n"
							@printf "\n$(DEF_COLOR)🔄 Compiling dependencies...$(DEF_COLOR)\n"
							@make -C $(LIBFT) 
							@printf "\n$(DEF_COLOR)✅ Dependencies fulfilled.$(DEF_COLOR)\n"
							@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
							@printf "\n$(BOLD_GREEN)[$(NAME)]:\t✅ $(NAME) compiled successfully!$(DEF_COLOR)\n"
#	test
$(TEST_EXEC)			:	$(OBJ_PARSER) $(OBJ_EXEC) $(TEST_OBJ)
							@make -C $(LIBFT) 
							@echo "$(ORANGE)[$(NAME)]:\t🔧 Testing mode activated.$(DEF_COLOR)"
							@$(CC) $(CFLAGS) -o $(TEST_EXEC) $(OBJ_PARSER) $(OBJ_EXEC) $(TEST_OBJ) $(LDFLAGS_TEST)

$(OBJ)					:	$(OBJ_DIR)
$(OBJ_PARSER)			:	$(OBJ_DIR)
$(OBJ_EXEC)				:	$(OBJ_DIR)
$(TEST_OBJ)				:	$(TEST_OBJ_DIR)

#	Create the object directory if it doesn't exist
$(OBJ_DIR)				:	
							@mkdir -p $(OBJ_DIR)
							@mkdir -p $(OBJ_DIR_APP)
							@mkdir -p $(OBJ_DIR_PARSER)
							@mkdir -p $(OBJ_DIR_EXEC)

#	test
$(TEST_OBJ_DIR)			:
							@mkdir -p $(TEST_OBJ_DIR)

###	Rules for creating compiling .c files into obj
##	prod
$(OBJ_DIR)/%.o			:	$(SRC_DIR)/%.c | $(OBJ_DIR)
							$(PROGRESS_BAR)
							@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

##	test
$(TEST_OBJ_DIR)/%.o		:	$(TEST_SRC_DIR)/%.c | $(TEST_OBJ_DIR)
							@$(CC) $(CFLAGS_TEST) -I$(INCLUDES) -c $< -o $@

test					:	$(TEST_EXEC)
							@./$(TEST_EXEC)

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

.PHONY					:	all clean fclean re test

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