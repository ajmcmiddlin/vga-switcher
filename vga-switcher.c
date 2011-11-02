/* 
 * Simple C program that sends the ON/OFF commands to the switch file in
 * /sys/kernel/debug/vgaswitcheroo/switch.  We are writing a C program because
 * a shell script is not safe to be run with setuid as root.
 *
 * Takes either ON or OFF as its only argument.  ON turns the discrete graphics
 * on, and OFF turns it off.
 *
 * NOTE: This code has only been tested on Xubuntu 11.10 with the latest
 * version of asus-switcheroo from awilliam's github repo.
 * https://github.com/awilliam/asus-switcheroo
 *
 * This code is open source, but I have no idea what license to use.
 */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>


int main(int argc, const char *argv[]) {
	const char * const ARG_ERROR = "Must provide 'ON' or 'OFF' as only argument";
	const char * const SWITCH_PATH = "/sys/kernel/debug/vgaswitcheroo/switch";
	int arg_length = 0;
	
	if (argc != 2) {
		printf("%s\n", ARG_ERROR);
		exit(1);
	}

	arg_length = strlen(argv[1]);
	if ((arg_length != 2) && (arg_length != 3)) {
		printf("%s\n", ARG_ERROR);
		exit(2);
	}

	if ((strncmp(argv[1], "ON", 2) != 0) && (strncmp(argv[1], "OFF", 3) != 0)) {
		printf("%s\n", ARG_ERROR);
		exit(3);
	}
	
	struct stat unused_stat;
	if (stat(SWITCH_PATH, &unused_stat) != 0) {
		printf("Unable to stat %s\n", SWITCH_PATH);
		exit(4);
	}

	FILE *switch_file = 0;
	switch_file = fopen(SWITCH_PATH, "w");
	if (switch_file == 0) {
		printf("Error opening %s\n", SWITCH_PATH);
		exit(5);
	}

	fprintf(switch_file, "%s", argv[1]);
	fclose(switch_file);

	exit(0);
}

