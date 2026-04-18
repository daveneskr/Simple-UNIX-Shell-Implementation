/*
 * Name: David Neškrabal
 * Email: david.neskrabal@ucdconnect.ie
 * Student ID: 24711891
 */

#ifndef INPUT_H
#define INPUT_H

#define MAX_ARG 64

/* trim string from newline character
 */
void trim_newline(char *input);

/* reads a line from stdin
 * if input contains EOF, terminate program with EXIT_SUCCESS
 * on SIGINT returns null
 * on input error, terminates program with EXIT_FAILURE
 * returns an allocatted char* in heap (needs to be freed)
 */
char *readline_input();

/* tokenizes line by ' ' delimiter
 * returns an allocated char** of size MAX_ARG in heap (needs to be freed)
 * or null if line is null
 *
 * exits program if error at malloc
 */
char **tokenize(char *line);

#endif
