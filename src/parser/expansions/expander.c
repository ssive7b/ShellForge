#include "ast_mock.h"
#include "expansions.h"
#include "lexer.h"
#include "minishell.h"
#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

void expand_tokens(t_token *tokens, char **envp)
{
	while (tokens)
	{
		if (tokens->value[0] == '\0') // Skip empty tokens
		{
			tokens = tokens->next;
			continue;
		}
		if (ft_strncmp(tokens->value, "<<", 2) == 0)
		{
			if (tokens->next)
				tokens = tokens->next->next;
			else
				tokens = tokens->next;
			continue;
		}
		expand_tilde(&tokens->value, envp);
		expand_variables(&tokens->value, envp);
		expand_wildcards(&tokens->value);
		tokens = tokens->next;
	}
}

// Replaces Tilde with the HOME environment variable
void	expand_tilde(char **token, t_envp *env)
{
	char	*home;
	char	*expanded;

	if (!(*token) || **token != '~')
		return ;
	home = getenv_list(env, "HOME");
	if (!home)
		return ;
	if ((*token)[1] == '\0') // "~" alleine
		expanded = ft_strdup(home);
	else
		expanded = ft_strjoin(home, (*token) + 1);
	free(*token);
	*token = expanded;
}

// Expands $VAR and $?
void	expand_variables(char **token, t_envp *env)
{
	int		i;
	char	*var_start;
	char	*expanded;
	char	*var_value;

	i = 0;
	expanded = ft_strdup(*token);
	while (expanded[i])
	{
		if (expanded[i] == '$' && valid_var_chr(expanded[i + 1]))
		{
			var_start = &expanded[i + 1];
			if (*var_start == '?')
				var_value = ft_itoa(env->last_exit_status);
			else
				var_value = getenv_list(env, var_start);
			replace_variable(&expanded, i, var_start, var_value);
			if (var_value)
				free(var_value);
		}
		i++;
	}
	free(*token);
	*token = expanded;
}

void	replace_variable(char **line, int pos, char *var_start, char *var_value)
{
	char	*before;
	char	*after;
	char	*new_line;
	int		var_len;

	var_len = 0;
	while (valid_var_chr(var_start[var_len]))
		var_len++;
	before = ft_substr(*line, 0, pos);
	after = ft_strdup(&var_start[var_len]);
	if (var_value)
		new_line = ft_strjoin_three(before, var_value, after);
	else
		new_line = ft_strjoin_three(before, "", after);
	free(*line);
	*line = new_line;
	free(before);
	free(after);
}

void	expand_wildcards(char **token)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*expanded;

	expanded = NULL;
	if (!ft_strchr(*token, '*'))
		return ;
	dir = opendir(".");
	if (!dir)
		return ;
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] == '.' && (*token)[0] != '.')
			continue ;
		if (match_wildcard(entry->d_name, *token))
		{
			if (expanded)
				expanded = ft_strjoin_free(expanded, " ");
			expanded = ft_strjoin_free(expanded, entry->d_name);
		}
	}
	closedir(dir);
	if (expanded && *expanded)
	{
		free(*token);
		*token = expanded;
	}
	else
		free(expanded);
}

char	*getenv_list(t_envp *env, const char *name)
{
	int		i;
	size_t	name_len;

	if (!env || !env->envp || !name)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (env->envp[i])
	{
		// Check if "KEY=" matches the start of the env var
		if (ft_strncmp(env->envp[i], name, name_len) == 0 && env->envp[i][name_len] == '=')
			return (env->envp[i] + name_len + 1); // Return pointer to VALUE part
		i++;
	}
	return (NULL);
}


int	valid_var_chr(char c)
{
	return (ft_isalpha(c) || c == '_' || c == '?');
}

char	*ft_strjoin_three(const char *s1, const char *s2, const char *s3)
{
	char	*temp;
	char	*result;

	if (!s1 || !s2 || !s3)
		return (NULL);
	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, s3);
	free(temp);
	return (result);
}

int	match_wildcard(const char *str, const char *pattern)
{
	if (!*pattern)
		return (!*str);
	if (*pattern == '*')
	{
		while (*str)
		{
			if (match_wildcard(str, pattern + 1))
				return (1);
			str++;
		}
		return (match_wildcard(str, pattern + 1));
	}
	if (*pattern == *str || *pattern == '?')
		return (match_wildcard(str + 1, pattern + 1));
	return (0);
}

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}
