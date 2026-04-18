/*
 * Name: David Neškrabal
 * Email: david.neskrabal@ucdconnect.ie
 * Student ID: 24711891
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtins.h"

/* checks if the first argument is "cd"
 * if not, return NOT_CD
 * if yes, change the current directory based on the second argument
 */
int cd(char **argv) {
	// check if first arg is "cd"
	if (strcmp(*argv, "cd") != 0) return NOT_CD;

	char *path;
	if (argv[1] != NULL) { // if second argument present, use as direcotry path
		path = argv[1];
	} else {               // if not, change to HOME
		path = getenv("HOME");
	}

	// change current directory to 'path'
	int result = chdir(path);
	if (result == -1) {
		perror("cd");
		return ERR_CD;
	}

	return OK_CD;
}
