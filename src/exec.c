/*
 * Name: David Neškrabal
 * Email: david.neskrabal@ucdconnect.ie
 * Student ID: 24711891
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "exec.h"

/* returns index of a string in array of strings
 * or -1 otherwise
 */
int find_string(char **argv, char *str) {
	int idx = 0;
	// iterate over array, comparing each element with str
	while (*argv != NULL) {
		// return index if found
		if (strcmp(*argv, str) == 0) {
			return idx;
		}
		idx++;
		argv++;
	}
	return -1;
}

/* redirect stdout to a file at 'filepath'
 * returns file pointer to original stdout for later restoration
 * or -1 on failure
 */
int redirect_stdout(char *filepath) {
	// open file with rw-rw-rw- permissions
	int f = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (f < 0) {
		perror("open");
		return -1;
	}
	dup2(f, STDOUT_FILENO); // redirect stdout
	close(f);

	// save current stdout pointer
	int saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1) {
		perror("dup");
		return -1;
	}

	return saved_stdout;
}

/* looks for ">" in argv
 * if present
 * 	1. checks if some arg after ">" exists
 *	2. redirects stdout
 *	3. trims argv from ">"
 * returns 0 on success
 * or -1 otherwise
 */
int redirect(char **argv) {
    int redir = find_string(argv, ">");
    if (redir == -1) {
        return 0;   // no redirection, but not an error
    }

    if (argv[redir + 1] == NULL) {
        fprintf(stderr, "missing argument after >\n");
        return -1;
    }

    if (argv[redir + 2] != NULL) {
        fprintf(stderr, "invalid redirection syntax\n");
        return -1;
    }

    char *path = argv[redir + 1];

    if (redirect_stdout(path) == -1) {
        return -1;
    }

    argv[redir] = NULL;
    argv[redir + 1] = NULL;

    return 0;
}

/* restore stdout to f
 * return 0 on success and -1 otherwise
 */
int restore_stdout(int f) {
	fflush(stdout); // clean buffer
	if (dup2(f, STDOUT_FILENO) == -1) {
		perror("dup2");
		return -1;
	}
	close(f);

	return 0;
}

/* spans a new process and executes command line argument based on argv
 * supports stdout redirection to file using >
 * returns 0 on success and -1 otherwise
 */
int run_command(char **argv) {
	if (argv == NULL) return 0;

	pid_t pid = fork();
	if (pid == 0) { // child
	    if (redirect(argv) == -1) {
	        exit(EXIT_FAILURE);
	    }

	    printf("Executing in child process..\n");
	    execvp(argv[0], argv);

	    // only reached if exec fails
	    perror(argv[0]);
	    exit(EXIT_FAILURE);

	} else if (pid > 0) { // parent
		int status;
		wait(&status);
		if (status == EXIT_FAILURE) {
			return -1;
		}
	} else {
		perror("fork");
		return -1;
	}

	return 0;
}
