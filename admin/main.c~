/*
 * Copyright (C) 2012 - Marco A Benatto <benattoi@mandriva.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 */

#include <stdio.h>
#include <stdlib.h>


int main (int argc, char **argv){
	char *opt;

	if (argc < 2){
		printf("Usage: \n");
		printf(" include <event code> <script>\n");
		printf(" remove	 <event code> <script name>\n");
		printf(" list\n");
		printf(" remove-all <event code>\n");
		printf(" listen\n");

		return -1;
	}

	opt = argv[1];

	if (strcmp(opt, "include") == 0){
		/*validating parms count*/
		if (argc != 4){
			fprintf(stderr, "Missing parameters for include <event code> <script> or extra parameter found\n");
			return -1;
		}

		/*TODO: insert script into event-related folder*/
	}else if(strcmp(opt, "remove") == 0){
		if (argc != 4){
			fprintf(stderr, "Missing parameters for remove <event code> <script> or extra parameter found\n");
			return -1;
		}

		/*TODO: remove file from event-related folder*/
	}else if(strcmp(opt, "list") == 0){
		if (argc > 2){
			fprintf(stderr, "Extra parameters found, discarding command\n");
			return -1;
		}

		/*TODO: list all files from event-related folder*/
	}else if(strcmp(opt, "remove-all") == 0){
		if (argc != 3){
			fprintf(stderr, "Missing parameters for remove <event code> <script> or extra parameter found\n");
			return -1;
		}

		/*TODO: remove all files from event-related folder*/
	}else if(strcmp(opt, "listen") == 0){
		if (argc != 2){
			fprintf(stderr, "Missing parameters for remove <event code> <script> or extra parameter found\n");
			return -1;
		}

		/*TODO: subscribe into X server event queue and dump events into user screen*/
	}else{
		fprintf(stderr, "Unrecognized command\n");
		return -1;
	}

	return 0;
}
