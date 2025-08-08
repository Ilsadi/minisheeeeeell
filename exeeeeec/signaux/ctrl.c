//de ce que je comprends il faut faire le signin? permet signaux
#include "minishell.h"

//signaux a gerer
// SIGINT (Ctrl+C) : Interrompt le programme / Comportement : Nouvelle ligne + nouveau prompt
// SIGQUIT (Ctrl+\) : Interrompt le programme et génère un core dump
// EOF (Ctrl+D) : Indique la fin de l'entrée standard

volatile sig_atomic_t g_sig = 0; // Variable atomique pour les signaux
int g_in_cmd = 0; // Variable pour suivre si nous sommes dans une commande
//sig_atomic_t => permet de l'atomicite, c est a dire pas d interruption pendant l'execution

void sigint_handler(int sig)
{
	(void)sig;
	g_sig = SIGINT;
	if (!g_in_cmd)  // Si on n'est PAS dans une commande (au prompt)
	{
		write(STDOUT_FILENO, "\n", 1); // Affiche un saut de ligne
		rl_replace_line("", 0); // Remplace la ligne courante dans readline
		rl_on_new_line(); // Passe à la nouvelle ligne
		rl_redisplay(); // Redessine la ligne courante
	}
}

void setup_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART; // Relancer les appels système interrompus (utile avec readline)
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN); // Tu peux aussi mettre via sigaction si tu veux être cohérent
}
void setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL); // Réinitialise le handler pour SIGINT
	signal(SIGQUIT, SIG_DFL); // Réinitialise le handler pour SIGQUIT
}
// a implementer dans le main principal + dans le exec 
