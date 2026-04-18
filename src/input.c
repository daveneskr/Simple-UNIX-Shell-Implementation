/*
 * Name: David Neškrabal
 * Email: david.neskrabal@ucdconnect.ie
 * Student ID: 24711891
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "input.h"
#include "signals.h"

/* trim string from newline character
 */
void trim_newline(char *input) {
	char *newline = strchr(input, '\n');
	if (newline != NULL) {
		*newline = '\0';
	}
}

/* reads a line from stdin
 * if input contains EOF, terminate program with EXIT_SUCCESS
 * on SIGINT returns null
 * on input error, terminates program with EXIT_FAILURE
 * returns an allocatted char* in heap (needs to be freed)
 */
 char *readline_input() {
	char *buffer = NULL;
	size_t size = 0;

	errno = 0;

	if (getline(&buffer, &size, stdin) == -1) {
		// if input contains EOF, terminate
		if (feof(stdin)) {
			write(STDOUT_FILENO, "\n", sizeof(char));
			fflush(stdout);
			exit(EXIT_SUCCESS);
		// if SIGINT interrupt
		} else if (errno == EINTR && got_sigint) {
			clearerr(stdin);
			return NULL;
		// on error
		} else {
			perror("readline");
			exit(EXIT_FAILURE);
		}
	}

	trim_newline(buffer);

	return buffer;
}

/* tokenizes line by ' ' delimiter
 * returns an allocated char** of size MAX_ARG in heap (needs to be freed)
 * or null if line is null
 *
 * exits program if error at malloc
 */
char **tokenize(char *line) {
	if (line == NULL) return NULL;

	// allocate array of strings
	char **argv = malloc(MAX_ARG * sizeof(char *));
	if (argv == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	// tokenize line and add to array
	int argc = 0;
	char *token = strtok(line, " ");
	while (token != NULL) {
		argv[argc++] = token;
		token = strtok(NULL, " ");
	}

	// null-terminate array
	argv[argc] = NULL;

	return argv;
}
