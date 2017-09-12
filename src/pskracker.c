/*
 * PSKracker: WPA/WPA2/WPS default key/pin generator written in C.
 *
 * Copyright (c) 2017, soxrok2212 <soxrok2212@gmail.com>
 * SPDX-License-Identifier: GPL-3.0+
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "pskracker.h"
#include "version.h"
#include "att.h" // att module
#include "xfinity.h" // xfinity module

int DONE = 1;
char ERR[120]; // should change this
char TARGET[9];
char MODE[4];
/**
 * Serial and mac address are for future keygens
 * (and once I actually know C :P)
 */
//char SERIAL[];
//
char MADDR[11];
/**
 * Just some command line arguments using getopt
 */
static const char *option_string = "t:e:s:m:h";
static const struct option long_options[] = { { "target", required_argument, 0,
		't' }, { "encryption", required_argument, 0, 'e' }, { "serial",
required_argument, 0, 's' }, { "maddr",
required_argument, 0, 'm' }, { "help", no_argument, 0, 0 }, { 0,
no_argument, 0, 'h' }, { 0, 0, 0, 0 } };

void usage_err() {
	fprintf(stderr, usage, SHORT_VERSION);
	exit(0);
}
void usage_err_verbose() {
	fprintf(stderr, usage_verbose, SHORT_VERSION);
	exit(0);
}

/**
 *  This probably isn't optimal coding technique but it works
 *  Just some simple configuration vectors
 *  Thanks for understanding
 */

void bruteforce() {
	unsigned char pw[13]; // set size of password (12)
	if (((strcmp("nvg589", TARGET)) == 0) && ((strcmp("wpa", MODE)) == 0)) {
		for (int k = 0; k <= INT_MAX; k++) {
			genpass589(k, pw);
			printf("%s\n", pw);
			DONE = 0;
		}
	} else if (((strcmp("nvg599", TARGET)) == 0)
			&& ((strcmp("wpa", MODE)) == 0)) {
		for (int k = 0; k <= INT_MAX; k++) {
			genpass599(k, pw);
			printf("%s\n", pw);
			DONE = 0;
		}
	} else if ((((strcmp("dpc3939", TARGET)) == 0)
			|| ((strcmp("dpc3941", TARGET)) == 0)
			|| ((strcmp("tg1682g", TARGET)) == 0))
			&& ((strcmp("wpa", MODE)) == 0)) {
		genpassXHS();
		DONE = 0;
	} else {
		usage_err();
	}
}

int main(int argc, char **argv) {
	int opt = 0;
	int long_index = 0;

	opt = getopt_long(argc, argv, option_string, long_options, &long_index);
	while (opt != -1) {
		switch (opt) {

		case 't': // target model number selection
			if ((strcmp("nvg589", optarg)) == 0) {
				strcpy(TARGET, optarg);

			} else if ((strcmp("nvg599", optarg)) == 0) {
				strcpy(TARGET, optarg);

			} else if ((strcmp("smcd3gnv", optarg)) == 0) {
				strcpy(TARGET, optarg);
			} else if (((strcmp("dpc3939", optarg)) == 0)
					|| ((strcmp("dpc3941", optarg)) == 0)
					|| ((strcmp("tg1682g", optarg)) == 0)) {
				strcpy(TARGET, optarg);
			} else
				usage_err();
			break;

		case 'e': // security/encryption mode selection
			if ((strcmp("wpa", optarg)) == 0) {
				strcpy(MODE, optarg);

			} else if ((strcmp("wps", optarg)) == 0) {
				strcpy(MODE, optarg);
			} else
				usage_err();
			break;

		case 'm':
			if ((strlen(optarg) == 10)) {
				strcpy(MADDR, optarg);
			} else {
				strcpy(ERR,
						"Invalid MAC Address or length. Please enter the MAC Address without colons. Ex: 0011223344\n");
			}
			break;
		case 'h':
			// display verbose help
			usage_err_verbose();
			break;

		default:
			usage_err();
			break;
		}
		opt = getopt_long(argc, argv, option_string, long_options, &long_index);
	}
	bruteforce();
	printf("%s", ERR);
	return DONE;
}
