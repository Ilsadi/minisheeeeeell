#include "minishell.h"

void	disable_signal_echo(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return ;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
// \*term.c_lflag &= ~ECHOCTL;
// ECHOCTL = echo des caractères de contrôle(^C, ^\) *\