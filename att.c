/*
 * ATTxxxxxxx PSKracker: ATTxxxxxxx WPA default password generator.
 *           Thank you to mrfancypants for research and preliminary Python code.
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

#include "att.h"
#include "version.h"

int DONE = 0;

static const char *option_string = "m:h";
static const struct option long_options[] = { { "mode", required_argument, 0,
		'm' }, { "help", no_argument, 0, 0 }, { 0, no_argument, 0, 'h' }, { 0,
		0, 0, 0 } };

void usage_err() {
	fprintf(stderr, usage, SHORT_VERSION);
}

void genpass589(unsigned x, unsigned char *buf) {
	static const char CHARSET[] = "abcdefghijkmnpqrstuvwxyz23456789#%+=?";
	long double x1 = x * 465661287.5245797;
	long long x2 = x1;
	int i;
	buf[12] = 0;
	for (i = 0; i < 6; i++) {
		int k1 = CHARSET[x2 % 37];
		x2 /= 37;
		int k2 = 50 + (x2 % 8);
		x2 /= 37;
		buf[(10 - (i * 2)) + 1] = k1;
		buf[(10 - (i * 2)) + 0] = k2;
	}
}

void genpass599(unsigned y, unsigned char *buf) {
	// not implemented yet
}

int main(int argc, char **argv) {
	unsigned char pw[13];
	int opt = 0;
	int long_index = 0;

	opt = getopt_long(argc, argv, option_string, long_options, &long_index);
	while (opt != -1) {
		switch (opt) {
		case 'm':
			if ((strcmp("nvg589", optarg)) == 0) {
				for (unsigned j = 0; j <= INT_MAX; j++) {
					genpass589(j, pw);
					printf("%s\n", pw);
				}
			} else if ((strcmp("nvg599", optarg)) == 0) {
				/* for (unsigned j = 0; j <= INT_MAX; j++) {
				 genpass599(j, pw);
				 printf("%s\n", pw);
				 }
				 */
			} else {
				usage_err();
			}
			break;
		case 'h':
				usage_err();
			break;
		default:
			break;
		}
		opt = getopt_long(argc, argv, option_string, long_options, &long_index);
	}
	return DONE;
}
