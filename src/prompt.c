/*
 * Name: David Neškrabal
 * Email: david.neskrabal@ucdconnect.ie
 * Student ID: 24711891
 */

#include <stdio.h>
#include <time.h>
#include "prompt.h"

#define STRTIME_MAX_LEN 15

/* print current time to stdout
 * in format "[dd/mm hh:mm]"
 */
void print_time() {
	time_t t = time(NULL);
	char strT[STRTIME_MAX_LEN];
	struct tm *tm_struct = localtime(&t);
	strftime(strT, STRTIME_MAX_LEN, "[%d/%m %H:%M]", tm_struct);
	printf("%s", strT);
}

/* print promt to stdout
 * in format "[dd/mm hh:mm]# "
 */
void print_prompt() {
	print_time();
	putchar('#');
	putchar(' ');
}
