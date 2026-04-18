/*
 * Name: David Neškrabal
 * Email: david.neskrabal@ucdconnect.ie
 * Student ID: 24711891
 */

#ifndef EXEC_H
#define EXEC_H

/* returns index of a string in array of strings
 * or -1 otherwise
 */
int find_string(char **argv, char *str);

/* redirect stdout to a file at 'filepath'
 * returns file pointer to original stdout for later restoration
 * or -1 on failure
 */
int redirect_stdout(char *filepath);

/* looks for ">" in argv
 * if present
 * 	1. checks if some arg after ">" exists
 *	2. redirects stdout
 *	3. trims argv from ">"
 * returns 0 on success
 * or -1 otherwise
 */
int redirect(char **argv);

/* restore stdout to f
 * return 0 on success and -1 otherwise
 */
int restore_stdout(int f);

/* spans a new process and executes command line argument based on argv
 * supports stdout redirection to file using >
 * returns 0 on success and -1 otherwise
 */
int run_command(char **argv);

#endif
