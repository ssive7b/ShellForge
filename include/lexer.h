#ifndef LEXER_H
# define LEXER_H

# define MAX_TOKEN_SIZE 4096

typedef enum e_token_type {
	TOKEN_WORD,
	TOKEN_OPERATOR,	// <<, >>, <, >, |, ||, &, && 
	TOKEN_NEW_LINE,	// 
	TOKEN_END		// 
}	t_token_type;

typedef struct	e_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef enum	e_lexer_state
{
	LEXER_DEFAULT,
	LEXER_IN_WORD,
	LEXER_IN_QUOTE,
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

// lexer_state_handlers.c
void	ft_finalize_token(t_lexer *lx);
void	ft_handle_default_state(t_lexer *lx, char current_char);
void	ft_handle_single_quote_state(t_lexer *lx, char current_char);
void	ft_handle_double_quote_state(t_lexer *lx, char current_char);

// lexer_ops.c
t_token	*ft_create_token(t_token_type type, const char *value);
void	ft_append_token(t_lexer *lexer, t_token *new_token);

// lexer_utils.c
int	ft_is_whitespace(char c);
int	ft_is_operator(char c);
int	ft_is_quote(char c);
int	ft_is_expansion(char c);

#endif