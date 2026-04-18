/*
 * Name: David Neškrabal
 * Email: david.neskrabal@ucdconnect.ie
 * Student ID: 24711891
 */

#include <stdlib.h>
#include "signals.h"
#include "prompt.h"
#include "input.h"
#include "builtins.h"
#include "exec.h"

int main() {
	init_sig_handler();

	// Shell main loop
	while (1) {
		got_sigint = 0;
		print_prompt();
		char *line = readline_input();
	    char **argv = tokenize(line);
	    if (argv != NULL) {
	        int cd_result = cd(argv); // try run built-in cd
	        if (cd_result == NOT_CD) {
	            run_command(argv); // run external command
	        }
	    }
	    free(argv);
	    free(line);
	}
}

