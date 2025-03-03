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
SRC_FILES_PARSER		=
SRC_FILES_EXEC			=	pseudo_test.c
SRC						=	$(addprefix $(SRC_DIR_APP)/, $(SRC_FILES_APP))				\
							$(addprefix $(SRC_DIR_PARSER)/, $(SRC_FILES_PARSER))		\
							$(addprefix $(SRC_DIR_EXEC)/, $(SRC_FILES_EXEC))

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

###	Target rules
#	Default Target
all						:	$(OBJ) $(NAME)

#	prod
$(NAME)					:	$(OBJ)
							@printf "\n"
							@make -C $(LIBFT) 
							@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
#	test
$(TEST_EXEC)			:	$(OBJ_PARSER) $(OBJ_EXEC) $(TEST_OBJ)
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
							@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

##	test
$(TEST_OBJ_DIR)/%.o		:	$(TEST_SRC_DIR)/%.c | $(TEST_OBJ_DIR)
							@$(CC) $(CFLAGS_TEST) -I$(INCLUDES) -c $< -o $@

test					:	$(TEST_EXEC)
							./$(TEST_EXEC)

clean					:
							@$(RM) $(OBJ_DIR) $(TEST_OBJ_DIR)
							@make clean -C $(LIBFT)

fclean					:	clean
							@$(RM) $(NAME) $(TEST_EXEC)
							@$(RM) $(LIBFT)/libft.a

re						:	fclean all

.PHONY					:	all clean fclean re test