#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "../libft/include/libft.h"

typedef struct s_tty	t_tty;

typedef struct s_envp
{
    char    **envp;
    int     last_exit_status; // Stores the last command's exit status
}   t_envp;

void expand_tokens(t_token *tokens, char **envp);
void expand_tilde(char **token, t_envp *env);
void expand_variables(char **token, t_envp *env);
void replace_variable(char **line, int pos, char *var_start, char *var_value);
void expand_wildcards(char **token);
char *getenv_list(t_envp *env, const char *name);
int valid_var_chr(char c);
char *ft_strjoin_three(const char *s1, const char *s2, const char *s3);
int match_wildcard(const char *str, const char *pattern);
char *ft_strjoin_free(char *s1, const char *s2);

# endif