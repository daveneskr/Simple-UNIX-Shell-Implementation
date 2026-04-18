/*
 * Name: David Neškrabal
 * Email: david.neskrabal@ucdconnect.ie
 * Student ID: 24711891
 */

#ifndef BUILTINS_H
#define BUILTINS_H

#define NOT_CD  1
#define ERR_CD (-1)
#define OK_CD   0

/* checks if the first argument is "cd"
 * if not, return NOT_CD
 * if yes, change the current directory based on the second argument
 */
int cd(char **argv);

#endif
