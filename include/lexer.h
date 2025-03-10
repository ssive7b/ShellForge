#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>

# define MAX_TOKEN_SIZE 4096

typedef enum e_token_type {
	TOKEN_WORD,
	TOKEN_OPERATOR,	// <<, >>, <, >, |, ||, &, && 
	TOKEN_QUOTE,
	TOKEN_EXPANSION,
	TOKEN_NEWLINE,
	TOKEN_WHITESPACE,
	TOKEN_COMMENT, 
	TOKEN_EOF
}	t_token_type;

typedef struct	s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef enum	e_lexer_state
{
	LEXER_DEFAULT,
	LEXER_IN_OPERATOR,
	LEXER_IN_SINGLE_QUOTE,
	LEXER_IN_DOUBLE_QUOTE,
	LEXER_IN_EXPANSION,
	LEXER_IN_SUBSTITUTION,
	LEXER_IN_COMMENT
}	t_lexer_state;

typedef struct s_lexer
{
	char			*input;
	size_t			char_idx;
	t_lexer_state	state;
	t_token			*tokens;
	char			*token_buffer; // initialize with the size of the input, free once tokenized
	size_t			buff_idx;
}	t_lexer;


// lexer.c
t_token	*ft_lexer(char *input);

// lexer_handler_funcs.c
void	ft_handle_eof(t_lexer *lx);
void	ft_handle_operator(t_lexer *lx, char c);
void	ft_handle_quotes(t_lexer *lx, char c);
void	ft_handle_expansion(t_lexer *lx, char c);
void	ft_handle_standalone_operator(t_lexer *lx, char c);
void	ft_handle_newline(t_lexer *lx);
void	ft_handle_whitespace(t_lexer *lx);
void	ft_handle_word_continuation(t_lexer *lx, char c);
void	ft_handle_comment(t_lexer *lx);
void	ft_handle_new_word(t_lexer *lx, char c);

// lexer_ops.c
t_token	*ft_create_token(t_token_type type, const char *value);
void	ft_append_token(t_lexer *lexer, t_token *new_token);
void	ft_finalize_token(t_lexer *lx, t_token_type type);
void	ft_append_char(t_lexer *lx, char c);

// lexer_utils.c
int	ft_is_whitespace(char c);
int	ft_is_operator(char c);
int	ft_is_quote(char c);
int	ft_is_expansion(char c);

#endif