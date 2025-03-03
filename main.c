/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 00:53:38 by cschnath          #+#    #+#             */
/*   Updated: 2025/03/03 12:16:16 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Compile with cc -Wall -Werror -Wextra main.c init.c -lreadline
// Run with ./a.out

#include "minishell.h"

int	main(int argc, char **argv)
{
	char *line;
    
	ft_init(argc, argv);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (line[0] != '\0')
			add_history(line);
		printf("%s\n", line);
		free(line);
	}
	return (0);
}






