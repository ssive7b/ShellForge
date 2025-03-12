int	ft_is_whitespace(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	ft_is_operator(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>');
}

int	ft_is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	ft_is_expansion(char c)
{
	return (c == '$' || c == '`');
}