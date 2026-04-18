/*
 * Name: David Neškrabal
 * Email: david.neskrabal@ucdconnect.ie
 * Student ID: 24711891
 */

#ifndef SIGNALS_H
#define SIGNALS_H

extern int got_sigint;

/* on SIGINT write '\n' to stdout and flush stdout
 */
void handle_sigint(int sig);

/* initialize signal handler
 * includes handlers for:
 *     SIGINT
 */
void init_sig_handler();

#endif
