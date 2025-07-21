#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	(void)ac;
	(void)av;

	while (1)
	{
		line = readline(" Minisheeeeeeeeell ✗ ");
		if (line == NULL)
		{
			break ;
		}
		if (*line)
			add_history(line);
		if (parsing(line, envp))
			ft_printf("ca maaaarche !\n");
		if (ft_strncmp(line, "exit", 4) == 0)
			break ;
		free(line);
	}
	ft_printf("exit\n");
	return (0);
}