/*
 * att.c
 *
 *  Created on: Jul 11, 2017
 *      Author: soxrok2212 and rofl0r
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

void genpass589(unsigned x, unsigned char *buf1) {
	static const char CHARSET[] = "abcdefghijkmnpqrstuvwxyz23456789#%+=?";
	long double x1 = x * 465661287.5245797;
	long long x2 = x1;
	int i;
	buf1[12] = 0;
	for (i = 0; i < 6; i++) {
		int k1 = CHARSET[x2 % 37];
		x2 /= 37;
		int k2 = 50 + (x2 % 8);
		x2 /= 37;
		buf1[(10 - (i * 2)) + 1] = k1;
		buf1[(10 - (i * 2)) + 0] = k2;
	}
}

void genpass599(unsigned y, unsigned char *buf2) {
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
				goto eof;
			} else if ((strcmp("nvg599", optarg)) == 0) {
				/* for (unsigned j = 0; j <= INT_MAX; j++) {
				 genpass599(j, pw);
				 printf("%s\n", pw);
				 }
				 goto eof;
				 */
			} else {
				goto usage_err;
			}
			break;
		case 'h':
			goto usage_err;
			break;
		default:
			break;
		}
		opt = getopt_long(argc, argv, option_string, long_options, &long_index);
	}
	usage_err: fprintf(stderr, usage, SHORT_VERSION);
	eof: ;
	return DONE;
}
