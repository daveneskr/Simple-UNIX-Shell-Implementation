/*
 * Name: David Neškrabal
 * Email: david.neskrabal@ucdconnect.ie
 * Student ID: 24711891
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include "signals.h"

int got_sigint;

/* on SIGINT write '\n' to stdout and flush stdout
 */
void handle_sigint(int sig) {
	(void)sig;
	got_sigint = 1;
	write(STDOUT_FILENO, "\n", sizeof(char));
	fflush(stdout);
}

/* initialize signal handler
 * includes handlers for:
 *     SIGINT
 */
void init_sig_handler() {
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}
