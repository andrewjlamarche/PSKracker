/*
 * att.c
 *
 *  Created on: Jul 11, 2017
 *      Author: soxrok2212
 */

#include <stdio.h>
#include <limits.h>

void genpass(unsigned x, unsigned char *buf) {
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

char main() {
	static const char VERSION[] = "0.1";
	unsigned char pw[12];
	for (unsigned j = 0; j <= INT_MAX; j++) {
		genpass(j, pw);
		printf("%s\n", pw);
	}
}
