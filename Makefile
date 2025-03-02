###	Variables
NAME				=	minishell
TEST_EXEC			=	test_runner
INCLUDES			=	./include
MAKEFLAGS			+=	--no-print-directory

###	Source files specs
SRC_DIR				=	src
SRC_FILES			=	pseudo_test.c
SRC					=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))

### Object files specs
OBJ_DIR				=	obj
OBJ					=	$(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

###	Compilation/ Linking specifications
CC					=	cc
CFLAGS				=	-Werror -Wextra -Wall
LDFLAGS				=	-lcriterion
RM					=	rm -rf

###	</Testing set-up
TEST_DIR			=	tests
TEST_SRC_FILES		=	test_harness.c
TEST_SRC_DIR		=	$(TEST_DIR)/src
TEST_OBJ_DIR		=	$(TEST_DIR)/obj
TEST_SRC			= 	$(addprefix $(TEST_SRC_DIR)/, $(TEST_SRC_FILES))
TEST_OBJ			=	$(addprefix $(TEST_OBJ_DIR)/, $(TEST_SRC_FILES:.c=.o))
CFLAGS_TEST			=	$(CFLAGS) -g
LDFLAGS_TEST		=	$(LDFLAGS) -lcriterion
###	Testing set-up />

###	Create obj files dirs
#	prod
$(OBJ_DIR)			:
						@mkdir -p $(OBJ_DIR)

#	test
$(TEST_OBJ_DIR)		:
						@mkdir -p $(TEST_OBJ_DIR)

###	Define rules for linking into the final exe
#	prod
$(NAME)				:	$(OBJ)
						@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
#	test
$(TEST_EXEC)		:	$(OBJ) $(TEST_OBJ)
						@$(CC) $(CFLAGS) -o $(TEST_EXEC) $(OBJ) $(TEST_OBJ) $(LDFLAGS_TEST)

###	Rules for creating compiling .c files into obj
#	prod
$(OBJ_DIR)/%.o		:	$(SRC_DIR)/%.c | $(OBJ_DIR)
						@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

#	test
$(TEST_OBJ_DIR)/%.o	:	$(TEST_SRC_DIR)/%.c | $(TEST_OBJ_DIR)
						@$(CC) $(CFLAGS_TEST) -I$(INCLUDES) -c $< -o $@

all					:	$(NAME)

test				:	$(TEST_EXEC)
						./$(TEST_EXEC)

clean				:
						@$(RM) $(OBJ_DIR) $(TEST_OBJ_DIR)

fclean				:	clean
						@$(RM) $(NAME) $(TEST_EXEC)

.PHONY				:	all clean fclean test